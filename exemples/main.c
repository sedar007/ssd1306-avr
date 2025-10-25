#include <stdint.h>
#include "../include/ssd1306.h"
#include "../include/ssd1306_text.h"
#include <util/delay.h>

int main(void) {
    ssd1306_init();
    ssd1306_clear();

    const char *text = "Hello everyone!"; // "Bonjour à tous!"
    uint8_t page = 3;


   ssd1306_print_utf8_center(text, page);


    for(;;) {}
    return 0;
}
