#ifndef PM_SWITCH_H__
#define PM_SWITCH_H__

#include <pm_image.h>
#include <pm_widget.h>

#include <sigslot.h>

namespace Persimmon
{

class Switch : public Widget
{
public:
    Switch(Image* on, Image* off, bool status = false);
    virtual ~Switch();

    bool getStatus()
    {
        return on;
    }

    void setStatus(bool on);

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev,
                                    const struct rtgui_gesture *gest);

    Signal<bool> changed;

private:
    Image *image_on;
    Image *image_off;

    bool on;
};

}

#endif

