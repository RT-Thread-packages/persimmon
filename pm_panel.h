/*
 * File      : pm_panel.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <pm_container.h>
#include <pm_image.h>

namespace Persimmon
{

class Panel : public Container
{
public:
    enum type
    {
        VERTICAL   = 1 << 0,
        HORIZONTAL = 1 << 1,
        LEFT = 1 << 2,
        TOP = 1 << 3,
    };
    DEFINE_CLASS_ENUM_FLAG_OPERATORS(type);

    Panel(const Rect rect, enum type tp = VERTICAL);
    virtual ~Panel();

    void setScrollbar(Image *yImg, Image *xImg);
    void addItem(Widget *w);
    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev,
                                    const struct rtgui_gesture *gest);

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

protected:
    void fixChildrenExtent(int xOffset, int yOffset);

    enum type mtype;

private:
    int yLastPosition, yFirstPosition;
    int xLastPosition, xFirstPosition;
    int yMovePitch, xMovePitch;

    Image *yImage, *xImage;
};

}

