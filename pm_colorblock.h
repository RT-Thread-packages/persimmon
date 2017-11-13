/*
* File      : pm_colorblock.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
*/
#pragma once

#include <pm_widget.h>
#include <pm_image.h>

namespace Persimmon
{

class ColorBlock : public Widget
{
public:
    ColorBlock(const Rect &rect, rtgui_color_t color);
    virtual ~ColorBlock();

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);
};

}
