#ifndef PM_WINDOW_H__
#define PM_WINDOW_H__

#include <rtgui/widgets/window.h>

#include <pm_widget.h>
#include <pm_container.h>
#include <vector>

namespace Persimmon
{

class Window : public Container
{
    typedef Container super;

public:
    /* create a main window */
    Window(const char *title);
    /* create a normal window */
    Window(struct rtgui_win *parent, const char *title, rtgui_rect_t *rect, rt_uint16_t style);

    virtual ~Window();

    virtual int show(rt_bool_t isModal = RT_FALSE);
    virtual void close(int code);
    void close()
    {
        close(0);
    }
    void hide()
    {
        rtgui_win_hide(getWindow());
    }

    void move(int x, int y);

    struct rtgui_win* getWindow(void)
    {
        return RTGUI_WIN(widget);
    }

    void winPaintEnable(bool paint = true)
    {
        WIN_PAINT = paint;
    }

    rt_bool_t privateEventHandler(struct rtgui_event *event);
    virtual rt_bool_t eventHandler(struct rtgui_event *event);
    virtual bool dealKbd(struct rtgui_event_kbd *kev);

    void saveClip(struct rtgui_region &region);
    void restoreClip(struct rtgui_region &region);

    void addFloatingWidget(Widget *widget);
    void removeFloatingWidget(Widget *widget);
    void renderFloatingWidget(rtgui_rect_t *rect);
    void renderLogo(rtgui_rect_t *rect);
    void claerMouse(void)
    {
        RTGUI_MOUSE_BUTTON_IS_DOWN = false;
    }

protected:
    void paintChildren();
    bool dealMouseButton(struct rtgui_event_mouse *mev);
    bool dealMouseMotion(struct rtgui_event_mouse *mev);
    bool dealGesture(struct rtgui_event_gesture *mev);

private:
    void setupMouseOwner(struct rtgui_event_mouse *mev);
    Widget *setupMouseOwnerFloating(struct rtgui_event_mouse *mev);

    struct rtgui_gesture gesture;
    Widget *mouseEventOwner;
    rt_uint32_t curMouseId;
    bool WIN_PAINT, RTGUI_MOUSE_BUTTON_IS_DOWN;

    /* floating widget */
    std::vector<Widget*> childrenFloating;
};

}

#endif
