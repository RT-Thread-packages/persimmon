#ifndef PM_IMAGEROTOBOX_H__
#define PM_IMAGEROTOBOX_H__


#include <pm_widget.h>
#include <pm_timer.h>
#include <sigslot.h>

namespace Persimmon
{

class ImageRotoBox : public Widget
{
public:
    ImageRotoBox(const char* img_name);
    virtual ~ImageRotoBox();

    void start(int once_ticks, int frame, bool once = true);
    void stop(void);

    Signal<void> finished;

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    void timeout(void);

protected:
    struct rtgui_dc *img_dc;
    Timer *timer;
    int coord_x, coord_y, frame;
    double roto_degree;
    bool roto_mode;
};

}

#endif
