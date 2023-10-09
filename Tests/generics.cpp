#include <iostream>

using namespace std;

template<class T>
T compare(T &first, T &second) {
    return first < second;
}

int main() {
    int i = 5, j = 10;
    cout << compare(i, j) << endl;
    return 0;
}
