/*
 * File      : pm_dotIndicator.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <pm_widget.h>
#include <pm_image.h>

namespace Persimmon
{

class DotIndicator : public Widget
{
public:
    enum type
    {
        HORIZONTAL  = 0,
        VERTICAL    = 1,
    };

    DotIndicator(Image *norImg, Image *selImg, int num, int gap = 0);
    virtual ~DotIndicator();

    void setDirection(enum type t = HORIZONTAL)
    {
        direction = t;
    }

    void selectDotIndicator(int num)
    {
        if (num >= dotIndicatorNum || num < 0)
            return;

        dotIndicatorSelNum = num;
    }

    int getSelectNum(void)
    {
        return dotIndicatorSelNum;
    }

    void setDotIndicatorNum(int num)
    {
        dotIndicatorNum = num;
    }

    void setDotIndicatorGap(int gap)
    {
        dotIndicatorGap = gap;
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    enum type direction;
    Image *norImage, *selImage;
    int dotIndicatorNum, dotIndicatorSelNum, dotIndicatorGap;
};

}
