/*************************************************************************
	> File Name: patient.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/ 7 09:51:42 2019
 ************************************************************************/

#include <iostream>
#include <string>

using namespace std;

class patient {
public:
    string symptom;
public:
    patient(){}
    patient(string talk): symptom(talk) {}
    
    void show() {
        cout << symptom << endl;
        return ;
    }

    void checknet() {
        cout << "checking net" << endl;
        return ;
    }

    void checkconf() {
        cout << "checking net" << endl;
    }

    string getSym() {
        return this->symptom;
    }

    void setSym(string sym) {
        this->symptom = sym;
        return ;
    }
};


