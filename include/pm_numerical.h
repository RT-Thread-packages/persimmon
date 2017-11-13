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
	enum NUM_ALIGN		//���뷽ʽ��Ĭ��������У������п��󣬿��ң�����
	{
		ALIGN_LEFT = 0x00,
		ALIGN_RIGHT = 0x01,
		ALIGN_CENTER = 0x02,
	};

	Numerical(const Rect& rect);
    virtual ~Numerical();

	void addImgPath(const char *img)	//�������ͼƬ��Ӧ·������0 - 9 ��˳�����
	{
		imgPath.push_back(rt_strdup(img));
	}
	
	void setNumWidth(int width)		//��������ͼƬ����ռ���
	{
		numWidth = width;
	}

	void setDigit(int digit)	//������ֵλ����ʾ����λ��0
	{
		this->digit = digit;
	}

	void setNumericalUnit(Image *image)		//���õ�λ��ʾ
	{
		if (unit)
			delete unit;

		unit = image;
	}

	void setNumericalMinus(Image *image)	//����֧����ʾ����
	{
		if (minus)
			delete minus;

		minus = image;
	}

	void setNumAlign(enum NUM_ALIGN algn = ALIGN_CENTER)	//���ö��뷽ʽ
	{
		numAlgn = algn;
	}
	
    void setNumerical(int value)	//������ʾ��ֵ
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
