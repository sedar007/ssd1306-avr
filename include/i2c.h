//
// Created by Adjy Sedar Desir on 25/10/2025.
//



#ifndef SSD1306_AVR_I2C_H
#define SSD1306_AVR_I2C_H

#include <stdint.h>
#ifndef F_SCL
#define F_SCL 100000UL
#endif

#ifndef F_CPU
#warning "F_CPU should be defined by the build system (e.g. -DF_CPU=16000000UL)"
#endif

#define TWBR_val ((((F_CPU / F_SCL) - 16 ) / 2 ))

void i2c_init(void);
void i2c_start_write(uint8_t address7);
void i2c_write(uint8_t data);
void i2c_stop(void);

#endif //SSD1306_AVR_I2C_H
