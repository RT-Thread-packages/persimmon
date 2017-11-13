/*
* File      : container_image_button.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2017 RT-Thread Develop Team
*/
#pragma once

#include "pm_container.h"

namespace Persimmon
{

class ContainerImageButton: public Container		//从容器派生，容器按钮
{
public:
    ContainerImageButton(const Rect &rect);		//构造函数，参数坐标范围
    virtual ~ContainerImageButton();

    void setNorDc(struct rtgui_dc *nor)		//设置控件初始背景，参数图片dc
    {
		if (this->nor)
			rtgui_dc_destory(this->nor);
		this->nor = nor;
    }

    void setSelDc(struct rtgui_dc *sel)		//设置控件按下时背景，参数图片dc
    {
		if (this->sel)
			rtgui_dc_destory(this->sel);
		this->sel = sel;
    }

    void setSelectDc(struct rtgui_dc *select)	//设置控件按下时覆盖，参数图片dc
    {
		if (this->select)
			rtgui_dc_destory(this->select);
		this->select = select;
    }

    Signal<void> clicked;	//点击事件

    virtual bool handleGestureEvent(struct rtgui_event_gesture *, const struct rtgui_gesture *);	//触摸手势事件处理函数

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
