# IoTLCDDisplay

Arduino library that adapts [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C) to the `IoTTextDisplay` interface, providing a consistent API for I2C character LCD displays (16×2, 20×4, etc.).

## Features

- Implements the `IoTTextDisplay` interface for display-agnostic code
- Text output for `const char*`, `String`, `__FlashStringHelper*` (PROGMEM), `int`, and `float`
- Cursor positioning and display clear
- Backlight on/off control
- Custom character creation and rendering (up to 8 CGRAM slots)
- Direct access to the underlying `LiquidCrystal_I2C` instance for advanced features
- Works with any I2C LCD backpack at any address (typically `0x27` or `0x3F`)

## Dependencies

- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- `IoTTextDisplay` base class (from the IoT framework library)

## Installation

Clone or copy this repository into your Arduino `libraries/` folder or your PlatformIO `lib/` directory:

```bash
git clone https://github.com/kalejap/IoTLCDDisplay
```

Or add to `platformio.ini`:

```ini
lib_deps =
    https://github.com/kalejap/IoTLCDDisplay
```

## Usage

```cpp
#include <IoTLCDDisplay.h>

// 16-column, 2-row LCD at I2C address 0x27
IoTLCDDisplay display(0x27, 16, 2);

void setup() {
    display.begin();              // init LCD and turn backlight on
    display.clear();
    display.setCursor(0, 0);
    display.print("Hello, World!");
    display.setCursor(0, 1);
    display.print(3.14f, 2);      // prints "3.14"
}

void loop() {
    // use display through IoTTextDisplay* for display-agnostic code
    IoTTextDisplay* d = &display;
    d->setCursor(0, 1);
    d->print(millis() / 1000);
    delay(1000);
}
```

### Custom Characters

```cpp
// Define a degree symbol (8 rows of 5 bits)
const uint8_t degreeChar[8] = {
    0b00110,
    0b01001,
    0b01001,
    0b00110,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};

display.createChar(0, degreeChar);   // store in CGRAM slot 0
display.setCursor(5, 0);
display.writeChar(0);                // write the custom glyph
```

## Class Reference

### `IoTLCDDisplay`

Constructed with the I2C address, column count, and row count of the display.

| Method | Description |
|---|---|
| `IoTLCDDisplay(address, cols, rows)` | Constructor — I2C address, number of columns, number of rows |
| `begin()` | Initialise the LCD and turn the backlight on |
| `clear()` | Clear the display and return cursor to home |
| `cols()` | Return the number of columns |
| `rows()` | Return the number of rows |
| `setCursor(col, row)` | Move cursor to the given column and row (0-indexed) |
| `print(text)` | Print a `const char*`, `String`, or PROGMEM string |
| `print(value)` | Print an `int` value |
| `print(value, decimals)` | Print a `float` with the given number of decimal places (default 1) |
| `setBacklight(on)` | Turn the backlight on (`true`) or off (`false`) |
| `createChar(index, charmap)` | Store a custom 5×8 character in CGRAM slot `index` (0–7) |
| `writeChar(index)` | Write the custom character stored in CGRAM slot `index` |
| `lcd()` | Return a reference to the underlying `LiquidCrystal_I2C` for advanced use |

## License

MIT License — Copyright (c) 2026 Peter Kaleja. See [LICENSE](LICENSE).
