#ifndef PM_APPLICATION_H__
#define PM_APPLICATION_H__

#include <rtgui/rtgui_app.h>
#include <rtgui/rtgui_system.h>
// for utils
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

#if 0
// Include the C header in the outer namespace.
#include <wbus.h>

namespace Persimmon
{

class WBusApplication : public Application
{
    typedef Application super;
public:
    WBusApplication(const char *t) : super(t) {}
    virtual ~WBusApplication() {}

    virtual rt_bool_t onWBusEvent(struct wbus_notify_event *eve) = 0;

    virtual rt_bool_t eventHandler(struct rtgui_event *event)
    {
        switch (event->type)
        {
        case WBUS_NOTIFY_EVENT:
            return onWBusEvent((struct wbus_notify_event *)event);
        default:
            return super::eventHandler(event);
        }
    }

    rt_err_t WBusSubscribe(const char *topic)
    {
        return wbus_subscribe(topic, getApplication()->mq);
    }

    rt_err_t WBusUnSubscribe(const char *topic)
    {
        return wbus_unsubscribe(topic, getApplication()->mq);
    }
};

}

#endif

#endif
