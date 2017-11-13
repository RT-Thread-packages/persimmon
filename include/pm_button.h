/*
* File      : pm_button.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2017 RT-Thread Develop Team
*/
#pragma once

#include <pm_image.h>
#include <pm_widget.h>
#include <sigslot.h>

namespace Persimmon
{

class Button : public Widget
{
public:
    Button(const char *text, Image *imgNor, Image *imgDown);
    Button(Image *imgNor, Image *imgDown);
    virtual ~Button();

    void setId(int id);
    int getId(void);

    void setText(const char *text);
    const char* getText(void);

    void setNorImage(Image *imgNor);
    Image* getNorImage(void);

    void setDownImage(Image *imgDown);
    Image* getDownImage(void);

    void setShadowImage(Image *imgShadow);
    Image* getShadowImage(void);

    Signal<int> clicked;

    virtual bool handleGestureEvent(struct rtgui_event_gesture *, const struct rtgui_gesture *);
    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    int id;
    char *text;
    Image *imageNor, *imageDown, *imageShadow;
    bool down;
};

}
