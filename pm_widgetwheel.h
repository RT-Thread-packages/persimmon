/*
 * File      : pm_widgetwheel.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <vector>

#include <pm_container.h>
#include <sigslot.h>
#include <pm_timer.h>

namespace Persimmon
{

class WidgetWheel : public Container
{
public:
    enum type
    {
        HORIZONTAL  = 1 << 0,
        VERTICAL    = 1 << 1,
        CYCLE       = 1 << 2,
    };
    DEFINE_CLASS_ENUM_FLAG_OPERATORS(type);

    WidgetWheel(const Rect& rect, int norSize, int selSize);
    virtual ~WidgetWheel();

    void addItem(Widget* widget);
    void emptyItem(void);

    void setSlideType(enum type tp = HORIZONTAL)
    {
        mtype = tp;
    }

    void fixItemExtent(int itemNum, bool ref);

    int getSelItemNum(void)
    {
        return selItemNum;
    }

    Widget* getSelItem(void)
    {
        return item[selItemNum];
    }

    Widget* getItem(int value)
    {
        if (value < 0 || value >= item.size())
            return RT_NULL;

        return item[value];
    }

    void setAdjustSpeed(int value)    //调整滑动手势结束后，控件继续滑动的速度，即距离
    {
        if (value >= 0)
            adjustSpeed = value;
    }

    void animationEnable(bool enable = true)
    {
        animEnable = enable;
    }

    void tapSelEnable(bool enable = true)
    {
        tapEnable = enable;
    }

    Signal<int> clicked;

    virtual void act(int itemNum, int progress);
    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev, const struct rtgui_gesture *gest);

protected:
    std::vector<Widget*> item;
    std::vector<int> item_num;
    int norExtentSize;
    enum type mtype;                //滑动类型 水平或垂直

private:
    void moveItem(bool ref);
    void filterSelItem(void);       //筛选出当前选中项

    void animationStart(void);      //开始动画
    void onAnimation(void);         //动画刷新

    int selItemNum, oldSelItemNum, selExtentSize;
    int itemMovePitch, oldPitch, adjustSpeed;

    Timer *animationTimer;         //动画效果使用的定时器
    bool animationMoving, animEnable, tapEnable;  //true 则为动画进行时  false 则否
    int animationMovePitch, _progress;      //分别为未选中项和选中项动画需移动的总距离
    int animationPitch, animationProgress;  //分别为未选中项和选中项动画中当前移动的距离，以及 animationProgress 动画进度
};

}

