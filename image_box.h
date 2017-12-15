/*
* File      : image_box.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2017 RT-Thread Develop Team
*/
#pragma once

#include <pm_widget.h>
#include <pm_image.h>

namespace Persimmon
{

class ImageBox : public Widget
{
public:
    ImageBox(Image *image);
    virtual ~ImageBox();

    void setImage(Image *m);
	Image* getImage(void);

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

protected:
    Image *image;
};

}
