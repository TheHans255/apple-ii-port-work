#include "apple-ii-io.h"
#include "apple-iie-io.h"
#include "sound.h"
#include "paddle.h"
#include "text-lores-io.h"

typedef unsigned short size_t;
int printf(const char *format, ...);
void *memcpy(void *dest, const void *src, size_t count);

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

void pick_colors();
void reset_round();
void update_paddle();
void update_ball();
void main_loop();
void kill_ball();
void end_game();

char player_name[16];

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
    text_set_window_left(0);
    text_set_window_width(40);
    text_set_window_top(0);
    text_set_window_bottom(24);
}

void setup_graphics_mode() {
    *APPLEII_MIXEDMODE_ON = 0;
    *APPLEII_HIRES_OFF = 0;
    *APPLEII_TEXTMODE_GRAPHICS = 0;
    text_set_window_left(0);
    text_set_window_width(40);
    text_set_window_top(20);
    text_set_window_bottom(24);
}

void wait_for_vblank() {
    while (*APPLEIIE_VBLANK >= 128);
    while (*APPLEIIE_VBLANK < 128);
}

void reset_round() {
    lores_set_color(BACKGROUND_COLOR);
    lores_plot(ball_x, ball_y / 3);
    ball_x = 19;
    ball_y = rand() % 120;
    ball_dx = -1;
    ball_dy = (rand() % 5) - 2;
    text_set_htab(5);
    text_set_vtab(21);
    if (balls_remaining > 1) {
        printf("%d BALLS LEFT\n", balls_remaining);
    } else {
        printf("LAST BALL, %s!\n", player_name);
    }
    time_until_ball_active = 60;
    ball_hits_in_round = 0;
}

void update_paddle() {
    signed int paddle_y_raw = ((signed int) paddle_read(0) - 20) / 6;
    if (paddle_y_raw < 0) paddle_y_raw = 0;
    if (paddle_y_raw > 34) paddle_y_raw = 34;
    paddle_y = (unsigned char) paddle_y_raw;

    lores_set_color(PADDLE_COLOR);
    lores_vline(0, paddle_y, paddle_y + 5);
    lores_set_color(BACKGROUND_COLOR);
    if (paddle_y > 0) {
        lores_vline(0, 0, paddle_y - 1);
    }
    if (paddle_y < 34) {
        lores_vline(0, paddle_y + 5, 39);
    }
}

void update_ball() {
    unsigned char old_ball_x = ball_x;
    unsigned char old_ball_y = ball_y;

    lores_set_color(BACKGROUND_COLOR);

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
        enum appleii_lores_color ball_pos_color = lores_scrn(ball_screen_x, ball_screen_y);
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
            lores_vline(ball_x, ball_screen_y & 0xfe, (ball_screen_y & 0xfe) + 1);
            unsigned char block_value = ball_x / 2 - 9;
            player_score += block_value;
            text_set_vtab(20);
            text_set_htab(12);
            printf("%3d\n", player_score);
            square_wave(1000, 127 - block_value * 2);
            square_wave(1500, 110 - block_value * 2);
        }
    }
    
    lores_plot(old_ball_x, old_ball_y / 3);
    lores_set_color(BALL_COLOR);
    lores_plot(ball_x, ball_y / 3);
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
    pick_colors();
    setup_graphics_mode();
    text_home();
    text_set_vtab(20);
    lores_set_color(BACKGROUND_COLOR);
    for (unsigned char i = 0; i <= 39; i++) {
        lores_vline(i, 0, 39);
    }
    for (unsigned char i = 20; i <= 34; i += 2) {
        text_set_htab(i + 1);
        printf("%d", i / 2 - 9);
        lores_set_color(EVEN_BRICK_COLOR);
        lores_vline(i, 0, 39);
        lores_set_color(ODD_BRICK_COLOR);
        for (unsigned char j = i % 4; j <= 39; j += 4) {
            lores_vline(i, j, j+1);
        }
    }
    text_set_htab(4);
    printf("SCORE =   0\n\n");
    text_set_window_top(21);

    player_score = 0;
    balls_remaining = 5;
    paddle_y = 0;
    ball_x = 10;
    ball_y = 10;
    reset_round();
    while (1) {
        if (balls_remaining <= 0) {
            printf("YOUR SCORE OF %d IS %s\n", player_score, SCORE_RATINGS[player_score / 100]);
            break;
        }
        if (player_score >= 720) {
            printf("CONGRATULATIONS, %s, YOU WIN!\n", player_name);
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

static enum appleii_lores_color pick_single_color() {
    int response;
    while (1) {
        printf(" COLOR (0 TO 15)");
        char buffer[4];
        unsigned char len = text_getln(buffer, 4);
        response = 0;
        for (unsigned char i = 0; i < len; i++) {
            unsigned char c = buffer[i];
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r') continue;
            if (c >= '0' && c <= '9') {
                response = response * 10 + (c - '0');
            } else {
                // illegal character found
                response = -1;
                break;
            }
        }
        if (response < 0 || response > 15) {
            printf("INVALID, REENTER");
        } else {
            break;
        }
    }
    return (enum appleii_lores_color) response;
}

void pick_colors() {
    printf("STANDARD COLORS, %s", player_name);
    printf("(Y/N)?");
    unsigned char standard_color_response = getchar();
    printf("\n");
    if (standard_color_response != 'N' && standard_color_response != 'n') {
        // use standard colors
        BACKGROUND_COLOR = LORES_MAGENTA;
        EVEN_BRICK_COLOR = LORES_YELLOW;
        ODD_BRICK_COLOR = LORES_ORANGE;
        PADDLE_COLOR = LORES_MEDIUM_BLUE;
        BALL_COLOR = LORES_WHITE;
        return;
    }
    // pick custom colors
    setup_graphics_mode();
    for (unsigned char i = 0; i <= 39; i++) {
        lores_set_color((enum appleii_lores_color) (i/2 * (i < 32)));
        lores_vline(i, 0, 39);
    }
    text_set_window_top(20);
    printf("\n\n\n");
    for (unsigned char i = 0; i <= 15; i++) {
        text_set_vtab(i % 2 + 20);
        text_set_htab(i * 2 + (i < 10));
        printf("%d", i);
    }
    text_set_window_top(22);
    text_set_vtab(23);
    printf("\n");
    printf("BACKGROUND");
    BACKGROUND_COLOR = pick_single_color();
    printf("EVEN BRICK");
    EVEN_BRICK_COLOR = pick_single_color();
    printf("ODD BRICK");
    ODD_BRICK_COLOR = pick_single_color();
    printf("PADDLE");
    PADDLE_COLOR = pick_single_color();
    printf("BALL");
    BALL_COLOR = pick_single_color();
}

int main() {
    setup_text_mode();
    text_home();
    text_set_htab(9);
    text_set_vtab(4);
    printf("*** BREAKOUT ***\n\n");
    printf("  OBJECT IS TO DESTROY ALL BRICKS\n\n");

    {
        printf("HI, WHAT'S YOUR NAME?");
        text_getln(player_name, 16);
    }

    while (1) {
        srand(1); // TODO: Get rand seed from getchar()
        main_loop();
        printf("ANOTHER GAME, %s? (Y/N)", player_name);
        unsigned char response = getchar();
        printf("\n");
        if (response != 'Y' && response != 'y') {
            break;
        }
    }

    setup_text_mode();
    text_home();
    printf("GAME OVER\n\n");
    return 0;
}