/*
* File      : pm_label.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2017 RT-Thread Develop Team
*/
#pragma once

#include <pm_widget.h>

namespace Persimmon
{

class Label : public Widget
{
public:
    Label(const char* label);
    Label(const char* label, const Rect& rect);
    Label(const char *label, struct rtgui_font* font);
    Label(const char *label, struct rtgui_font* font, const Rect& rect);
    virtual ~Label();

    void setLabel(const char* label);
    void setLabel(int number);
    void setLabel(char* fmt, ...);

    char* getLabel(void);
	void clearLabel(void);

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    char *label;
};

}
