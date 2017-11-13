/*
* File      : pm_checkbox.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2009-2017 RT-Thread Develop Team
*/
#pragma once

#include <vector>
#include <pm_container.h>
#include <pm_image.h>
#include "sigslot.h"

namespace Persimmon
{

class Checkbox : public Widget
{
public:
    Checkbox(const Rect& rect);
    virtual ~Checkbox();

    bool isSelected(void)		//�Ƿ�ѡ��
    {
        return selected;
    }

    void enableSelected(bool sel = true)	//ѡ��
    {
        selected = sel;
    }

    void setSelectedImg(Image *image)
    {
        if (selectedImg)
            delete selectedImg;

        selectedImg = NULL;

        if (image)
            selectedImg = image;
    }

    Image *getSelectedImg(void)
    {
        return selectedImg;
    }

    void setNormalImg(Image *image)
    {
        if (normalImg)
            delete normalImg;

        normalImg = NULL;

        if (image)
            normalImg = image;
    }

    Image *getNormalImg(void)
    {
        return normalImg;
    }

    void setCheckboxNum(int num)	//���� �ؼ� ���
    {
        checkboxNum = num;
    }

    int getCheckboxNum(void)	//��ȡ �ؼ� ���
    {
        return checkboxNum;
    }

    Signal<int, bool> clicked;	//�ؼ��¼�����

    virtual bool handleGestureEvent(struct rtgui_event_gesture *, const struct rtgui_gesture *);	//���������¼�������

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    Image *selectedImg, *normalImg;
    bool selected;		//״̬
    int checkboxNum;	//���
};

class GroupBox : public Container
{
public:
    GroupBox(const Rect& rect);
    virtual ~GroupBox();

    virtual void handleClicked(int num, bool sel)
    {
        if (sel == true)
        {
            if (selCheckboxNum != num)
            {
                this->checkbox[selCheckboxNum]->enableSelected(false);
                this->checkbox[selCheckboxNum]->refresh();
                selCheckboxNum = num;
				clicked(selCheckboxNum);
            }
        }
        else
        {
            this->checkbox[selCheckboxNum]->enableSelected(true);
            this->checkbox[selCheckboxNum]->refresh();
        }
    }

    void addCheckbox(Checkbox* widget)
    {
        if (widget != NULL)
        {
            this->checkbox.push_back(widget);
            widget->setCheckboxNum(this->checkbox.size() - 1);
            widget->clicked.connect(this, &GroupBox::handleClicked);
            this->addChild(widget);
        }
    }

    void selectCheckbox(int num = 0)
    {
        if (selCheckboxNum != num)
            this->checkbox[selCheckboxNum]->enableSelected(false);
        this->checkbox[selCheckboxNum]->refresh();
        selCheckboxNum = num;
        this->checkbox[selCheckboxNum]->enableSelected();
        this->checkbox[selCheckboxNum]->refresh();
    }

    int getselectNum(void)
    {
        return selCheckboxNum;
    }

	Signal<int> clicked;

private:
    std::vector<Checkbox*> checkbox;
    int selCheckboxNum;
};

}
