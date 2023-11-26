//
// Created by Fran on 26 Nov 2023.
//
#include <iostream>

using namespace std;

template<typename T>
class List {
private:
    template<typename X>
    class ListElement {
    public:
        X el;
        ListElement<X> *next;
    };

    ListElement<T> *head = nullptr;
    ListElement<T> *tail = nullptr;
public:

    bool RemoveFirst();

    bool insert(T data);

    void print();
};

template<typename T>
bool List<T>::RemoveFirst() {
    if (!head) return false;
    ListElement<T> *t = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete t;
    return true;
}

template<typename T>
bool List<T>::insert(T data) {
    ListElement<T> *el = new(nothrow) ListElement<T>;
    if (!el) return false;
    el->next = head;
    el->el = data;
    if (!tail) tail = el;
    head = el;
    return true;
}

template<typename T>
void List<T>::print() {
    for (ListElement<T> **p = &head; *p; p = &((*p)->next)) {
        cout << (*p)->el << ' ';
    }
    cout << endl;
}

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
void preurediRed(Queue<T> *q, T v) {
    Stack<T> veci, manji, t;
    T data;
    while (q->dequeue(data)) {
        if (data < v) manji.push(data);
        else veci.push(data);
    }
    while (veci.pop(data)) t.push(data);
    while (manji.pop(data)) t.push(data);
    while (t.pop(data)) q->enqueue(data);
}

bool jestPodskup(int A[], int B[], int m, int n) {
    if (n == 0) return true;
    if (m == 0) return false;
    if (A[0] == B[0]) return jestPodskup(++A, ++B, --m, --n);
    else return jestPodskup(++A, B, --m, n);
}

template<typename T>
bool RemoveAllFromList(List<T> *lista) {
    bool removed = false;
    while (lista->RemoveFirst()) removed = true;
    return removed;
}

int main() {
    Queue<int> q;
    /*q.enqueue(4);
    q.enqueue(1);
    q.enqueue(5);
    q.enqueue(7);
    q.enqueue(8);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(9);*/
    q.enqueue(14);
    q.enqueue(11);
    q.enqueue(5);
    q.enqueue(7);
    q.enqueue(8);
    q.enqueue(9);
    preurediRed(&q, 5);
    q.print();

    int A[]{1, 2, 4, 6, 7, 9}, B[]{1, 2, 4, 6, 7, 9, 10};
    //cout << jestPodskup(A, B, 6, 7);

    List<int> l;
    cout << RemoveAllFromList(&l) << endl;
    l.print();
    return 0;
}