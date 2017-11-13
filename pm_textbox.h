#ifndef PM_TEXTBOX_H__
#define PM_TEXTBOX_H__

#include <pm_widget.h>

namespace Persimmon
{

class TextBox : public Widget
{
public:
    TextBox(const Rect& rect);
    TextBox(struct rtgui_font* font, const Rect& rect);
    virtual ~TextBox();

    void addText(char* text);
    void addText(char text);
    void addText(int num);
    void cutText(void);

    char* getText(void);
    void clearText(void)
    {
        if (text != RT_NULL) rt_free(text);

        text = RT_NULL;
		textLen = 0;
    }

	void setTextMaxLen(int len)
	{
		textMaxLen = len;
	}

    void enableMask(bool mas = true)
    {
        mask = mas;
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    void updateText(const char* fmt, ...);

    char *text;
	int textMaxLen, textLen;
    bool mask;
};

}

#endif

