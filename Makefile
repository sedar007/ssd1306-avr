# Configuration
CC = avr-gcc
AR = avr-ar
MCU = atmega328p
F_CPU = 16000000UL
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

# Dossiers
SRC_DIR = src
INC_DIR = include
LIB_DIR = ssd1306-libs
I2C_SRC = libs/i2c/src
I2C_INC = libs/i2c/include

# Fichiers sources
SOURCES = $(SRC_DIR)/ssd1306.c $(SRC_DIR)/ssd1306_text.c $(SRC_DIR)/font5x7.c $(I2C_SRC)/i2c.c
OBJECTS = $(SOURCES:.c=.o)

# Cible de la bibliothèque
TARGET = $(LIB_DIR)/libssd1306.a

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(LIB_DIR)/include
	$(AR) rcs $@ $^
	cp $(INC_DIR)/*.h $(LIB_DIR)/include/
	@echo "Bibliothèque créée: $@"

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(I2C_INC) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf $(LIB_DIR)/include

install: $(TARGET)
	@echo "Bibliothèque prête dans $(LIB_DIR)/"
