/*
* File      : animation.cpp
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
*/
#include "animation.h"
#include "image_box.h"

#include "logo_image.h"
#include <math.h>

using namespace Persimmon;

AnimationWin::AnimationWin()
	: Window("button")
{
	_logo = rtgui_image_create_from_mem("hdc", persimmon_demo_image_hdc, sizeof(persimmon_demo_image_hdc), true);
	RT_ASSERT(_logo != RT_NULL);

	Rect wRect(0, 0, _logo->w, _logo->h);

	_logo_dc = rtgui_dc_buffer_create_pixformat(RTGRAPHIC_PIXEL_FORMAT_ARGB888, wRect.getWidth(), wRect.getHeight());
	RT_ASSERT(_logo_dc != RT_NULL);
	rtgui_image_blit(_logo, _logo_dc, wRect.getRect());
	
	img1 = new ImageBox(NULL);
	img1->setBackground(_logo_dc);
	img1->setBackground(TRANSPARENT);
	img1->setRect(Rect(0, 0, _logo->w, _logo->h));

	setBackground(LIGHT_GREY);	

	setInterestGesture(RTGUI_GESTURE_LONGPRESS | RTGUI_GESTURE_TAP);

	Rect userRect = getRect();
	width = userRect.getWidth();
	height = userRect.getHeight();

	touch_point_x = 0;
	touch_point_y = 0;
	point_src_x = 0;
	point_src_y = 0;
	cnt = 0;
	is_press = false;

	timer = new Timer(RT_TICK_PER_SECOND, Timer::ONE_SHOT);
	timer->timeout.connect(this, &AnimationWin::onButton);
	timer->start();
}

AnimationWin::~AnimationWin()
{

}

void AnimationWin::onButton(void)
{
	uint16_t two_point_length = 0;
	uint16_t xx = 0;
	uint16_t yy = 0;
	int16_t touch_point_x_old = 0;
	int16_t touch_point_y_old = 0;
	for (;;)
	{
		Animation *anim = new Animation(*this);

		srand((unsigned int)rt_tick_get());
		int16_t position_point_x = rand() % (width - logo_image_width);

		srand((unsigned int)rt_tick_get());
		int16_t position_point_y = rand() % (height - logo_image_height);

		if (cnt == 0)
		{
			point_des_x = width - logo_image_width;
			point_des_y = position_point_y;
		}
		else if (cnt == 1)
		{
			point_des_x = position_point_x;
			point_des_y = height - logo_image_height;
		}
		else if (cnt == 2)
		{
			point_des_x = 0;
			point_des_y = position_point_y;
		}
		else if (cnt == 3)
		{
			point_des_x = position_point_x;
			point_des_y = 0;
		}

		if (is_press == true)
		{
			point_des_x = touch_point_x - logo_image_width/2;
			point_des_y = touch_point_y - logo_image_height/2;
		}

		if ((point_des_x - point_src_x) < 0)
		{
			xx = (point_src_x - point_des_x)*(point_src_x - point_des_x);
		}
		else
		{
			xx = (point_des_x - point_src_x)*(point_des_x - point_src_x);
		}

		if ((point_des_y - point_src_y) < 0)
		{
			yy = (point_src_y - point_des_y)*(point_src_y - point_des_y);
		}
		else
		{
			yy = (point_des_y - point_src_y)*(point_des_y - point_src_y);
		}

		two_point_length = (uint16_t)sqrtf((float)(xx+yy));

		AnimMoveAnimator *animator1 = new AnimMoveAnimator(_logo_dc, Point(point_src_x, point_src_y), Point(point_des_x, point_des_y));

		struct rtgui_dc *bgDC = getBufferDrawing();

		anim->setBGbuffer(bgDC)
			->setInterval(RT_TICK_PER_SECOND/20) //RT_TICK_PER_SECOND/25
			->setDuration((two_point_length / 20 + 1) * (RT_TICK_PER_SECOND/20)) // two_point_length/20
			->addAnimator(animator1);

		anim->start();
		delete anim;

		rtgui_dc_destory(bgDC);

		point_src_x = point_des_x;
		point_src_y = point_des_y;

		cnt++;
		if (cnt > 3) cnt = 0;
	}
}

bool AnimationWin::handleGestureEvent(struct rtgui_event_gesture *gev,
	const struct rtgui_gesture *gest)
{
	if(gev->type == 0x8008) // longpress end
	{
		is_press = false;
	}
	else if(gev->type == 0x8001) // tap click end
	{
		is_press = false;
	}
	else if(gev->type == 0x0001)
	{
		is_press = true;
	}
	else if(gev->type == 0x0008)
	{
		is_press = true;
	}
	else
	{
		is_press = false;
	}

	if (gest->current.x == touch_point_x && gest->current.y == touch_point_y)
		return true;

	touch_point_x = gest->current.x;
	touch_point_y = gest->current.y;

	return true;
}
