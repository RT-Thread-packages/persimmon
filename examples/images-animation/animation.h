/*
* File      : animation.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
*/
#pragma once

#include <rtthread.h>
#include <pm_animation.h>
#include "image_box.h"

#include "logo_image.h"

using namespace Persimmon;

class AnimationWin : public Window
{
public:
	AnimationWin();
	virtual ~AnimationWin();

	virtual bool handleGestureEvent(struct rtgui_event_gesture *gev, const struct rtgui_gesture *gest);

	void onButton(void);
	
private:
	int16_t width;
	int16_t height;
	ImageBox *img1;
	struct rtgui_dc *_logo_dc;
    struct rtgui_image *_logo;
    
	int16_t point_src_x;
	int16_t point_src_y;
	int16_t point_des_x;
	int16_t point_des_y;
	int16_t touch_point_x;
	int16_t touch_point_y;

	Timer *timer;
	int cnt;
	bool is_press;

};