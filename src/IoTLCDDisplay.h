/*
  IoTLCDDisplay.h - IoTTextDisplay adapter for LiquidCrystal_I2C displays.
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
#include <IoTLCDDisplayT.h>

/**
 * @brief IoTLCDDriverTraits specialisation for LiquidCrystal_I2C.
 *
 * LiquidCrystal_I2C uses init() (which calls Wire.begin() internally)
 * instead of begin(cols, rows), and exposes backlight control.
 * This specialisation must be defined before IoTLCDDisplay is instantiated.
 */
template<>
struct IoTLCDDriverTraits<LiquidCrystal_I2C>
{
    static void begin(LiquidCrystal_I2C& lcd, uint8_t /*cols*/, uint8_t /*rows*/)
    {
        lcd.init();
        lcd.backlight();
    }

    static void setBacklight(LiquidCrystal_I2C& lcd, bool on)
    {
        if (on)
        {
            lcd.backlight();
        }
        else
        {
            lcd.noBacklight();
        }
    }
};

/**
 * @brief IoTTextDisplay adapter for LiquidCrystal_I2C (I2C character LCD).
 *
 * Drop-in replacement for the previous concrete IoTLCDDisplay class.
 * Use lcd() for any LCD-specific features not covered by IoTTextDisplay.
 */
using IoTLCDDisplay = IoTLCDDisplayT<LiquidCrystal_I2C>;
