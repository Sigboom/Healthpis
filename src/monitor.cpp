/*************************************************************************
	> File Name: monitor.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二  8/28 21:26:23 2019
 ************************************************************************/

#include "Window.h"

class IconWindow : public Window {
public:
    //...
    virtual void drawContents();
private:
    const char *_bitmapName;
};

void IconWindow::drawContents() {
    WindowImp *imp = GetWindowImp();
    if (imp != 0) {
        imp->deviceBitmap(_bitmapName, 0.0, 0.0);
    }
}

class XWindowImp : public WindowImp {
public:
    XWindowImp();

    virtual void deviceRect(Coord, Coord, Coord, Coord);
    //remainder of public interface
private:
    //X Window system-specific state
    Display *_dpy;
    Drawable _winid;
    GC _gc;
};

class PMWindowImp : public WndowImp {
public:
    PMWindowImp();
    virtual void deviceRect(Coord, Coord, Coord, Coord);

    //remainder of public interface...
private:
    //lots of PM Window system-specific state
    HPS _hps;
};
