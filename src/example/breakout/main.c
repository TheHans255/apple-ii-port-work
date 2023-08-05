#include "apple-ii-monitor.h"
#include "apple-ii-mmio.h"
#include "stdio.h"

// C adaptation of Integer Basic BREAKOUT program
// from the Apple II Red Book, by TheHans255.
// Waiting for VBLANK (an Apple IIe feature)
// is used to account for the difference in execution speed,
// and the sound functions are improved.

// VARIABLE NOTES:
// A$: Player Name
// B$: Y/N Buffer
// A: Background Color
// B: Even Brick Color
// C: Odd Brick Color
// D: Paddle Color
// E: Ball Color
// I: (Temporary Iterator Variable)
// J: (Temporary Iterator Variable)
// L: Balls Left
// M: (Dummy Variable for Speaker PEEK)
// N: Number of Ball Hits Per Round
// P: (Paddle Vertical Previous Position) (not used)
// Q: Paddle Vertical Position
// S: Score
// V: Ball X Velocity
// W: Ball Y Velocity (divided by 3)
// X: Ball X Position
// Y: Ball Y Position (divided by 3)

int rand();
void srand(int);

void setup_text_mode();
void setup_graphics_mode();
void wait_for_vblank();

void reset_round();
void update_paddle();
void update_ball();
void main_loop();
void kill_ball();
void end_game();

unsigned int player_score = 0;
unsigned char balls_remaining = 0;
unsigned char paddle_y = 0;
unsigned int ball_hits_in_round = 0;
unsigned char time_until_serve = 0;
signed char ball_x = 0;
signed char ball_y = 0;
signed char ball_dx = 0;
signed char ball_dy = 0;

enum appleii_lores_color BACKGROUND_COLOR = LORES_MAGENTA;
enum appleii_lores_color EVEN_BRICK_COLOR = LORES_YELLOW;
enum appleii_lores_color ODD_BRICK_COLOR = LORES_ORANGE;
enum appleii_lores_color PADDLE_COLOR = LORES_MEDIUM_BLUE;
enum appleii_lores_color BALL_COLOR = LORES_WHITE;

void setup_text_mode() {
    *APPLEII_TEXTMODE_TEXT = 0;
    *APPLEII_MONITOR_WNDLFT = 0;
    *APPLEII_MONITOR_WNDWDTH = 39;
    *APPLEII_MONITOR_WNDTOP = 0;
    *APPLEII_MONITOR_WNDBTM = 23;
}

void setup_graphics_mode() {
    *APPLEII_MIXEDMODE_ON = 0;
    *APPLEII_HIRES_OFF = 0;
    *APPLEII_TEXTMODE_GRAPHICS = 0;
    *APPLEII_MONITOR_WNDLFT = 0;
    *APPLEII_MONITOR_WNDWDTH = 39;
    *APPLEII_MONITOR_WNDTOP = 20;
    *APPLEII_MONITOR_WNDBTM = 23;
}

void wait_for_vblank() {
    while (*APPLEIIE_VBLANK >= 128);
    while (*APPLEIIE_VBLANK < 128);
}

void reset_round() {
    appleii_setcol(BACKGROUND_COLOR);
    appleii_plot(ball_x, ball_y / 3);
    ball_x = 19;
    ball_y = rand() % 120;
    ball_dx = -1;
    ball_dy = (rand() % 5) - 2;
    *APPLEII_MONITOR_CH = 6;
    if (balls_remaining > 1) {
        printf("BALLS LEFT: %d\n", balls_remaining);
    } else {
        printf("LAST BALL!   \n");
    }
    time_until_serve = 60;
}

void update_paddle() {
    // signed int paddle_y_raw = ((signed int) appleii_pread(0) - 20) / 6;
    // if (paddle_y_raw < 0) paddle_y_raw = 0;
    // if (paddle_y_raw > 34) paddle_y_raw = 34;
    // paddle_y = (unsigned char) paddle_y_raw;
    paddle_y++;
    if (paddle_y > 34) paddle_y = 0;

    appleii_setcol(PADDLE_COLOR);
    appleii_vline(0, paddle_y, paddle_y + 5);
    appleii_setcol(BACKGROUND_COLOR);
    if (paddle_y > 0) {
        appleii_vline(0, 0, paddle_y - 1);
    }
    if (paddle_y < 34) {
        appleii_vline(0, paddle_y + 5, 39);
    }
}

void update_ball() {
    unsigned char old_ball_x = ball_x;
    unsigned char old_ball_y = ball_y;

    appleii_setcol(BACKGROUND_COLOR);

    ball_y += ball_dy;
    if (ball_y < 0 || ball_y > 120) {
        ball_y = old_ball_y;
        ball_dy = -ball_dy;
        // TODO: play bump sound
    }
    ball_x += ball_dx;
    if (ball_x < 0) {
        kill_ball();
        return;
    }
    if (ball_x > 39) {
        ball_x = old_ball_x;
        ball_dx = -ball_dx;
        // TODO: play bump sound
    } else {
        enum appleii_lores_color ball_pos_color = appleii_scrn(ball_x, ball_y / 3);
        if (ball_pos_color == BACKGROUND_COLOR) {
            // do nothing
        } else if (ball_x == 0) {
            // must be a paddle hit
            ball_hits_in_round++;
            ball_dx = (ball_hits_in_round > 5) + 1;
            ball_dy = ((ball_y / 3) - paddle_y) * 2 - 5;
        } else {
            // must be a block hit
            ball_dy = -ball_dy;
            appleii_vline(ball_x, ball_y / 6 * 2, ball_y / 6 * 2 + 1);
            player_score += ball_x / 2 - 9;
            *APPLEII_MONITOR_CH = 13;
            appleii_vtab(21);
            printf("%3d\n", player_score);
            // TODO: play block hit sound
        }
    }
    
    appleii_plot(old_ball_x, old_ball_y / 3);
    appleii_setcol(BALL_COLOR);
    appleii_plot(ball_x, ball_y / 3);
}

void kill_ball() {
    // TODO: play kill sound
    balls_remaining--;
    if (balls_remaining >= 1) {
        reset_round();
    }
}

const char *SCORE_RATINGS[] = {
    "TERRIBLE!",
    "LOUSY.",
    "POOR.",
    "GOOD.",
    "VERY GOOD.",
    "EXCELLENT.", 
    "NEARLY PERFECT."
};

void main_loop() {
    setup_graphics_mode();
    appleii_vtab(20);
    appleii_setcol(BACKGROUND_COLOR);
    for (unsigned char i = 0; i < 39; i++) {
        appleii_vline(i, 0, 39);
    }
    for (unsigned char i = 20; i < 34; i += 2) {
        *APPLEII_MONITOR_CH = i + 1;
        printf("%d", i / 2 - 9);
        appleii_setcol(EVEN_BRICK_COLOR);
        appleii_vline(i, 0, 39);
        appleii_setcol(ODD_BRICK_COLOR);
        for (unsigned char j = i % 4; j < 39; j += 4) {
            appleii_vline(i, j, j+1);
        }
    }
    *APPLEII_MONITOR_CH = 5;
    printf("SCORE =0\n\n\n");
    *APPLEII_MONITOR_WNDTOP = 21;

    player_score = 0;
    balls_remaining = 5;
    reset_round();
    while (1) {
        if (balls_remaining <= 0) {
            printf("YOUR SCORE OF %d IS %s\n", player_score, SCORE_RATINGS[player_score / 100]);
            break;
        }
        if (player_score >= 720) {
            printf("CONGRATULATIONS, YOU WIN!\n");
            break;
        }
        update_paddle();
        if (time_until_serve > 0) {
            time_until_serve--;
        } else {
            update_ball();
        }
        wait_for_vblank();
    }
}

int main() {
    setup_text_mode();
    appleii_home();
    *APPLEII_MONITOR_CH = 10;
    appleii_vtab(4);
    printf("*** BREAKOUT ***\n\n");
    printf("  OBJECT IS TO DESTROY ALL BRICKS\n\n");
    printf("  PRESS KEY TO BEGIN");
    getchar();

    while (1) {
        srand(*APPLEII_MONITOR_RND);
        main_loop();
        printf("ANOTHER GAME (Y/N)?");
        unsigned char response = getchar();
        if (response != 'Y' && response != 'y') {
            break;
        }
    }

    // NOTE: The old program printed "GAME OVER" here,
    // but that won't show up because ProDOS will take
    // us back to the system menu
    return 0;
}