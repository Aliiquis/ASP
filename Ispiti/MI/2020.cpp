//
// Created by Fran on 26 Nov 2023.
//
#include <iostream>

using namespace std;

template<class T>
struct Atom {
    T data;
    Atom *next;
};

template<class T>
class Stack {
private:
    Atom<T> *head = nullptr;
public:
    bool push(T data);

    bool pop(T &data);

    void print();
};

template<class T>
bool Stack<T>::push(T data) {
    Atom<T> *e = new Atom<T>;
    if (!e) return false;
    e->data = data;
    e->next = head;
    head = e;
    return true;
}

template<class T>
bool Stack<T>::pop(T &data) {
    if (!head) return false;
    Atom<T> *t = head;
    data = head->data;
    head = head->next;
    delete t;
    return true;
}

template<class T>
void Stack<T>::print() {
    for (Atom<T> **p = &head; *p; p = &((*p)->next)) {
        cout << (*p)->data << ' ';
    }
    cout << endl;
}

template<class T>
class List {
private:
    Atom<T> *head = nullptr;
public:
    bool insert(T data);

    void print();

    void kopirajParne(List<T> &dstList);
};

template<class T>
bool List<T>::insert(T data) {
    Atom<T> *e = new Atom<T>;
    if (!e) return false;
    e->data = data;
    e->next = head;
    head = e;
    return true;
}

template<class T>
void List<T>::print() {
    for (Atom<T> **p = &head; *p; p = &((*p)->next)) {
        cout << (*p)->data << ' ';
    }
    cout << endl;
}

template<class T>
void List<T>::kopirajParne(List<T> &dstList) {
    List<T> temp;
    for (Atom<T> **p = &head; *p; p = &((*p)->next)) {
        if ((*p)->data % 2 == 0) {
            temp.insert((*p)->data);
        }
    }
    for (Atom<T> **p = &(temp.head); *p; p = &((*p)->next)) {
        dstList.insert((*p)->data);
    }
}

bool isPalindrome(string str) {
    Stack<char> s;
    char c;
    for (int i = 0; i < str.length(); i++) {
        if (i < (str.length() / 2)) {
            s.push(str.at(i));
        } else if (i == (str.length() / 2) && str.length() % 2 != 0) {
            // ništa
        } else {
            s.pop(c);
            if (c != str[i]) return false;
        }
    }
    return true;
}

int main() {
    string s = "abba";
    cout << isPalindrome(s) << endl;

    List<int> srcList, dstList;
    srcList.insert(3);
    srcList.insert(2);
    srcList.insert(8);
    srcList.insert(6);
    srcList.insert(1);
    srcList.insert(7);
    srcList.insert(4);
    srcList.insert(5);
    srcList.print();
    srcList.kopirajParne(dstList);
    dstList.print();
    return 0;
}