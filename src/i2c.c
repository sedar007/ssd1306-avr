//
// Created by Adjy Sedar Desir on 25/10/2025.
//

#include "../include/i2c.h"
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>

void i2c_init(void) {
    TWBR = (uint8_t)TWBR_val;
}

void i2c_start_write(uint8_t address) {
    TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
    TWDR = (address << 1); // écriture
    TWCR = (1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
}

void i2c_stop(void) {
    TWCR = (1<<TWSTO)|(1<<TWEN)|(1<<TWINT);
    _delay_us(10);
}

void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
}
