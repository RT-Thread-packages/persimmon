#ifndef PM_MultiTextBox_H__
#define PM_MultiTextBox_H__

#include <pm_widget.h>
#include <vector>

namespace Persimmon
{

class MultiTextBox : public Widget
{
public:
    MultiTextBox(const Rect& rect, int lines);
    MultiTextBox(struct rtgui_font* font, const Rect& rect, int lines);
    virtual ~MultiTextBox();

    void addText(char* text);
    void addText(char text);
    void addText(int num);


    char *getText(void);
    int getCurrentLineNum(void)
    {
        return textLinesPtr.size();
    }

    char *getLineText(int index);

    void cutText(void);
    void clearText(void);

    void setTextMaxLen(int len)
    {
        textMaxLen = len;
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    void updateText(const char* fmt, ...);
    void branch(void);
    std::vector<char *> textLinesPtr;

    char *text;
    int textLines, currentLine;
    int textMaxLen, textTotalLen;
};

}

#endif

