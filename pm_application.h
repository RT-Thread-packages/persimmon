/*
 * File      : pm_application.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <rtgui/rtgui_app.h>
#include <rtgui/rtgui_system.h>
#include <pm_widget.h>

DEFINE_CLASS_ENUM_FLAG_OPERATORS2(rtgui_app_flag);

namespace Persimmon
{

class Application : private utils::noncopyable<Application>
{
public:
    Application(const char *title);
    virtual ~Application();

    virtual rt_bool_t eventHandler(struct rtgui_event *event);

    void run(void);

    struct rtgui_app *getApplication(void)
    {
        return application;
    }

    void activate(void)
    {
        rtgui_app_activate(application);
    }

private:
    struct rtgui_app *application;
};

}

