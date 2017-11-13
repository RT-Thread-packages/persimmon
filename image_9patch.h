#ifndef IMAGE_9PATH_H__
#define IMAGE_9PATH_H__

#include <pm_image.h>

namespace Persimmon
{

class Image9Patch : public Image
{
public:
    Image9Patch(const char* filename);
    virtual ~Image9Patch();

    virtual void render(struct rtgui_dc* dc, const Rect& rect);
    virtual void render(struct rtgui_dc* dc, const Point& point);

private:
    int top_x, top_width;
    int left_y, left_height;

    struct rtgui_dc *buffer;
};

}

#endif

