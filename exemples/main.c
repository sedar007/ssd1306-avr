#include <stdint.h>
#include "../include/ssd1306.h"
#include "../include/ssd1306_text.h"
#include <util/delay.h>
#include <avr/io.h>

#define LED4 PD4
#define LED5 PD5
#define LED6 PD6
#define LED7 PD7

#define BTN_UP PB4
#define BTN_UP2 PB6
#define BTN_DOWN PC6
#define BTN_DOWN2 PB5
#define BTN_SELECT PE6

#define DEBOUNCE_MS 5
#define WELCOME_DELAY 500
#define INIT_DELAY 1000
#define SELECTION_DELAY 2000

typedef enum {
    MENU_START = 0,
    MENU_INFOS = 1,
    MENU_EXIT = 2,
    MENU_COUNT = 3
} MenuOption;

void init_buttons(void) {
    DDRB &= ~((1 << BTN_UP) | (1 << BTN_UP2) | (1 << BTN_DOWN2));
    PORTB |= (1 << BTN_UP) | (1 << BTN_UP2) | (1 << BTN_DOWN2);

    DDRC &= ~(1 << BTN_DOWN);
    PORTC |= (1 << BTN_DOWN);

    DDRE &= ~(1 << BTN_SELECT);
    PORTE |= (1 << BTN_SELECT);

    DDRD |= (1 << LED4) | (1 << LED5) | (1 << LED6);
}

uint8_t button_debounce(uint8_t port_pin, volatile uint8_t *port_reg, uint8_t pin) {
    if (!((*port_reg) & (1 << pin))) {
        _delay_ms(DEBOUNCE_MS);
        if (!((*port_reg) & (1 << pin))) {
            while (!((*port_reg) & (1 << pin)));
            _delay_ms(DEBOUNCE_MS);
            return 1;
        }
    }
    return 0;
}

uint8_t button_up_pressed(void) {
    return button_debounce(BTN_UP, &PINB, BTN_UP) ||
           button_debounce(BTN_UP2, &PINB, BTN_UP2);
}

uint8_t button_down_pressed(void) {
    return button_debounce(BTN_DOWN, &PINC, BTN_DOWN) ||
           button_debounce(BTN_DOWN2, &PINB, BTN_DOWN2);
}

void display_menu(MenuOption selected) {
    ssd1306_clear_page(2);
    ssd1306_clear_page(4);
    ssd1306_clear_page(6);

    ssd1306_print_utf8_center(
        selected == MENU_START ? "> 1. Start <" : "  1. Start  ", 2);

    ssd1306_print_utf8_center(
        selected == MENU_INFOS ? "> 2. Infos <" : "  2. Infos  ", 4);

    ssd1306_print_utf8_center(
        selected == MENU_EXIT ? "> 3. Exit <" : "  3. Exit  ", 6);
}

void show_selection(MenuOption selected) {
    ssd1306_clear();

    const char *messages[] = {"Starting...", "Infos", "Goodbye!"};
    const uint8_t leds[] = {LED4, LED5, LED6};

    //ssd1306_print_utf8_center(messages[selected], 3);

    if (selected == MENU_INFOS) {
        ssd1306_print_utf8_center("uid: 04 A2 B3 C4", 2);
        ssd1306_print_utf8_center("type: MIFARE", 4);
        ssd1306_print_utf8_center("status: OK", 6);
    }
    else {
        ssd1306_print_utf8_center(messages[selected], 3);
    }

    PORTD |= (1 << leds[selected]);
    _delay_ms(SELECTION_DELAY);
    PORTD &= ~(1 << leds[selected]);
    ssd1306_clear();
}

void show_message(const char *msg) {
    ssd1306_clear();
    ssd1306_print_utf8_center(msg, 3);
}

int main(void) {
    MenuOption current_selection = MENU_START;

    init_buttons();
    ssd1306_init();

    show_message("Welcome!");
    _delay_ms(WELCOME_DELAY);

    show_message("Initialisation...");
    _delay_ms(INIT_DELAY);
    ssd1306_clear_page(3);

    display_menu(current_selection);

    while (1) {
        if (button_up_pressed()) {
            current_selection = (current_selection == 0)
                ? MENU_COUNT - 1 : current_selection - 1;
            display_menu(current_selection);
        }

        if (button_down_pressed()) {
            current_selection = (current_selection == MENU_COUNT - 1)
                ? 0 : current_selection + 1;
            display_menu(current_selection);
        }

        if (button_debounce(BTN_SELECT, &PINE, BTN_SELECT)) {
            show_selection(current_selection);
            display_menu(current_selection);
        }
    }

    return 0;
}
