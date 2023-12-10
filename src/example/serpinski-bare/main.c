#include "apple-ii-io.h"

int rand(void);
void srand(unsigned int seed);
void hires_clear();
void hires_plot_on(unsigned int x, unsigned int y);

int main() {
    srand(1);
    hires_clear();
    *APPLEII_HIRES_ON = 0;
    *APPLEII_MIXEDMODE_OFF = 0;
    *APPLEII_PAGE_PAGE2 = 0;
    *APPLEII_TEXTMODE_GRAPHICS = 0;
    unsigned int sx = rand() % 280;
    unsigned int sy = rand() % 192;
    while (1) {
        unsigned char attractor = rand() % 3;
        unsigned int ax, ay;
        switch(attractor) {
            case 0:
                ax = 0;
                ay = 192;
                break;
            case 1:
                ax = 280;
                ay = 192;
                break;
            case 2:
                ax = 140;
                ay = 0;
                break;
        }
        sx = (sx + ax) / 2;
        sy = (sy + ay) / 2;
        hires_plot_on(sx, sy);
    }
}