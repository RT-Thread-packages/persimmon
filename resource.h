/*
* File      : resource.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
*/
#ifndef RESOURCE_H__
#define RESOURCE_H__

#include <rtgui/rtgui.h>
#include <pm_image.h>

using namespace Persimmon;

#define PREFIX		"/"

Image* getImage(const char* fmt, ...);
struct rtgui_dc *getImageDc(const char* fmt, ...);

rt_thread_t rtgui_loading_thread_init(const char *name,
                                      void (*entry)(void *parameter),
                                      void *parameter,
                                      rt_uint32_t stack_size);

#endif
