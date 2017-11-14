/*
* File      : pm_numerical.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2017 RT-Thread Develop Team
*/
#pragma once

#include <vector>
#include <pm_widget.h>
#include <pm_image.h>
#include "resource.h"

namespace Persimmon
{

class Numerical : public Widget
{
public:
	enum NUM_ALIGN		//对齐方式，默认纵向居中，横向有靠左，靠右，居中
	{
		ALIGN_LEFT = 0x00,
		ALIGN_RIGHT = 0x01,
		ALIGN_CENTER = 0x02,
	};

	Numerical(const Rect& rect);
    virtual ~Numerical();

	void addImgPath(const char *img)	//添加数字图片对应路径，从0 - 9 按顺序添加
	{
		imgPath.push_back(rt_strdup(img));
	}
	
	void setNumWidth(int width)		//设置数字图片，所占宽度
	{
		numWidth = width;
	}

	void setDigit(int digit)	//设置数值位数显示，高位填0
	{
		this->digit = digit;
	}

	void setNumericalUnit(Image *image)		//设置单位显示
	{
		if (unit)
			delete unit;

		unit = image;
	}

	void setNumericalMinus(Image *image)	//设置支持显示负号
	{
		if (minus)
			delete minus;

		minus = image;
	}

	void setNumAlign(enum NUM_ALIGN algn = ALIGN_CENTER)	//设置对齐方式
	{
		numAlgn = algn;
	}
	
    void setNumerical(int value)	//设置显示数值
    {
		numerical = value;
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
	enum NUM_ALIGN numAlgn;
	std::vector<char *> imgPath;
    Image *unit, *minus;
    int numerical, numWidth, digit;
};

}
