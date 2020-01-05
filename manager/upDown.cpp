/*************************************************************************
	> File Name: upDown.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四  1/ 2 17:09:00 2020
 ************************************************************************/

#include <iostream>
#include <stdio.h>
using namespace std;

struct myint {
    char f;
    char s;
    char t;
    char l;
};

int main() {
    int in = 0;
    struct myint gig;
    while (in != '0') {
        in = getchar();
        gig.f = in << 0 >> 24;
        gig.s = in << 8 >> 24;
        gig.t = in << 16 >> 24;
        gig.l = in << 24 >> 24;
        cout << gig.f << " | " << gig.s << " | " << gig.t << " | " << gig.l << endl;
        cout << (int)gig.f << " | " << (int)gig.s << " | " << (int)gig.t << " | " << (int)gig.l << endl;
    }
    return 0;
}
