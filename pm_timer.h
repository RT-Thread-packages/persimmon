#pragma once

#include <pm_widget.h>
#include <sigslot.h>

#include <rtgui/rtgui_system.h>

namespace Persimmon
{

class Timer: private utils::noncopyable<Timer>
{
public:
    enum flag
    {
        ONE_SHOT   = RT_TIMER_FLAG_ONE_SHOT,
        PERIODIC   = RT_TIMER_FLAG_PERIODIC,
        SOFT_TIMER = RT_TIMER_FLAG_SOFT_TIMER,
    };

    Timer(int time, enum flag flag);
    ~Timer();

    void start();
    void stop();
    void setTimeout(int time);

    Signal<void> timeout;

private:
    struct rtgui_timer *m_timer;
    static void _onTimeout(struct rtgui_timer *timer, void *parameter);
};

}
