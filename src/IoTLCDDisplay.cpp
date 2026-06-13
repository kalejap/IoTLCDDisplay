/*
  IoTLCDDisplay.cpp - IoTTextDisplay implementation for LiquidCrystal_I2C displays.
  Copyright (c) 2024 Peter Kaleja.  All right reserved.

  See IoTLCDDisplay.h for license.
*/

#include "IoTLCDDisplay.h"

IoTLCDDisplay::IoTLCDDisplay(uint8_t address, uint8_t cols, uint8_t rows)
    : _lcd(address, cols, rows), _cols(cols), _rows(rows)
{
}

void IoTLCDDisplay::begin()
{
    _lcd.init();
    _lcd.backlight();
}

void IoTLCDDisplay::clear()
{
    _lcd.clear();
}

void IoTLCDDisplay::setCursor(uint8_t col, uint8_t row)
{
    _lcd.setCursor(col, row);
}

void IoTLCDDisplay::print(const char* text)
{
    _lcd.print(text);
}

void IoTLCDDisplay::print(const __FlashStringHelper* text)
{
    _lcd.print(text);
}

void IoTLCDDisplay::print(int value)
{
    _lcd.print(value);
}

void IoTLCDDisplay::print(float value, uint8_t decimals)
{
    _lcd.print(value, (int)decimals);
}

void IoTLCDDisplay::setBacklight(bool on)
{
    if (on) _lcd.backlight();
    else    _lcd.noBacklight();
}

void IoTLCDDisplay::createChar(uint8_t index, const uint8_t charmap[8])
{
    // LiquidCrystal_I2C::createChar takes a non-const pointer; cast is safe
    // since the underlying implementation only reads the array.
    _lcd.createChar(index, const_cast<uint8_t*>(charmap));
}

void IoTLCDDisplay::writeChar(uint8_t index)
{
    _lcd.write(index);
}
