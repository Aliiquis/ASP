//
// Created by Fran on 26 Nov 2023.
//
#include <iostream>

using namespace std;

template<typename T>
struct ListElement {
    T data;
    ListElement<T> *next;
};

template<typename T>
class List {
    ListElement<T> *head = nullptr;
public:
    bool append(T item);

    void print();

    void removeGreaterThan(T item);
};

template<typename T>
bool List<T>::append(T item) {
    ListElement<T> *el = new(nothrow) ListElement<T>;
    if (!el) return false;
    el->data = item;
    el->next = nullptr;
    ListElement<T> **p;
    for (p = &head; *p; p = &((*p)->next));
    *p = el;
    return true;
}

template<typename T>
void List<T>::print() {
    ListElement<T> **p;
    for (p = &head; *p; p = &((*p)->next)) {
        cout << (*p)->data << ' ';
    }
    cout << endl;
}

template<typename T>
void List<T>::removeGreaterThan(T item) {
    ListElement<T> **p = &head;
    while (*p) {
        if ((*p)->data > item) {
            ListElement<T> *t = *p;
            *p = (*p)->next;
            delete t;
        } else p = &((*p)->next);
    }
}

template<class T>
class Queue {
private:
    static const int MAX = 100;
    T queue[MAX];
    int write = 0;
    int read = 0;
public:
    bool enqueue(T data);

    bool dequeue(T &data);

    void print();

    Queue<T> *split(Queue<T> *q);
};

template<class T>
bool Queue<T>::enqueue(T data) {
    if ((write + 1) % MAX == read) return false;
    queue[write] = data;
    write = (write + 1) % MAX;
    return true;
}

template<class T>
bool Queue<T>::dequeue(T &data) {
    if (read == write) return false;
    data = queue[read];
    read = (read + 1) % MAX;
    return true;
}

template<class T>
void Queue<T>::print() {
    T data;
    while (dequeue(data)) {
        cout << data << ' ';
    }
    cout << endl;
}

template<class T>
Queue<T> *Queue<T>::split(Queue<T> *q) {
    int cutoff = q->write;
    Queue<T> temp, *ret = new Queue<T>;
    T data;
    for (int j = 1, i = q->read; i < cutoff; j++, i++) {
        q->dequeue(data);
        if (j % 2 == 0) {
            q->enqueue(data);
        } else {
            temp.enqueue(data);
        }
    }
    while (temp.dequeue(data)) {
        ret->enqueue(data);
    }
    return ret;
}

bool podnizUNizu(string niz, string podniz, int pocetak) {
    if (pocetak < 0 || pocetak > niz.length() || niz.empty() && !podniz.empty()) return false;
    if (podniz.empty()) return true;
    if (pocetak == 0) {
        if (niz.at(0) == podniz.at(0)) return podnizUNizu(niz.erase(0, 1), podniz.erase(0, 1), pocetak);
        else return false;
    } else return podnizUNizu(niz.erase(0, 1), podniz, pocetak - 1);
}

int main() {
    string niz = "Dobar dan!", podniz = "dan";
    cout << podnizUNizu(niz, podniz, 6) << endl;

    List<int> l;
    l.append(1);
    l.append(2);
    l.append(3);
    l.append(4);
    l.append(2);
    l.print();
    l.removeGreaterThan(2);
    l.print();

    Queue<int> q, *t;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    t = q.split(&q);
    t->print();
    q.print();
    return 0;
}