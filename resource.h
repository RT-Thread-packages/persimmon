/*
 * File      : resource.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <rtgui/rtgui.h>
#include <pm_image.h>

using namespace Persimmon;

#define PREFIX      "/"

Image* getImage(const char* fmt, ...);
struct rtgui_dc *getImageDc(const char* fmt, ...);

rt_thread_t rtgui_loading_thread_init(const char *name,
                                      void (*entry)(void *parameter),
                                      void *parameter,
                                      rt_uint32_t stack_size);


