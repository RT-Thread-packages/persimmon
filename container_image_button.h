/*
 * File      : container_image_button.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include "pm_container.h"

namespace Persimmon
{

class ContainerImageButton: public Container        //Derived from container, container button
{
public:
    ContainerImageButton(const Rect &rect);
    virtual ~ContainerImageButton();

    void setNorDc(struct rtgui_dc *nor)            //Setting the initial background
    {
        if (this->nor)
            rtgui_dc_destory(this->nor);
        this->nor = nor;
    }

    void setSelDc(struct rtgui_dc *sel)            //Setting press background
    {
        if (this->sel)
            rtgui_dc_destory(this->sel);
        this->sel = sel;
    }

    void setSelectDc(struct rtgui_dc *select)      //Pictures that are covered when pressed
    {
        if (this->select)
            rtgui_dc_destory(this->select);
        this->select = select;
    }

    Signal<void> clicked;           //Click event

    virtual bool handleGestureEvent(struct rtgui_event_gesture *, const struct rtgui_gesture *);    //Touch gesture event

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal)
    {
        if (nor && selectState == false)
        {
            setBack(nor);
        }

        if (sel && selectState)
        {
            setBack(sel);
        }

        Container::render(dc, dcPoint, srcRect, flags);

        if (select && selectState)
        {
            struct rtgui_point dc_point = { 0, 0 };
            Rect rect;

            /* get widget rect */
            rect = getRect();
            rect.move(dcPoint);

            select->engine->blit(select, &dc_point, dc, rect.getRect());
        }
    }

private:
    Widget* setBack(struct rtgui_dc* bg)
    {
        if (backgroundDc != nor && backgroundDc != sel)
            rtgui_dc_destory(backgroundDc);

        backgroundDc = bg;

        return this;
    }

    bool selectState;
    struct rtgui_dc *select;
    struct rtgui_dc *nor, *sel;
};

}
