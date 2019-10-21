/*************************************************************************
	> File Name: PhoneWindow.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 三  8/28 19:10:26 2019
 ************************************************************************/

#include "PhoneWindow.h"

void IconWindow::drawContents() {
    WindowImp *imp = GetWindowImp();
    if (imp != 0) {
        imp->deviceBitmap(_bitmapName, 0.0, 0.0);
    }
}

