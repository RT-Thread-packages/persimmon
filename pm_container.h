/*
 * File      : pm_container.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <pm_widget.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/container.h>
#include "sigslot.h"
#include <vector>

namespace Persimmon
{

class Container : public Widget
{
    typedef Widget super;

public:
    Container();
    Container(const rtgui_type_t* type);
    Container(const Rect &rect);
    virtual ~Container();

    virtual void addChild(Widget* widget);
    virtual void removeChild(Widget* widget);

    int getChildIndex(Widget* widget);

    void empty();

    void saveClip(struct rtgui_region &region);
    void restoreClip(struct rtgui_region &region);

    virtual void setRect(const Rect &rect);
    void setBox(struct rtgui_box *box);
    void layout();

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);
    virtual rt_bool_t eventHandler(struct rtgui_event *event);

    virtual Widget* getMouseOwner(int x, int y);

protected:
    /* C++ children object under this window */
    std::vector<Widget*> children;

    void handleEventInChildren(struct rtgui_event *event);
};

class TapContainer: public Container
{
public:
    TapContainer(const Rect &rect, int value = 0);
    virtual ~TapContainer() {}

    Signal<int> touch;

    virtual bool handleGestureEvent(struct rtgui_event_gesture *, const struct rtgui_gesture *);

private:
    int baseValue;
};

}


