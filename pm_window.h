#ifndef PM_WINDOW_H__
#define PM_WINDOW_H__

#include <rtgui/widgets/window.h>

#include <pm_widget.h>
#include <pm_container.h>
#include <vector>
#include <pm_animation.h>

namespace Persimmon
{

class Window : public Container
{
    typedef Container super;
public:
	enum AnimType
	{
		AnimNone = 0x00,
		AnimFade = 0x01,
		AnimMove = 0x02,
		AnimMoveUp = 0x04,
		AnimMoveDown = 0x08,
		AnimMoveLeft = 0x10,
		AnimMoveRight = 0x20,
	};
	DEFINE_CLASS_ENUM_FLAG_OPERATORS(AnimType);

    /* create a main window */
    Window(const char *title);
    /* create a normal window */
    Window(struct rtgui_win *parent, const char *title, rtgui_rect_t *rect, rt_uint16_t style);

    virtual ~Window();

    virtual int show(rt_bool_t isModal = RT_FALSE);
    virtual void close(int code = 0);
    void hide()
    {
        rtgui_win_hide(getWindow());
    }

    void move(int x, int y);

    struct rtgui_win* getWindow(void)
    {
        return RTGUI_WIN(widget);
    }

    rt_bool_t privateEventHandler(struct rtgui_event *event);
    virtual rt_bool_t eventHandler(struct rtgui_event *event);
    virtual bool dealKbd(struct rtgui_event_kbd *kev);
	virtual bool dealCmd(struct rtgui_event_command *cmd);

    void saveClip(struct rtgui_region &region);
    void restoreClip(struct rtgui_region &region);

    void addFloatingWidget(Widget *widget);
    void removeFloatingWidget(Widget *widget);
	void _renderFloatingWidget(struct rtgui_dc *dc, rtgui_rect_t *rect);
    void renderFloatingWidget(rtgui_rect_t *rect);
	void _renderLogo(struct rtgui_dc *dc, rtgui_rect_t *rect);

	void setAnimType(enum AnimType type, bool anim = true)
	{
		animType = type;
		doAnim = anim;
	}
	void doAnimShow(void);
	void doAnimHide(void);

	void paintWindow(void);
	void cancelGesture(void);

protected:
    void paintChildren();
    bool dealMouseButton(struct rtgui_event_mouse *mev);
    bool dealMouseMotion(struct rtgui_event_mouse *mev);
    bool dealGesture(struct rtgui_event_gesture *gev);
	void renderLogo(rtgui_rect_t *rect);

private:
    void setupMouseOwner(struct rtgui_event_mouse *mev);
    Widget *setupMouseOwnerFloating(struct rtgui_event_mouse *mev);

    struct rtgui_gesture gesture;
    Widget *mouseEventOwner;
    rt_uint32_t curMouseId;
    bool RTGUI_MOUSE_BUTTON_IS_DOWN;

    /* floating widget */
    std::vector<Widget*> childrenFloating;

	/* anim show type */
	enum AnimType animType;
	bool doAnim;
};

}

#endif
