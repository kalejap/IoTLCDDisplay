/*
  IoTLCDDisplay.h - IoTTextDisplay implementation for LiquidCrystal_I2C displays.
  Copyright (c) 2024 Peter Kaleja.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <LiquidCrystal_I2C.h>
#include "IoTTextDisplay.h"

/**
 * @brief IoTTextDisplay adapter for LiquidCrystal_I2C (I2C character LCD).
 *
 * Wraps a LiquidCrystal_I2C instance and exposes the IoTTextDisplay interface.
 * Use lcd() for any LCD-specific features not covered by IoTTextDisplay.
 */
class IoTLCDDisplay : public IoTTextDisplay
{
public:
    /**
     * @param address  I2C address of the LCD backpack (typically 0x27 or 0x3F)
     * @param cols     Number of character columns (e.g. 16)
     * @param rows     Number of character rows (e.g. 2)
     */
    IoTLCDDisplay(uint8_t address, uint8_t cols, uint8_t rows);

    void begin() override;
    void clear() override;
    uint8_t cols() const override { return _cols; }
    uint8_t rows() const override { return _rows; }
    void setCursor(uint8_t col, uint8_t row) override;
    using IoTTextDisplay::print;  // un-hide base convenience overloads (e.g. print(String))
    void print(const char* text) override;
    void print(const __FlashStringHelper* text) override;
    void print(int value) override;
    void print(float value, uint8_t decimals = 1) override;
    void setBacklight(bool on) override;
    void createChar(uint8_t index, const uint8_t charmap[8]) override;
    void writeChar(uint8_t index) override;

    /**
     * @brief Direct access to the underlying LiquidCrystal_I2C for features
     *        not covered by IoTTextDisplay (e.g. custom blink modes, OLED variant).
     */
    LiquidCrystal_I2C& lcd() { return _lcd; }

private:
    LiquidCrystal_I2C _lcd;
    uint8_t _cols;
    uint8_t _rows;
};
