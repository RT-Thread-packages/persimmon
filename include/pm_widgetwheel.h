/*
* File      : pm_widgetwheel.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
*/
#ifndef PM_WIDGETWHEEL_H__
#define PM_WIDGETWHEEL_H__

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
		HORIZONTAL	= 1 << 0,
        VERTICAL	= 1 << 1,
        CYCLE		= 1 << 2,
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

    void setAdjustSpeed(int value)	//�����������ƽ����󣬿ؼ������������ٶȣ�������
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
    enum type mtype;			       	//�������� ˮƽ��ֱ

private:
    void moveItem(bool ref);
    void filterSelItem(void);		    //ɸѡ����ǰѡ����

    void animationStart(void);		   	//��ʼ����
    void onAnimation(void);			    //����ˢ��

    int selItemNum, oldSelItemNum, selExtentSize;
    int itemMovePitch, oldPitch, adjustSpeed;

    Timer *animationTimer;		//����Ч��ʹ�õĶ�ʱ��
    bool animationMoving, animEnable, tapEnable;		//true ��Ϊ��������ʱ  false ���
    int animationMovePitch, _progress;	   	//�ֱ�Ϊδѡ�����ѡ��������ƶ����ܾ���
    int animationPitch, animationProgress;	//�ֱ�Ϊδѡ�����ѡ������е�ǰ�ƶ��ľ��룬�Լ� animationProgress ��������
};

}
#endif

