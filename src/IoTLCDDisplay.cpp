/*
  IoTLCDDisplay.cpp - IoTTextDisplay implementation for LiquidCrystal_I2C displays.
  Copyright (c) 2024 Peter Kaleja.  All right reserved.

  See IoTLCDDisplay.h for license.
*/

#include "IoTLCDDisplay.h"
#include "LCDLanguageSupport.h"
#ifdef _IOT_REAL_TIME
#include <TimeLib.h>
#endif

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

void IoTLCDDisplay::onSystemEvent(const IoTSystemEvent& event)
{
    using T = IoTSystemEvent::Type;
    switch (event.type)
    {
        case T::OTA_START:
            _lastOtaPct = 0xFF;
            printLine(0, L_LCD_OTA_START_LINE1);
            printLine(1, L_LCD_OTA_START_LINE2);
            break;

        case T::OTA_PROGRESS:
        {
            uint8_t pct = (event.arg2 > 0)
                ? (uint8_t)((uint64_t)event.arg1 * 100 / event.arg2) : 0;
            if (_lastOtaPct == 0xFF || pct == 100 || pct >= _lastOtaPct + 20)
            {
                _lastOtaPct = pct;
                char buf[17];
                snprintf(buf, sizeof(buf), L_LCD_OTA_PROGRESS_FMT, pct);
                printLine(1, buf);
            }
            break;
        }

        case T::OTA_END:
            _lastOtaPct = 0xFF;
            printLine(0, event.flag ? L_LCD_OTA_END_OK : L_LCD_OTA_END_FAIL);
            printLine(1, "");
            break;

        case T::RESTARTING:
            printLine(0, L_LCD_RESTARTING);
            printLine(1, "");
            break;

        default:
            break;
    }
}

#ifdef _IOT_REAL_TIME
void IoTLCDDisplay::printDateTime()
{
    if (timeStatus() == timeNotSet)
    {
        printLine(0, "  --:--:--      ");
        printLine(1, "");
        return;
    }

    static const char* const kDayNames[] = { L_LCD_DAY_NAMES };
    time_t t = now();
    char line[17];

    snprintf(line, sizeof(line), "    %02d:%02d:%02d    ",
        hour(t), minute(t), second(t));
    printLine(0, line);

    snprintf(line, sizeof(line), "%s %02d.%02d.%04d",
        kDayNames[weekday(t) - 1], day(t), month(t), year(t));
    printLine(1, line);
}
#endif
