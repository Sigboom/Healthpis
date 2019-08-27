/*************************************************************************
	> File Name: master.cpp
	> Author: 
	> Mail: 
	> Created Time: 二  8/27 21:26:23 2019
 ************************************************************************/

#include<iostream>
using namespace std;

class Window {
public:
    Windows (View *contents);

    virtual void drawContents();

    virtual void open();
    virtual void close();
    virtual void iconofy();
    virtual void deiconify();

    virtual void setOrigin(const Point &at);
    virtual void setExtent(const Point &extent);
    virtual void raise();
    virtual void lower();
    virtual void drawLine(const Point &, const Point &);
    virtual void drawRect(const Point &, const Point &);
    virtual void drawPolygon(const Point[], int n);
    virtual void DrawText(const char *, const Point &);

protected:
    WindowImp *getWindowImp();
    View *getView();
private:
    WindowImp *_imp;
    View *_contents;
};

class WindowsImp {
public:
    virtual void impTop() = 0;
    virtual void impBottom() = 0;
    virtual void impSetExtent(const Point &) = 0;
    virtual void impSetOrigin(const Point &) = 0;

    virtual void deviceRect(Coord, Coord, Coord, Coord) = 0;
    virtual void deviceText(const char *, Coord, Coord) = 0;
    virtual void deviceBitmap(const char *, Coord, Coord) = 0;
    //other function
protected:
    WindowImp();
};

class ApplicationWindow : public Window {
public:
    //...
    virtual void drawContents();
};

void ApplicationWindow::drawContents() {
    GetView()->DrawOn(this);
}

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

void Window::drawRect(const Point &p1, const Point &p2) {
    WindowImp *imp = getWindowImp();
    imp->deviceRect(p1.X(), p1.Y(), p2.X(), p2.Y());
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
