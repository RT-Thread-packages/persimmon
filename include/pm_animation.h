#pragma once

#include <pm_widget.h>
#include <pm_window.h>
#include <pm_timer.h>
#include <vector>

namespace Persimmon
{

enum
{
    ANIM_TICK_RANGE = 1024,
};

class AnimAbstractAnimator
{
public:
    AnimAbstractAnimator(struct rtgui_dc *b) : buffer(b), wgt(NULL) {}
    AnimAbstractAnimator(Widget &w) : buffer(NULL), wgt(&w) {}

    virtual ~AnimAbstractAnimator()
    {
        if (wgt && buffer)
            rtgui_dc_destory(buffer);
    }

    virtual void act(struct rtgui_dc* dest_dc,
                     int progress) = 0;
protected:
    struct rtgui_dc *buffer;
    Widget *wgt;
};

class AnimFadeAnimator: public AnimAbstractAnimator
{
    typedef AnimAbstractAnimator super;

public:
    AnimFadeAnimator(struct rtgui_dc *buffer,
                     bool is_fade_out,
                     const Point &start_pt);
    AnimFadeAnimator(Widget &wgt,
                     bool is_fade_out,
                     const Point &start_pt);

    virtual ~AnimFadeAnimator();
    virtual void act(struct rtgui_dc *dest_dc, int progress);

protected:
    Point start_pt;
    bool is_fade_out;
};

class AnimMoveAnimator: public AnimAbstractAnimator
{
    typedef AnimAbstractAnimator super;

public:
    AnimMoveAnimator(struct rtgui_dc *buffer,
                     const Point &start_pt,
                     const Point &stop_pt);
    AnimMoveAnimator(Widget &wgt,
                     const Point &start_pt,
                     const Point &stop_pt);

    void enableFade(bool fade = true)
    {
        is_fade = fade;
    }

    void enableFadeOut(bool fadeOut = true)
    {
        is_fade_out = fadeOut;
    }

    void setFadeA(int min, int max)
    {
        a_min = min;
        a_max = max;
    }

    virtual ~AnimMoveAnimator();
    virtual void act(struct rtgui_dc *dest_dc, int progress);

protected:
    Point start_pt, stop_pt;
    bool is_fade, is_fade_out;
    int a_min, a_max;
};

class AnimSlideAnimator : public AnimAbstractAnimator
{
    typedef AnimAbstractAnimator super;

public:
    AnimSlideAnimator(struct rtgui_dc *buffer,
                      const Rect &rect,
                      const Point &start_pt,
                      const Point &stop_pt);
    AnimSlideAnimator(Widget &wgt,
                      const Rect &rect,
                      const Point &start_pt,
                      const Point &stop_pt);

    virtual ~AnimSlideAnimator();
    virtual void act(struct rtgui_dc *dest_dc, int progress);
    void setColor(rtgui_color_t left, rtgui_color_t right)
    {
        colorLeft = left;
        colorRight = right;
    }

protected:
    Rect animRect;
    Point start_pt, stop_pt;
    rtgui_color_t colorLeft, colorRight;
};

class AnimScaleAnimator: public AnimAbstractAnimator
{
    typedef AnimAbstractAnimator super;

public:
    AnimScaleAnimator(struct rtgui_dc *buffer, bool zoomin);
    AnimScaleAnimator(Widget &wgt, bool zoomin);

    virtual ~AnimScaleAnimator();
    virtual void act(struct rtgui_dc *dest_dc, int progress);

protected:
    bool is_zoomin;
};

class AnimImageItem
{
public:
    AnimImageItem(const char *img_path, int value);
    virtual ~AnimImageItem() {}

    int getItemNum(void)
    {
        return item_num;
    }
    Image* getImage(void)
    {
        return image;
    }

private:
    Image* image;
    int item_num;
};

class AnimShowPictureAnimator : public AnimAbstractAnimator
{
    typedef AnimAbstractAnimator super;

public:
    AnimShowPictureAnimator(struct rtgui_dc *buffer, const char *img_path, const char *img_type, int p_num);
    AnimShowPictureAnimator(Widget &wgt, const char *img_path, const char *img_type, int p_num);

    virtual ~AnimShowPictureAnimator();
    virtual void act(struct rtgui_dc *dest_dc, int progress);

protected:
    int picture_num, progress_num;
    std::vector<AnimImageItem *> items;
};

class AnimAbstractInterpolator
{
public:
    virtual ~AnimAbstractInterpolator() {}
    virtual int interpolate(int cur, int max) = 0;
};

class AnimLinearInterpolator: public AnimAbstractInterpolator
{
public:
    virtual ~AnimLinearInterpolator() {}
    virtual int interpolate(int cur, int max)
    {
        return cur * ANIM_TICK_RANGE / max;
    }
};

class AnimInsquareInterpolator : public AnimAbstractInterpolator
{
public:
    virtual ~AnimInsquareInterpolator() {}
    virtual int interpolate(int cur, int max)
    {
        /* Care about integer overflow. tick can within 0~(4G/RTGUI_ANIM_TICK_RANGE). */
        return cur * ANIM_TICK_RANGE / max * cur / max;
    }
};

class AnimOutsquareInterpolator : public AnimAbstractInterpolator
{
public:
    virtual ~AnimOutsquareInterpolator() {}
    virtual int interpolate(int cur, int max)
    {
        /* Care about integer overflow. tick can within 0~(4G/RTGUI_ANIM_TICK_RANGE). */
        cur = max - cur;
        return ANIM_TICK_RANGE - (cur * ANIM_TICK_RANGE / max * cur / max);
    }
};

class Animation: private utils::noncopyable<Animation>
{
public:
    Animation(Widget &w);
    ~Animation();

    Animation *setBGbuffer(struct rtgui_dc *dc)
    {
        m_bg = dc;
        return this;
    }
    Animation *setInterval(int inter)
    {
        m_interval = inter;
        return this;
    }
    Animation *setDuration(int dur)
    {
        m_duration = dur;
        return this;
    }
    Animation *setInterpolator(AnimAbstractInterpolator &inter)
    {
        m_interplator = &inter;
        return this;
    }

    Animation *addAnimator(AnimAbstractAnimator *anim)
    {
        m_animators.push_back(anim);
        return this;
    }

    Signal<struct rtgui_dc *, int> actSignal;
    Signal<void> endSignal;

    void start(bool is_modal=true);
    void stop();

private:
    Widget *m_owner;
    Timer *m_timer;
    struct rtgui_dc *m_bg, *saveDc;
    unsigned int m_interval, m_duration, m_tick_start;

    std::vector<AnimAbstractAnimator*> m_animators;
    AnimAbstractInterpolator *m_interplator;

    enum stat
    {
        ANIM_ST_NONE  = 0,
        ANIM_ST_MODAL = (1 << 0),
        ANIM_ST_STOP  = (0 << 1),
        ANIM_ST_RUN   = (1 << 1),
    } m_stat;

    void _drawframe();
};

}
