#ifndef PM_WIDIGET_H__
#define PM_WIDIGET_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>
#include <gesture.h>

#include <persimmon.h>
#include <pm_rect.h>
#include <pm_image.h>

namespace Persimmon
{
namespace utils
{

/* Borrowed from Boost::noncopyable. Add the template to give each noncopyable
* a different signature. */
template <typename T>
class noncopyable
{
protected:
    noncopyable() {}
    ~noncopyable() {}
private:  // emphasize the following members are private
    noncopyable( const noncopyable& );
    noncopyable& operator=( const noncopyable& );
};

#define DEFINE_CLASS_ENUM_FLAG_OPERATORS(ENUMTYPE) \
    friend inline ENUMTYPE operator | (ENUMTYPE a,  ENUMTYPE b) \
           { return ENUMTYPE(((int)a)|((int)b)); } \
    friend inline ENUMTYPE operator |= (ENUMTYPE &a,  ENUMTYPE b) \
           { return (ENUMTYPE &)(((int &)a) |= ((int)b)); } \
    friend inline ENUMTYPE operator & (ENUMTYPE a,  ENUMTYPE b) \
           { return ENUMTYPE(((int)a)&((int)b)); } \
    friend inline ENUMTYPE operator &= (ENUMTYPE &a,  ENUMTYPE b) \
           { return (ENUMTYPE &)(((int &)a) &= ((int)b)); } \
    friend inline ENUMTYPE operator ~ (ENUMTYPE a) \
           { return (ENUMTYPE)(~((int)a)); } \
    friend inline ENUMTYPE operator ^ (ENUMTYPE a,  ENUMTYPE b) \
           { return ENUMTYPE(((int)a)^((int)b)); } \
    friend inline ENUMTYPE operator ^= (ENUMTYPE &a,  ENUMTYPE b) \
           { return (ENUMTYPE &)(((int &)a) ^= ((int)b)); }

#define DEFINE_CLASS_ENUM_FLAG_OPERATORS2(ENUMTYPE) \
    inline ENUMTYPE operator | (ENUMTYPE a,  ENUMTYPE b) \
           { return ENUMTYPE(((int)a)|((int)b)); } \
    inline ENUMTYPE operator |= (ENUMTYPE &a,  ENUMTYPE b) \
           { return (ENUMTYPE &)(((int &)a) |= ((int)b)); } \
    inline ENUMTYPE operator & (ENUMTYPE a,  ENUMTYPE b) \
           { return ENUMTYPE(((int)a)&((int)b)); } \
    inline ENUMTYPE operator &= (ENUMTYPE &a,  ENUMTYPE b) \
           { return (ENUMTYPE &)(((int &)a) &= ((int)b)); } \
    inline ENUMTYPE operator ~ (ENUMTYPE a) \
           { return (ENUMTYPE)(~((int)a)); } \
    inline ENUMTYPE operator ^ (ENUMTYPE a,  ENUMTYPE b) \
           { return ENUMTYPE(((int)a)^((int)b)); } \
    inline ENUMTYPE operator ^= (ENUMTYPE &a,  ENUMTYPE b) \
           { return (ENUMTYPE &)(((int &)a) ^= ((int)b)); }

}

class Container;
class Window;

/**
 * Persimmon UI Widget
 */
class Widget: private utils::noncopyable<Widget>
{
public:
    Widget();
    Widget(const rtgui_type_t *widget_type);
    virtual ~Widget();

    Widget *getParent(void)
    {
        if (widget->parent) return (Widget*)(widget->parent->user_data);
        return NULL;
    }

    Widget* setFont(struct rtgui_font* font)
    {
        RTGUI_WIDGET_FONT(this->widget) = font;
        return this;
    }

    struct rtgui_font* getFont(void)
    {
        return RTGUI_WIDGET_FONT(this->widget);
    }

    Widget* setBackground(rtgui_color_t color)
    {
        RTGUI_WIDGET_BACKGROUND(widget) = color;

        /* check whether has alpha channel */
        if (RTGUI_RGB_A(color) != 255)
        {
            widget->flag |= RTGUI_WIDGET_FLAG_TRANSPARENT;
            rtgui_widget_clip_return(widget);
        }
        else
        {
			if (backgroundDc)
				rtgui_dc_destory(backgroundDc);
			backgroundDc = RT_NULL;

            if (widget->flag & RTGUI_WIDGET_FLAG_TRANSPARENT)
            {
                widget->flag &= ~RTGUI_WIDGET_FLAG_TRANSPARENT;
                rtgui_widget_clip_parent(widget);
            }
            else
            {
                widget->flag &= ~RTGUI_WIDGET_FLAG_TRANSPARENT;
            }
        }

        return this;
    }

    Widget* setBackground(Image *image)
    {
        if (backgroundDc)
			rtgui_dc_destory(backgroundDc);
        backgroundDc = RT_NULL;

        if (image)
        {
            backgroundDc = rtgui_dc_buffer_create(image->getWidth(), image->getHeight());
			if (backgroundDc)
				rtgui_image_blit(image->getImage(), backgroundDc, RT_NULL);

            /* release this image */
            delete image;
        }

        return this;
    }

	Widget* setTransparentBackground(Image *image)
	{
		if (backgroundDc)
			rtgui_dc_destory(backgroundDc);
		backgroundDc = RT_NULL;

		if (image)
		{
			backgroundDc = rtgui_dc_buffer_create_pixformat(RTGRAPHIC_PIXEL_FORMAT_ARGB888, image->getWidth(), image->getHeight());
			if (backgroundDc)
				rtgui_image_blit(image->getImage(), backgroundDc, RT_NULL);

			/* release this image */
			delete image;
		}

		return this;
	}

    Widget* setBackground(struct rtgui_dc* bg)
    {
        if (backgroundDc)
			rtgui_dc_destory(backgroundDc);
        backgroundDc = bg;

        return this;
    }

    Widget* setForeground(rtgui_color_t color)
    {
        RTGUI_WIDGET_FOREGROUND(this->widget) = color;
        return this;
    }

    Widget* setTextAlign(int align)
    {
        RTGUI_WIDGET_TEXTALIGN(widget) = align;
        return this;
    }

    struct rtgui_widget* getWidget(void)
    {
        return RTGUI_WIDGET(this->widget);
    }

    Rect getRect(void) const;
    void getRect(struct rtgui_rect* rect) const;

    void setRect(struct rtgui_rect* rect);
    virtual void setRect(const Rect &rect);

    Point getPosition(void) const;
    Size getSize(void) const;
    void setSize(const Size &size);

    Rect getExtent(void) const;
    void getExtent(struct rtgui_rect* rect) const;

    Widget* getVisiableParent(void);

    bool isInAnimation(void)
    {
        return (rtgui_widget_is_in_animation(getWidget()) == RT_TRUE) ? true:false ;
    }

    bool isTransparent(void)
    {
        return (widget->flag & RTGUI_WIDGET_FLAG_TRANSPARENT) ? true:false;
    }

    void refresh(bool update = true);

    void freeze(void);
    void thaw(void);

    void setLastFocus(bool focus);
    void move(int x, int y);
    void moveTo(int x, int y);

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(), RenderFlag flags = DrawNormal);
    virtual void renderBackground(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                                  const Rect &srcRect = Rect(), RenderFlag flags = DrawNormal);

    struct rtgui_dc* getBufferDrawing(rt_uint8_t pixel_format, RenderFlag flags = DrawNormal);
    struct rtgui_dc* getBufferDrawing(RenderFlag flags = DrawNormal);

    void hide()
    {
        rtgui_widget_hide(widget);
    }
    virtual rt_bool_t onHide(struct rtgui_event *event);
    bool isHide()
    {
        return RTGUI_WIDGET_IS_HIDE(widget);
    }

    void show()
    {
        rtgui_widget_show(widget);
    }
    virtual rt_bool_t onShow(struct rtgui_event *event);

    virtual rt_bool_t eventHandler(struct rtgui_event *event);

    virtual Widget* getMouseOwner(int x, int y);

    void setInterestGesture(enum rtgui_gesture_type tp)
    {
        gest_tp = tp;
    }
    enum rtgui_gesture_type getInterestGesture();

    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev,
                                    const struct rtgui_gesture *gest);

    Widget* getParent() const
    {
        return parent;
    }

    void setParent(Widget *w)
    {
        parent = w;
        rtgui_widget_set_parent(widget, w ? w->widget : NULL);
    }
	
    virtual void setGestureRect(const Rect &rect, bool enable = true)
	{
		gestureRect = rect;
		enableGestureRect = enable;
	}

	void renderFloating(struct rtgui_dc *dc);

protected:
    static void renderParentBackground(Widget* widget, Widget* parent, struct rtgui_dc* dc, const Point &dcPoint, const Rect &srcRect);

    struct rtgui_widget* widget;
    struct rtgui_dc *backgroundDc;

private:
    /* Set by Container::addChild. */
    Widget *parent;

	bool enableGestureRect;
	Rect gestureRect;

    friend class Window;
    enum rtgui_gesture_type gest_tp;
};

}

DEFINE_CLASS_ENUM_FLAG_OPERATORS2(rtgui_gesture_type);

#endif
