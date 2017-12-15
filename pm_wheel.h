/*
* File      : pm_wheel.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
*/
#ifndef PM_WHEEL_H__
#define PM_WHEEL_H__

#include <vector>
#include <pm_container.h>
#include <sigslot.h>
#include <pm_timer.h>

namespace Persimmon
{

class Wheel : public Container
{
public:
    enum type
    {
        VERTICAL = 0,
        HORIZONTAL = 1,
    };

    Wheel(const Rect& rect, enum type tp = HORIZONTAL);
    virtual ~Wheel();

    void fixSelItem(void);
    void fixItemPtich(void);

    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev, const struct rtgui_gesture *gest);
    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(), const Rect &srcRect = Rect(), RenderFlag flags = DrawNormal);

    virtual void act(int num)
    {
        rt_kprintf(" act num : %d\n", num);
    }

    virtual void end(int num)
    {
        rt_kprintf(" end num : %d\n", num);
    }

    void setShowSize(int normal, int center = 0)
    {
        normalSize = normal;
        centerSize = normal > center ? normal : center;
    }

    void setShowItems(int items)
    {
        showItems = items;
    }

    void setItemSize(int size)
    {
        itemSize = size;
    }

    int getCenterSelNum(void)
    {
        return centerSelNum;
    }

protected:
    void onAnimation(void);
    void stopAnimation(void);

    enum type mtype;
    int movePitch, gestPitch;
    int centerSelNum;

    int normalSize, centerSize, showItems, itemSize;
    int firstItemPitch, firstItemNum, itemMovePitch;
    int centerNum, oldNum;

    Timer *animTimer;
    int animMovePitch, animMoveProgress;
    bool isFirstRender, isAnim, isStopAnim;
};

class xxWheel : public Wheel
{
public:
    xxWheel(const Rect& rect);
    virtual ~xxWheel();

    void addImg(Image *img, int size = 0);

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
        const Rect &srcRect = Rect(),
        RenderFlag flags = DrawNormal);

    void setCoverSize(int size)
    {
        coverSize = size;
    }

    void setReductionSize(int size)
    {
        reductionSize = size;
    }

protected:
    std::vector<Image *> image[5];

private:
    int getCorrectPitch(int num, int pitch)
    {
        int i, totalPitch = 0;

        for (i = 1; i < num; i++)
        {
            totalPitch += pitch * i;
        }

        totalPitch += pitch * num / 2;

        return totalPitch;
    }

    int reductionSize, coverSize;
};

}
#endif

