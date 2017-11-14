/*
 * ShadowWindow
 */

#pragma once

#include <pm_window.h>
#include <pm_container.h>

namespace Persimmon
{

class ShadowWin : public Window
{
public:
    ShadowWin(const Rect &rect);
    virtual ~ShadowWin();

    virtual void addChild(Widget* widget);
    virtual void removeChild(Widget* widget);

    virtual int show(rt_bool_t isModal = RT_FALSE);

    void setBackground(rtgui_color_t color);
    void setBackground(Image *image);
    void setShadowColor(rtgui_color_t color)
    {
        shadowColor = color;
    }

protected:
    Container *panel;
    rtgui_color_t shadowColor;
};

}
