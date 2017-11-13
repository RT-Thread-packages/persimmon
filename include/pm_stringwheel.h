/*
* File      : pm_stringwheel.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
*/
#ifndef PM_STRWHEEL_H__
#define PM_STRWHEEL_H__

#include <vector>
#include <pm_widget.h>
#include <sigslot.h>
#include <pm_timer.h>

namespace Persimmon
{

class StringWheel : public Widget
{
public:
    enum type
    {
        VERTICAL    = 0,
        HORIZONTAL  = 1 << 0,
        CYCLE       = 1 << 1,
    };
    DEFINE_CLASS_ENUM_FLAG_OPERATORS(type);

    StringWheel(const Rect& rect, int norSize, int selSize, enum type tp = HORIZONTAL);
    virtual ~StringWheel();

    Signal<int> clicked;

    void addStr(const char *text,const Rect& rect);
    void emptyStringWheel(void)
    {
        int size = str.size();

        for (int i = 0; i < size; i++)
        {
            if (str[i])
                rt_free(str[i]);
        }
        str.clear();
        extent.clear();

        number.clear();

        cycleEnable = 0;
        selItemNum = -1;
        currentItemNum = -1;
        itemMovePitch = 0;
        oldPitch = 0;
        _progress = 10;
    }

    void cycleMandatoryEnable(void)
    {
        int wWidth, size = str.size();

        cycleEnable = 1;
        mtype = mtype | CYCLE;

        if (mtype & HORIZONTAL)
        {
            wWidth = getRect().getWidth();
        }
        else
        {
            wWidth = getRect().getHeight();
        }

        do
        {
            cycleEnable ++;

            for (int i = 0; i < size; i++)
            {
                if (str[i])
                {
                    str.push_back(rt_strdup(str[i]));
                    extent.push_back(extent[i]);
                    number.push_back(str.size() - 1);
                }
            }
        }
        while(wWidth > selExtentSize + (str.size() - 2) * norExtentSize);
    }

    void setSlideType(enum type tp = HORIZONTAL)
    {
        mtype = tp;
    }

    void fixItemExtent(int itemNum, bool ref);

    int getSelItemNum(void)
    {
        return selItemNum;
    }

    void setAdjustSpeed(int value)	//调整滑动手势结束后，控件继续滑动的速度，即距离
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

    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev,
                                    const struct rtgui_gesture *gest);
    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

protected:
    std::vector<char *> str;
    std::vector<Rect> extent;
    std::vector<int> number;
    int norExtentSize, selExtentSize;
    int selItemNum, currentItemNum, selProgress;

private:
    void moveItem(bool ref);
    void filterSelItem(void);		    //筛选出当前选中项

    void animationStart(void);		   	//开始动画
    void onAnimation(void);			    //动画刷新

    enum type mtype;			       	//滑动类型 水平或垂直
    int cycleEnable;

    int itemMovePitch, oldPitch, adjustSpeed;

    Timer *animationTimer;		//动画效果使用的定时器
    bool animationMoving, animEnable, tapEnable;		//true 则为动画进行时  false 则否
    int animationMovePitch, _progress;	   	//分别为未选中项和选中项动画需移动的总距离
    int animationPitch, animationProgress;	//分别为未选中项和选中项动画中当前移动的距离，以及 animationProgress 动画进度
};



//class StringWheelOne : public StringWheel
//{
//public:
//    StringWheelOne(const Rect& rect, int norSize, int selSize, enum type tp = VERTICAL);
//    virtual ~StringWheelOne();

//    void setItemFontSizeBoundary(int max, int mini)
//    {
//        selItemFontSize = max;
//        norItemFontSize = mini;
//    }

//    void setItemFontColor(rtgui_color_t selColor, rtgui_color_t norColor)
//    {
//        selItemFontColor = selColor;
//        norItemFontColor = norColor;
//        setForeground(norColor);
//    }

//    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
//                        const Rect &srcRect = Rect(),
//                        RenderFlag flags = DrawNormal);

//private:
//    int norItemFontSize, selItemFontSize;
//    rtgui_color_t norItemFontColor, selItemFontColor;
//};



//class StringWheelTwo : public StringWheel
//{
//public:
//    StringWheelTwo(const Rect& rect, int norSize, int selSize, enum type tp = VERTICAL);
//    virtual ~StringWheelTwo();

//    void setItemFontSizeBoundary(int max, int mini)
//    {
//        selItemFontSize = max;
//        norItemFontSize = mini;
//    }

//    void setImage(Image *img, Point point, const Rect& rect, rtgui_color_t fore, rtgui_color_t back)
//    {
//		if (_image)
//			delete _image;

//        _image = img;
//        _point = point;
//        selRect = rect;
//        strRect = Rect(rect.left() + img->getWidth(), 0, rect.getWidth() - img->getWidth(), rect.getHeight());

//        foreColor = fore;
//        backColor = back;

//        if (selDc)
//        {
//            rtgui_dc_destory(selDc);
//            selDc = RT_NULL;
//        }

//        if (selDc == RT_NULL)
//        {
//            selDc = rtgui_dc_buffer_create_pixformat(RTGRAPHIC_PIXEL_FORMAT_RGB565, selRect.getWidth(), selRect.getHeight());
//            if (selDc)
//            {
//                rtgui_gc_t *gc = rtgui_dc_get_gc(selDc);

//                gc->background = backColor;
//                gc->foreground = foreColor;
//                gc->font = getFont();
//                gc->textalign = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_CENTER_VERTICAL;
//            }
//        }
//    }

//    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
//                        const Rect &srcRect = Rect(),
//                        RenderFlag flags = DrawNormal);

//private:
//    int norItemFontSize, selItemFontSize;

//    Image *_image;			//选中框左边的图片
//    Point _point;			//图片显示相对于选中框坐标起始点
//    Rect selRect, strRect;	//选中框、字符串显示相对坐标对应矩形
//    rtgui_color_t foreColor, backColor;		//选中框的前景色和背景色，背景色与控件背景色一致
//    struct rtgui_dc *selDc;		//选中框 dc
//};

}
#endif

