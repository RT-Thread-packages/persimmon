/*
* File      : ui_win.c
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2016 RT-Thread Develop Team
*/
#include "animation.h"
#include <rtthread.h>

#include <pm_application.h>
#include <pm_window.h>


extern "C" {
void ui_win(void)
{
    Application *app = new Application("MainWin");
    if (app)
    {
		AnimationWin *win = new AnimationWin();
        if (win)
        {
            win->show(true);
            delete win;
        }

        delete app;
    }
}
}