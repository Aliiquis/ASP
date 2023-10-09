#include <iostream>

using namespace std;

template<class T>
bool compare(T &first, T &second) {
    return first < second;
}

class MyClass {
public:
    int id;

    MyClass(int id) : id(id) {};

    friend bool operator<(MyClass &first, MyClass &second);
};

bool operator<(MyClass &first, MyClass &second) {
    return first.id < second.id;
}

int main() {
    MyClass myClass0(1);
    MyClass myClass1(1);
    cout << compare(myClass0, myClass1) << endl;
    return 0;
}
