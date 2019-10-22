/*************************************************************************
	> File Name: WebWindow.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 三  8/28 19:04:06 2019
 ************************************************************************/

#ifndef _WEBWINDOW_H
#define _WEBWINDOW_H

#include "Window.h"

class PCWindowImp : public WindowImp {
public:
    PCWindowImp();

    virtual void deviceRect(Coord, Coord, Coord, Coord);
    //remainder of public interface
private:
    //X Window system-specific state
    Display *_dpy;
    Drawable _winid;
    GC _gc;
};


class PCWindow : public Window {
public:
    //...
    virtual void drawContents();
};

#endif
