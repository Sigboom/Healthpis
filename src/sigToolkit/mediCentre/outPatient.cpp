/*************************************************************************
	> File Name: outPatient.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/ 7 11:14:49 2019
 ************************************************************************/

#include <queue>
#include "doctor.cpp"

using std::queue;
using std::shared_ptr;

class outPatient {
private:
    patient pa;
    queue<shared_ptr<doctor> > dq;
    sigDoctor doc;
public:
    outPatient() {}
    ~outPatient(){}

    void toRegister(string sym) {
        pa.setSym(sym);
        shared_ptr<doctor> bookform = doc.check(pa);
        dq.push(bookform);
        return ;
    }

    void treat() {
        for(auto doc = dq.front(); !dq.empty(); dq.pop())
            doc->execute();
        return ;
    }
};

