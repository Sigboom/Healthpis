/*************************************************************************
	> File Name: Window.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 三  8/28 19:00:49 2019
 ************************************************************************/

#include "Window.h"

void Window::drawRect(const Point &p1, const Point &p2) {
    WindowImp *imp = getWindowImp();
    imp->deviceRect(p1.X(), p1.Y(), p2.X(), p2.Y());
}

