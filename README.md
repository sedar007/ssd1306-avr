# SSD1306 AVR Library

A lightweight and efficient C library for controlling SSD1306 OLED displays (128x64) on AVR microcontrollers via I2C communication.

## Features

- 🖥️ **I2C Communication**: Optimized I2C driver for SSD1306 displays
- 📝 **Text Rendering**: Built-in 5x7 pixel font with UTF-8 support
- 🌍 **Accented Characters**: Support for French accented characters (é, è, à, ô, ù, ç)
- 🎯 **Text Alignment**: Left-aligned, centered text rendering
- 📜 **Text Scrolling**: Horizontal scrolling support for long text
- 🔤 **Multi-line Support**: Automatic text wrapping and newline handling
- ⚡ **Lightweight**: Minimal memory footprint, optimized for AVR
- 🎨 **Display Control**: Clear screen, set cursor position, send raw data

## Hardware Requirements

- **Microcontroller**: AVR series (tested on ATmega32u4)
- **Display**: SSD1306 128x64 OLED display with I2C interface
- **Connections**:
  - SDA (I2C Data)
  - SCL (I2C Clock)
  - VCC (3.3V or 5V depending on your module)
  - GND

## Installation

### Clone the Repository

```bash
git clone https://github.com/sedar007/ssd1306-avr.git
cd ssd1306-avr
```

### Project Structure

```
ssd1306-avr/
├── include/          # Header files
│   ├── ssd1306.h        # Main SSD1306 display control
│   ├── ssd1306_text.h   # Text rendering functions
│   ├── i2c.h            # I2C communication
│   └── font5x7.h        # 5x7 pixel font
├── src/              # Source files
│   ├── ssd1306.c        # Display driver implementation
│   ├── ssd1306_text.c   # Text rendering implementation
│   ├── i2c.c            # I2C driver implementation
│   ├── font5x7.c        # Font data
│   └── fonts/           # Additional font resources
├── exemples/         # Example programs
│   ├── main.c           # Usage example
│   └── Makefile         # Build configuration
└── LICENSE           # MIT License

```

## Usage

### Basic Example

```c
#include <stdint.h>
#include "ssd1306.h"
#include "ssd1306_text.h"
#include <util/delay.h>

int main(void) {
    // Initialize the display
    ssd1306_init();
    ssd1306_clear();

    // Display centered text on page 3
    const char *text = "Hello everyone!";
    ssd1306_print_utf8_center(text, 3);

    // Main loop
    for(;;) {}
    return 0;
}
```

### Advanced Examples

#### Multi-line Text with Wrapping

```c
ssd1306_init();
ssd1306_clear();

const char *text = "This is a long text\nthat spans multiple lines";
ssd1306_print_utf8(text, 0, 0);
```

#### Scrolling Text

```c
uint16_t scroll_offset = 0;
while(1) {
    ssd1306_print_utf8_scroll("This is a scrolling message!", 2, 0, 128, scroll_offset);
    scroll_offset += 2;
    _delay_ms(100);
}
```

#### Text with Maximum Width

```c
ssd1306_print_utf8_with_max_width("Constrained text", 1, 10, 80);
```

#### UTF-8 Accented Characters

```c
ssd1306_print_utf8_center("Bonjour à tous!", 3);
ssd1306_print_utf8("Café, crêpe, ça va?", 4, 0);
```

## API Documentation

### Display Control Functions

#### `void ssd1306_init(void)`
Initializes the SSD1306 display and I2C communication.

#### `void ssd1306_clear(void)`
Clears the entire display (fills with zeros).

#### `void ssd1306_set_cursor(uint8_t page, uint8_t col)`
Sets the cursor position for the next write operation.
- `page`: Page number (0-7, each page is 8 pixels high)
- `col`: Column number (0-127)

#### `void ssd1306_send_command(uint8_t cmd)`
Sends a command byte to the display.

#### `void ssd1306_send_data_byte(uint8_t data)`
Sends a single data byte to the display.

#### `void ssd1306_send_data(const uint8_t *buf, size_t len)`
Sends a buffer of data bytes to the display.

### Text Rendering Functions

#### `void ssd1306_print_utf8(const char *s, uint8_t start_page, uint8_t start_col)`
Prints UTF-8 string starting at the specified position.
- `s`: UTF-8 encoded string
- `start_page`: Starting page (0-7)
- `start_col`: Starting column (0-127)

#### `void ssd1306_print_utf8_center(const char *s, uint8_t page)`
Prints UTF-8 string centered horizontally on the specified page.
- `s`: UTF-8 encoded string
- `page`: Page number (0-7)

#### `void ssd1306_print_utf8_with_max_width(const char *s, uint8_t start_page, uint8_t start_col, uint8_t max_width_px)`
Prints UTF-8 string with automatic wrapping at the specified width.
- `max_width_px`: Maximum width in pixels

#### `void ssd1306_print_utf8_scroll(const char *s, uint8_t page, uint8_t start_col, uint8_t max_width_px, uint16_t scroll_offset)`
Prints UTF-8 string with horizontal scrolling.
- `scroll_offset`: Number of pixels to scroll left

#### `void ssd1306_putc(char c, uint8_t page, uint8_t col)`
Prints a single character at the specified position.

#### `uint16_t measure_string_px(const char *s)`
Measures the width of a string in pixels.

### I2C Functions

#### `void i2c_init(void)`
Initializes the I2C peripheral.

#### `void i2c_start_write(uint8_t address7)`
Starts I2C communication with the specified 7-bit address.

#### `void i2c_write(uint8_t data)`
Writes a byte via I2C.

#### `void i2c_stop(void)`
Stops I2C communication.

## Building and Flashing

### Configuration

Edit the Makefile in the `exemples/` directory to match your hardware:

```makefile
MCU = atmega32u4          # Your microcontroller
FCPU = 16000000          # CPU frequency in Hz
PROGRAMMER = dfu-programmer  # Your programmer tool
```

### Build Commands

```bash
cd exemples/

# Compile the project
make

# Check binary size
make size

# Upload to microcontroller
make upload

# Clean build files
make clean
```

### Custom F_CPU

You can override the CPU frequency during compilation:

```bash
make FCPU=8000000
```

## Configuration Options

### I2C Speed

By default, the I2C bus runs at 100kHz. To change it, define `F_SCL` before including `i2c.h`:

```c
#define F_SCL 400000UL  // 400kHz Fast Mode
#include "i2c.h"
```

### Display Address

The default I2C address is `0x3C`. To change it, modify `SSD1306_I2C_ADDR` in `ssd1306.h`:

```c
#define SSD1306_I2C_ADDR 0x3D  // Alternative address
```

### Display Dimensions

The library is configured for 128x64 displays. For other sizes, modify in `ssd1306.h`:

```c
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
```

## Supported Characters

- **ASCII**: Full printable ASCII range (32-126)
- **French Accents**: é, è, à, ô, ù, ç
- **Font**: 5x7 pixel monospace with 1px spacing between characters

## Memory Usage

The library is optimized for low memory usage:
- Font data: ~475 bytes (ASCII) + ~30 bytes (accents)
- Code size: ~800 bytes (core functions)
- RAM usage: Minimal (no frame buffer)

## Examples

Check the `exemples/` directory for complete working examples:
- **main.c**: Basic centered text display

## Troubleshooting

### Display Not Working

1. **Check connections**: Verify SDA, SCL, VCC, and GND are correctly connected
2. **I2C address**: Try alternative address `0x3D` if `0x3C` doesn't work
3. **Pull-up resistors**: Ensure I2C lines have 4.7kΩ pull-up resistors
4. **Power supply**: Verify the display has adequate power (3.3V or 5V)

### Garbled Text

1. **F_CPU**: Ensure F_CPU is correctly defined for your clock speed
2. **I2C speed**: Try reducing F_SCL to 100kHz
3. **Timing**: Add delays between operations if needed

### Compilation Errors

1. **F_CPU warning**: Define F_CPU in Makefile or as compiler flag: `-DF_CPU=16000000UL`
2. **avr-gcc not found**: Install AVR toolchain: `sudo apt-get install gcc-avr avr-libc`

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

**Adjy Sedar Desir** ([@sedar007](https://github.com/sedar007))

## Acknowledgments

- Font based on standard 5x7 monospace bitmap font
- SSD1306 datasheet and initialization sequence
- AVR community for I2C implementation examples

## Version History

- **1.0.0** (2025-10-25): Initial release
  - Basic display control
  - Text rendering with UTF-8 support
  - French accented characters
  - Scrolling and text alignment

---

Made with ❤️ for the AVR community