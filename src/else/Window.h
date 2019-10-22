/*************************************************************************
	> File Name: Window.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 三  8/28 18:58:50 2019
 ************************************************************************/

#ifndef _WINDOW_H
#define _WINDOW_H

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

class WindowImp {
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

#endif
