/*
 * File      : pm_rect.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <rtgui/rtgui.h>
#include <rtgui/region.h>

namespace Persimmon
{

class Rect;

class Point
{
public:
    Point()
    {
        xp = 0;
        yp = 0;
    }
    Point(int xpos, int ypos);

    void move(int x, int y);
    void moveTo(int x, int y);

    inline bool isNull() const
    {
        return (xp == 0 && yp == 0);
    }
    inline int x() const
    {
        return xp;
    }
    inline int y() const
    {
        return yp;
    }

    inline void set(int x, int y)
    {
        xp = x;
        yp = y;
    }
    inline void setX(int x)
    {
        xp = x;
    }
    inline void setY(int y)
    {
        yp = y;
    }

    inline Point &operator+=(const Point &p);
    inline Point &operator-=(const Point &p);

    friend inline const Point operator+(const Point &, const Point &);
    friend inline const Point operator-(const Point &, const Point &);

    struct rtgui_point getPoint(void)
    {
        struct rtgui_point p;
        p.x = xp;
        p.y = yp;
        return p;
    }

private:
    int xp;
    int yp;
};

inline Point &Point::operator+=(const Point &p)
{
    xp+=p.xp;
    yp+=p.yp;
    return *this;
}

inline Point &Point::operator-=(const Point &p)
{
    xp-=p.xp;
    yp-=p.yp;
    return *this;
}

inline const Point operator+(const Point &p1, const Point &p2)
{
    return Point(p1.xp+p2.xp, p1.yp+p2.yp);
}

inline const Point operator-(const Point &p1, const Point &p2)
{
    return Point(p1.xp-p2.xp, p1.yp-p2.yp);
}

class Size
{
public:
    Size(int width, int height);
    Size(const Rect &rect);

    int getWidth() const
    {
        return width;
    }
    int getHeight() const
    {
        return height;
    }

private:
    rt_uint16_t width;
    rt_uint16_t height;
};

class Rect
{
public:
    Rect()
    {
        rect.x1 = rect.x2 = 0;
        rect.y1 = rect.y2 = 0;
    }
    Rect(const struct rtgui_rect *r);
    Rect(int x, int y, int width, int height);
    Rect(const Point &point, const Size &size);

    bool isNull () const
    {
        return (rtgui_rect_is_empty(&rect) == RT_TRUE);
    }

    void set(int x, int y, int width, int height);
    int getWidth() const;
    Rect* setWidth(int width);
    int getHeight() const;
    Rect* setHeight(int height);

    Size getSize() const;
    void setSize(const Size& size);

    void moveTo(int x, int y);
    void moveTo(const Point &point);
    void move(int deltaX, int deltaY);
    void move(const Point &deltaPoint);

    int left() const;
    int top() const;
    int right() const;
    int bottom() const;

    int x() const
    {
        return rect.x1;
    }
    Rect* setX(int x)
    {
        rect.x1 = x;
        return this;
    }
    int y() const
    {
        return rect.y1;
    }
    Rect* setY(int y)
    {
        rect.y1 = y;
        return this;
    }

    bool contain(int x, int y);

    struct rtgui_rect* getRect(void)
    {
        return &rect;
    }
    void getRect(struct rtgui_rect* r)
    {
        if (r) *r = rect;
    }

private:
    struct rtgui_rect rect;
};

inline const Rect operator+(const Rect& rect,
                            const Point& pt)
{
    Rect rt(rect);

    rt.move(pt);
    return rt;
}

inline const Rect operator-(const Rect& rect,
                            const Point& pt)
{
    Rect rt(rect);

    rt.move(-pt.x(), -pt.y());
    return rt;
}

inline int Rect::left() const
{
    return rect.x1;
}

inline int Rect::top() const
{
    return rect.y1;
}

inline int Rect::right() const
{
    return rect.x2;
}

inline int Rect::bottom() const
{
    return rect.y2;
}

}

