#ifndef IMAGE_BOX_H__
#define IMAGE_BOX_H__

#include <pm_widget.h>
#include <pm_image.h>

namespace Persimmon
{

class ImageBox : public Widget
{
public:
    ImageBox(Image *image, const char *title = NULL);
    virtual ~ImageBox();

    void setImage(Image *m);
    void setTitle(char *title);

    Image* getImage(void)
    {
        return image;
    }
    const char* getTitle(void)
    {
        return title;
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

protected:
    Image *image;
    const char *title;
};

}
#endif

