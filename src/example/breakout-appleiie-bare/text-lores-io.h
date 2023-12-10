#ifndef __TEXT_LORES_IO
#define __TEXT_LORES_IO

typedef unsigned short size_t;

void lores_set_color(enum appleii_lores_color color);
void lores_plot(unsigned char x, unsigned char y);
void lores_vline(unsigned char x, unsigned char y1, unsigned char y2);
void lores_hline(unsigned char x1, unsigned char x2, unsigned char y);
enum appleii_lores_color lores_scrn(unsigned char x, unsigned char y);

void text_set_htab(unsigned char x);
void text_set_vtab(unsigned char y);
void text_set_window_left(unsigned char left);
void text_set_window_width(unsigned char width);
void text_set_window_top(unsigned char top);
void text_set_window_bottom(unsigned char bottom);
void text_home();

size_t text_getln(char *buffer, size_t buffer_len);

int getchar();
void __putchar(char c);

#endif // __TEXT_LORES_IO