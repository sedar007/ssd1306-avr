#include <stdint.h>
#include "../include/ssd1306.h"
#include "../include/ssd1306_text.h"
#include <util/delay.h>

int main(void) {
    ssd1306_init();
    ssd1306_clear();

    const char *text = "Hello everyone!";
    uint8_t page = 3;
   ssd1306_print_utf8_center(text, page);

    //ssd1306_clear();

    ssd1306_print_utf8_center("hola !!!!", 5);
    ssd1306_clear_page(4);

    ssd1306_print_utf8_center("hola 6!!!!", 6);
    _delay_ms(300);
    ssd1306_clear_page(6);

    for(;;) {}
    return 0;
}
