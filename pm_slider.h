/*
* File      : pm_slider.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
*/
#pragma once

#include <pm_widget.h>
#include <pm_image.h>
#include <sigslot.h>

namespace Persimmon
{

class Slider : public Widget
{
public:
    enum type
    {
        HORIZONTAL	= 0,
        VERTICAL	= 1,
    };

    Slider(Image *norImg, Image *barImg, Image *sliderImg);
    virtual ~Slider();

    void setDirection(enum type t = HORIZONTAL)
    {
        direction = t;
    }

    void setValueLimits(int min, int max)
    {
        minValue = min;
        maxValue = max;
    }

    void setCurrentValue(int value)
    {
        currentValue = value;
    }

    int getCurrentValue(void)
    {
        return currentValue;
    }

    void setNorImg(Image *img)
    {
        if (norImage)
        {
            delete norImage;
        }
        norImage = img;
    }

    void setBarImg(Image *img)
    {
        if (barImage)
        {
            delete barImage;
        }
        barImage = img;
    }

    void setSliderImg(Image *img)
    {
        if (sliderImage)
        {
            delete sliderImage;
        }
        sliderImage = img;
    }

    void enableGesture(bool ges = true)
    {
		if (ges)
			setInterestGesture(RTGUI_GESTURE_DRAG | RTGUI_GESTURE_TAP);
		else
			setInterestGesture(RTGUI_GESTURE_NONE);
    }

    Signal<int> clicked;

    virtual bool handleGestureEvent(struct rtgui_event_gesture *, const struct rtgui_gesture *);	//触摸手势事件处理函数
    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    enum type direction;
    Image *norImage, *barImage, *sliderImage;
    int progress, baseProgress;
    int minValue, maxValue, currentValue;
};

}
