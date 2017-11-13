/*
* File      : pm_progressbar.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
*/
#pragma once

#include <pm_widget.h>
#include <pm_image.h>
#include <sigslot.h>

namespace Persimmon
{

class ProgressBar : public Widget
{
public:
    enum type
    {
        HORIZONTAL	= 0,
        VERTICAL	= 1,
    };

    ProgressBar(Image *norImg, Image *barImg, Image *sliderImg);
    virtual ~ProgressBar();

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
		if (value > maxValue)
			currentValue = maxValue;
		else if (value < minValue)
			currentValue = minValue;
		else
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
