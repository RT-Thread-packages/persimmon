#ifndef IMAGE_GROUP_H__
#define IMAGE_GROUP_H__

#include <pm_container.h>
#include <sigslot.h>
#include <pm_image.h>

namespace Persimmon
{

class ImageItem;

class ImageGroup : public Container
{
public:
    ImageGroup(const Rect &rect);
    virtual ~ImageGroup()
    {
        items.clear();
    }

    Signal<int> clicked;

    void addItem(Image *itemImage, int value, const Rect rect);

    void select(int value);
    void clearSelect(void);
    int  getSelected(void)
    {
        return selectedItem;
    }

    virtual bool handleGestureEvent(struct rtgui_event_gesture *, const struct rtgui_gesture *);

private:
    ImageItem *getItem(int value);

    int selectedItem;
    std::vector<ImageItem *> items;
};

}

#endif
