/*
 * File      : pm_label.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <pm_widget.h>

enum AnimationEffect
{
    AnimationNone,
    AnimationFade,
    AnimationMoveUp,
    AnimationMoveDown,
    AnimationMoveLeft,
    AnimationMoveRight,
};

namespace Persimmon
{

class Label : public Widget
{
public:
    Label(char* label);
    Label(char* label, const Rect& rect);
    Label(const char *label, struct rtgui_font* font);
    Label(const char *label, struct rtgui_font* font, const Rect& rect);
    virtual ~Label();

    void setLabel(char* label);
    void setLabel(int number);
    void setLabel(const char* fmt, ...);

    char* getLabel(void);
    void clearLabel(void)
    {
        if (label != RT_NULL) rt_free(label);

        label = RT_NULL;
    }

    void setAnimType(enum AnimationEffect type)
    {
        this->animType = type;
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    /* update label display with animation */
    void update(char* label);
    struct rtgui_dc *getLabelDC(char* label);

private:
    char *label;

    AnimationEffect animType;
};

}

