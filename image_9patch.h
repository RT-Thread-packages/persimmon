/*
 * File      : image_9patch.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <pm_image.h>

namespace Persimmon
{

class Image9Patch : public Image
{
public:
    Image9Patch(const char* filename);
    virtual ~Image9Patch();

    virtual void render(struct rtgui_dc* dc, const Rect& rect);
    virtual void render(struct rtgui_dc* dc, const Point& point);

private:
    int top_x, top_width;
    int left_y, left_height;

    struct rtgui_dc *buffer;
};

}
