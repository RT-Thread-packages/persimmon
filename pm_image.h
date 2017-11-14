/*
 * File      : pm_image.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <rtgui/image.h>
#include <rtgui/image_container.h>
#include <pm_rect.h>

namespace Persimmon
{

class Image
{
public:
    Image(const char* filename, rt_bool_t load = RT_TRUE);
    virtual ~Image();

    void getRect(Rect& rect);
    int getWidth();
    int getHeight();

    struct rtgui_image* getImage(void);
    void loadImage(const char *filename);

    virtual void render(struct rtgui_dc* dc, const Point& point);
    virtual void render(struct rtgui_dc* dc, const Rect& rect);

protected:
    struct rtgui_image* image;
#ifdef RTGUI_IMAGE_CONTAINER
    struct rtgui_image_item* item;
#endif
};

}

