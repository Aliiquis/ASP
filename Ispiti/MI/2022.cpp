//
// Created by Fran on 26 Nov 2023.
//
#include <iostream>

using namespace std;

template<typename T>
class ListElement {
public:
    T val;
    ListElement<T> *next;
    ListElement<T> *prev;
};

template<typename T>
class DoubleList {
private:
    ListElement<T> *head = nullptr;
    ListElement<T> *tail = nullptr;
public:
    void AddFirst(T val) {
        ListElement<T> *el = new(nothrow) ListElement<T>;
        if (!el) return;
        el->val = val;
        el->prev = nullptr;
        el->next = head;
        head = el;
        if (el->next) el->next->prev = el;
        if (!tail) tail = el;
    }

    bool Find(T val) {
        for (ListElement<T> *p = head; p; p = p->next) {
            if (p->val == val) return true;
        }
        return false;
    }

    ~ DoubleList() {
        tail = nullptr;
        while (head) {
            ListElement<T> *t = head;
            head = head->next;
            delete t;
        }
    }
};

int main() {
    DoubleList<int> dl;
    dl.AddFirst(5);
    dl.AddFirst(4);
    dl.AddFirst(3);
    dl.AddFirst(2);
    dl.AddFirst(1);
    return 0;
}