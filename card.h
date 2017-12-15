/*
 * File      : card.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <vector>
#include <pm_widget.h>
#include <pm_image.h>
#include <pm_container.h>
#include <sigslot.h>

namespace Persimmon
{

class Card : public Container
{
    typedef Container super;

public:
    enum type
    {
        VERTICAL   = 0,
        HORIZONTAL = 1 << 0,
        CYCLE      = 1 << 1,
    };
    DEFINE_CLASS_ENUM_FLAG_OPERATORS(type);

    Card (const Rect& rect, enum type tp = HORIZONTAL);
    Card (Image *dot_nor, Image *dot_sel, const Rect& rect, enum type tp = HORIZONTAL);
    virtual ~Card();

    virtual void addChild(Widget* widget);
    virtual void removeChild(Widget* widget);

    void setDotIndicator(Image *dot_nor, Image *dot_sel)
    {
        if (this->dot_nor)
            delete this->dot_nor;

        if (this->dot_sel)
            delete this->dot_sel;

        this->dot_nor = dot_nor;
        this->dot_sel = dot_sel;
    }

    void nextCardPage(void)
    {
        changeCardPage(currentIndex + 1);
    }

    void prevCardPage(void)
    {
        changeCardPage(currentIndex - 1);
    }

    void selectCardPage(int index)
    {
        /* set currentIndex */
        if (index < 0 || index >= children.size())
            return;
        children[currentIndex]->hide();
        currentIndex = index;
        children[currentIndex]->show();
    }

    int getCurrentCardPage()
    {
        return currentIndex;
    }
    int pageCount(void)
    {
        return children.size();
    }
    void setActiveValue(unsigned int value)
    {
        activeValue = value;
    }
    void setMinMovePitch(unsigned int value)
    {
        minMovePitch = value;
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);
    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev,
                                    const struct rtgui_gesture *gest);

    virtual Widget* getMouseOwner(int x, int y);

    Signal<int> changed;
    Signal<void> moving;

protected:
    enum type mtype;

    int currentIndex, old_pitch;
    struct rtgui_dc *mvdc;
    bool old_mvnext, is_moveing, is_boundary;

    Image *dot_nor, *dot_sel;

private:
    void changeCardPage(int index);
    void moveCard(struct rtgui_event_gesture* event, const struct rtgui_gesture *gesture);
    struct rtgui_dc* getAnimationDC(bool left);
    struct rtgui_dc* getAnimationDC(int first, int last);
    void renderIndicator(struct rtgui_dc *dc, const Point &point);

    unsigned int activeValue, minMovePitch;
};

}

