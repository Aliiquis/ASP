//
// Created by Fran on 25 Nov 2023.
//
#include <iostream>

using namespace std;

template<typename T>
class Stack {
private:
    size_t size = 100;
    size_t increment = 100;
    T *sp;
    int tos = -1;
public:
    Stack() { sp = (T *) malloc(size * sizeof(T)); }

    Stack(size_t size) : size(size) { sp = (T *) malloc(size * sizeof(T)); }

    bool push(T el) {
        if (tos == size) {
            sp = (T *) realloc(sp, (size + increment) * sizeof(T));
            size += increment;
        }
        sp[++tos] = el;
        return true;
    }

    bool pop(T &el) {
        if (tos == -1) return false;
        el = sp[tos--];
        if (tos < size - increment && size >= increment) {
            sp = (T *) realloc(sp, (size - increment) * sizeof(T));
            size -= increment;
        }
        return true;
    }

    bool peek(T &el) {
        if (pop(el)) {
            push(el);
            return true;
        } else return false;
    }
};

int main() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    int a;
    stack.peek(a);
    cout << "Peek first: " << a << endl;
    return 0;
}