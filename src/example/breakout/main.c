#include "apple-ii-monitor.h"
#include "apple-ii-mmio.h"
#include "sound.h"
#include "stdio.h"

// C adaptation of Integer Basic BREAKOUT program
// from the Apple II Red Book, by TheHans255.
// Waiting for VBLANK (an Apple IIe feature)
// is used to account for the difference in execution speed,
// and the sound functions are improved.

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
unsigned char time_until_ball_active = 0;
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
    *APPLEII_MONITOR_CH = 5;
    if (balls_remaining > 1) {
        printf("BALLS LEFT: %d\n", balls_remaining);
    } else {
        printf("LAST BALL!   \n");
    }
    time_until_ball_active = 60;
    ball_hits_in_round = 0;
}

void update_paddle() {
    signed int paddle_y_raw = ((signed int) appleii_pread(0) - 20) / 6;
    if (paddle_y_raw < 0) paddle_y_raw = 0;
    if (paddle_y_raw > 34) paddle_y_raw = 34;
    paddle_y = (unsigned char) paddle_y_raw;

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
    if (ball_y < 0 || ball_y >= 120) {
        ball_y = old_ball_y;
        ball_dy = -ball_dy;
        square_wave(1000, 110);
    }
    ball_x += ball_dx;
    if (ball_x < 0) {
        kill_ball();
        return;
    }
    if (ball_x > 39) {
        ball_x = old_ball_x;
        ball_dx = -ball_dx;
        square_wave(1000, 110);
    } else {
        unsigned char ball_screen_x = ball_x;
        unsigned char ball_screen_y = ball_y / 3;
        enum appleii_lores_color ball_pos_color = appleii_scrn(ball_screen_x, ball_screen_y);
        if (ball_pos_color == BACKGROUND_COLOR) {
            // do nothing
        } else if (ball_x == 0) {
            // must be a paddle hit
            ball_hits_in_round++;
            ball_dx = (ball_hits_in_round > 5) + 1;
            ball_dy = (ball_screen_y - paddle_y) * 2 - 5;
            square_wave(2000, 127);
        } else {
            // must be a block hit
            ball_dx = -ball_dx;
            appleii_vline(ball_x, ball_screen_y & 0xfe, (ball_screen_y & 0xfe) + 1);
            unsigned char block_value = ball_x / 2 - 9;
            player_score += block_value;
            appleii_vtab(20);
            *APPLEII_MONITOR_CH = 12;
            printf("%3d\n", player_score);
            square_wave(1000, 127 - block_value * 2);
            square_wave(1500, 110 - block_value * 2);
        }
    }
    
    appleii_plot(old_ball_x, old_ball_y / 3);
    appleii_setcol(BALL_COLOR);
    appleii_plot(ball_x, ball_y / 3);
}

void kill_ball() {
    square_wave(1200, 100);
    square_wave(1200, 70);
    square_wave(1200, 100);
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
    for (unsigned char i = 0; i <= 39; i++) {
        appleii_vline(i, 0, 39);
    }
    for (unsigned char i = 20; i <= 34; i += 2) {
        *APPLEII_MONITOR_CH = i + 1;
        printf("%d", i / 2 - 9);
        appleii_setcol(EVEN_BRICK_COLOR);
        appleii_vline(i, 0, 39);
        appleii_setcol(ODD_BRICK_COLOR);
        for (unsigned char j = i % 4; j <= 39; j += 4) {
            appleii_vline(i, j, j+1);
        }
    }
    *APPLEII_MONITOR_CH = 4;
    printf("SCORE =   0\n\n");
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
        if (time_until_ball_active > 0) {
            time_until_ball_active--;
        } else {
            time_until_ball_active = 3;
            update_ball();
        }
        wait_for_vblank();
    }
}

int main() {
    setup_text_mode();
    appleii_home();
    *APPLEII_MONITOR_CH = 9;
    appleii_vtab(4);
    printf("*** BREAKOUT ***\n\n");
    printf("  OBJECT IS TO DESTROY ALL BRICKS\n\n");
    // TODO: Allow getting player name (requires getline())
    printf("  PRESS KEY TO BEGIN");
    getchar();

    while (1) {
        // TODO: Allow setting custom colors (requires scanf())
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