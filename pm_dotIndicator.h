/*
* File      : pm_dotIndicator.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
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
        HORIZONTAL	= 0,
        VERTICAL	= 1,
    };

    DotIndicator(Image *norImg, Image *selImg, int num, int gap = 0);
    virtual ~DotIndicator();

    void setDirection(enum type t = HORIZONTAL)
    {
        direction = t;
    }

    void selectDotIndicator(int num)    /* 选中对应编号的点，起始值 0 */
    {
        if (num >= dotIndicatorNum || num < 0)
            return;

        dotIndicatorSelNum = num;
    }

    int getSelectNum(void)  /* 获取当前选中点编号 */
    {
        return dotIndicatorSelNum;
    }

    void setDotIndicatorNum(int num)   /* 设置总共有多少个点 */
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
