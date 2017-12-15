/*
 * File      : pm_listctrl.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <vector>
#include <pm_widget.h>

#include <pm_animation.h>

namespace Persimmon
{

class ListCtrlAnimator;

class ListCtrl : public Widget
{
    typedef Widget super;

public:
    enum type
    {
        VERTICAL    = 0,
        HORIZONTAL  = 1 << 0,
        CYCLE       = 1 << 1,
        SNAP_CENTER = 1 << 2,
        BUFFERED    = 1 << 3,
    };
    DEFINE_CLASS_ENUM_FLAG_OPERATORS(type);

    ListCtrl(const Rect& rect,
             int itemSize = 25,
             enum type tp = VERTICAL);

    virtual ~ListCtrl();

    void empty();

    void addItem(Widget* widget);
    void addItem(int index, Widget* widget);
    void removeItem(Widget* widget);

    void setItemHeight(int height)
    {
        itemSize = height;
    }

    virtual rt_bool_t eventHandler(struct rtgui_event *event);

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);
    virtual void drawBackGround(struct rtgui_dc* dc, const Point &point);

    virtual Widget* getMouseOwner(int x, int y);

    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev,
                                    const struct rtgui_gesture *gest);

    Widget* getCenterWidget(void);
    void    setCenterIndex(unsigned int i);

    void invalidateBuffer(Widget *w);

protected:
    /* C++ children object under this window */
    std::vector<Widget*> children;
    std::vector<struct rtgui_dc*> buffer;

    virtual void animationMoveTo(int oldPos, int newPos);

    friend class ListCtrlAnimator;

    virtual void drawItems(struct rtgui_dc* dc, const Point &point, int offset);

    void drawScrollbar(void);

    int getItemIndexAt(int x, int y);

    int firstPosition;
    int beginItemIndex;
    int currentItemIndex;
    int itemSize;
    enum type mtype;

    void fixChildrenExtent(void);
    void hideChildren(void);

    struct rtgui_dc* getItemBuffer(void);
private:
    int lastOffset;
    void _doDrawItems(struct rtgui_dc *dc, int idx, const Point &pos);
};

class ListCtrlAnimator: public AnimAbstractAnimator
{
    typedef AnimAbstractAnimator super;

public:
    ListCtrlAnimator(ListCtrl &pl, int oldPos, int newPos);
    virtual ~ListCtrlAnimator() {}

    virtual void act(struct rtgui_dc* dest_dc, int progress);

private:
    const int oldPos, newPos;
};

}

