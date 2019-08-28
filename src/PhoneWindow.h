/*************************************************************************
	> File Name: PhoneWindow.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 三  8/28 19:09:31 2019
 ************************************************************************/

#ifndef _PHONEWINDOW_H
#define _PHONEWINDOW_H

#include "Window.h"

class PhoneWindowImp : public WindowImp {
public:
    PhoneWindowImp();
    virtual void deviceRect(Coord, Coord, Coord, Coord);

    //remainder of public interface...
private:
    //lots of PM Window system-specific state
    HPS _hps;
};

class PhoneWindow : public Window {
public:
    //...
    virtual void drawContents();
private:
    const char *_bitmapName;
};

#endif
