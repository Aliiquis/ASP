//
// Created by Fran on 25 Nov 2023.
//
#include <iostream>

using namespace std;

template<typename T>
struct ListElement {
    T data;
    ListElement<T> *next;
};

template<typename T>
class ListIterator {
private:
    ListElement<T> *ptr = nullptr;
public:
    ListIterator<T>() : ptr(nullptr) {}

    ListIterator<T>(ListElement<T> *ptr) : ptr(ptr) {}

    ListIterator<T> &operator++(); // prefix ++
    ListIterator<T> operator++(int);// postfix ++
    bool operator!=(const ListIterator<T> &other) { return ptr != other.ptr; }

    T &operator*() { return ptr->data; }
};

template<typename T>
class List {
    ListElement<T> *head = nullptr;
public:
    typedef ListIterator<T> iterator;

    iterator begin() { return iterator(head); }

    iterator end() { return iterator(); }

    bool insert(T data) {
        ListElement<T> *element = new(nothrow) ListElement<T>;
        if (element == nullptr) return false;
        element->next = head;
        element->data = data;
        head = element;
        return true;
    }

    bool append(T data) {
        ListElement<T> *element = new(nothrow) ListElement<T>;
        if (element == nullptr) return false;
        element->next = nullptr;
        element->data = data;
        ListElement<T> **p;
        for (p = &head; *p != nullptr; p = &((*p)->next));
        *p = element;
        return true;
    }

    bool insertSorted(T data) {
        ListElement<T> *element = new(nothrow) ListElement<T>;
        if (element == nullptr) return false;
        element->data = data;
        ListElement<T> **p;
        for (p = &head; *p != nullptr && (*p)->data < data; p = &((*p)->next));
        element->next = *p;
        *p = element;
        return true;
    }

    bool remove(T data) {
        ListElement<T> **p;
        for (p = &head; *p != nullptr && (*p)->data != data; p = &((*p)->next));
        if (*p == nullptr) return false;
        ListElement<T> *t = *p;
        *p = t->next;
        delete t;
        return true;
    }

    void print() {
        ListElement<T> **p;
        for (p = &head; *p != nullptr; p = &((*p)->next)) {
            cout << (*p)->data << ' ';
        }
    }

    T &at(int k) {
        if (k < 0) throw out_of_range("Indeks izvan granica");
        ListElement<T> **p;
        int i;
        for (i = 0, p = &head; *p != nullptr && i < k; i++, p = &((*p)->next));
        if (*p == nullptr) throw out_of_range("Indeks izvan granica");
        return (*p)->data;
    }

    ListElement<T> *at2(int k) {
        if (k < 0) return nullptr;
        ListElement<T> **p;
        int i;
        for (i = 0, p = &head; *p != nullptr && i < k; i++, p = &((*p)->next));
        return *p;
    }

    int length() {
        int l = 0;
        ListElement<T> **p;
        for (p = &head; *p != nullptr; p = &((*p)->next)) l++;
        return l;
    }

    int countItem(T item) {
        int n = 0;
        ListElement<T> **p;
        for (p = &head; *p != nullptr; p = &((*p)->next)) {
            if ((*p)->data == item) n++;
        }
        return n;
    }

    void deleteAll() {
        ListElement<T> *p = head;
        while (p != nullptr) {
            ListElement<T> *t = p;
            p = p->next;
            delete t;
        }
        head = nullptr;
    }

    void reverseList() {
        ListElement<T> *p = head, *prev = nullptr, *next = nullptr;
        while (p != nullptr) {
            next = p->next;
            p->next = prev;
            prev = p;
            p = next;
        }
        head = prev;
    }

    int removeDuplicates() {
        int n = 0;
        ListElement<T> *p = head;
        while (p != nullptr) {
            if (p->next && p->data == p->next->data) {
                ListElement<T> *t = p->next;
                p->next = p->next->next;
                delete t;
                n++;
            } else p = p->next;
        }
        return n;
    }
};

int main() {
    List<int> l;
    l.append(1);
    l.append(5);
    l.insertSorted(3);
    l.insertSorted(2);
    l.insertSorted(2);
    l.insertSorted(5);
    l.print();
    cout << endl << l.removeDuplicates() << endl;
    l.print();
    return 0;
}