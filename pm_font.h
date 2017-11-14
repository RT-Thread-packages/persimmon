/*
 * File      : pm_font.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <rtgui/rtgui.h>
#include <rtgui/font.h>

namespace Persimmon
{

/**
 * Font class
 */
class Font
{
public:
    enum Weight
    {
        Light    = 25,
        Normal   = 50,
        DemiBold = 63,
        Bold     = 75,
        Black    = 87
    };

    enum Style
    {
        StyleNormal,
        StyleItalic,
        StyleOblique
    };

    Font(struct rtgui_font* font);
    ~Font();

    Rect getMetrics(const char* text);
    struct rtgui_font* getFont()
    {
        return font;
    }

private:
    struct rtgui_font* font;
};

/*
 * FreeType Font
 */
class FTFont : public Font
{
public:
    FTFont(const char* fontname, int size, int weight = Font::Normal, bool italic = false);
    ~FTFont();

private:
};

}

