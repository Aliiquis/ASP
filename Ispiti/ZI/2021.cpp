//
// Created by Fran on 1 Feb 2024.
//
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

using namespace std;

template<typename T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {}

    void insert(const T &item) { insert(root, item); }

    int inorder2() { return inorder2(root); }

    int zamijeniVecim(BinaryTree<T> drugoBS) { return zamijeniVecim(root, drugoBS.root); }

private:
    struct Node {
        T item;
        shared_ptr<Node> left;
        shared_ptr<Node> right;

        Node(const T &newItem) : item(newItem), left(nullptr), right(nullptr) {}
    };

    shared_ptr<Node> root;

    void insert(shared_ptr<Node> &, const T &);

    int inorder2(shared_ptr<Node> &);

    int zamijeniVecim(shared_ptr<Node> &, shared_ptr<Node> &);
};

template<typename T>
void BinaryTree<T>::insert(shared_ptr<Node> &node, const T &newItem) {
    if (node) {
        if (node->item <= newItem) {
            insert(node->right, newItem);
        } else if (node->item > newItem) {
            insert(node->left, newItem);
        }
    } else {
        node = std::make_shared<Node>(newItem);
    }
}

template<typename T>
int BinaryTree<T>::inorder2(shared_ptr<Node> &node) {
    int n = 1;
    if (node->left) n += inorder2(node->left);
    cout << node->item << ' ';
    if (node->right) n += inorder2(node->right);
    return n;
}

template<typename T>
int BinaryTree<T>::zamijeniVecim(shared_ptr<Node> &prvo, shared_ptr<Node> &drugo) {
    if (!drugo) return 0;
    int n = 0;
    if (!prvo->left && drugo->left) {
        prvo->left = make_shared<Node>(drugo->left->item);
        n++;
    }
    if (!prvo->right && drugo->right) {
        prvo->right = make_shared<Node>(drugo->right->item);
        n++;
    }
    if (prvo && prvo->item < drugo->item) {
        prvo->item = drugo->item;
        n++;
    }
    return n + zamijeniVecim(prvo->left, drugo->left) + zamijeniVecim(prvo->right, drugo->right);
}

template<typename T>
class Vertex {
public:
    T item;
    vector<Vertex<T> *> next;
    vector<double> weights;
    Vertex<T> *previous = nullptr;
    double distance = INFINITY;
    bool traversed = false;

    Vertex(T item) { this->item = item; }
};

class DGraph {
public:
    Vertex<int> *v0;
    vector<Vertex<int> *> allVertices;

    DGraph() { /* kôd za kontruktor klase */ }

    void Dijkstra() { /* implementacija Dijk. Algor, */ }

    void PrintPath(Vertex<int> *v) {
        if (!v) return;
        PrintPath(v->previous);
        cout << v->item << " -> ";
    }
};

template<typename T, typename K>
class IHashableValue {
public:
    virtual K GetKey() const = 0;
};

template<typename T, typename K>
class HashElement {
public:
    IHashableValue<T, K> *value;
    HashElement *next;

    HashElement(IHashableValue<T, K> *value) { this->value = value; }
};

template<typename T, typename K>
class IHash {
protected:
    size_t size;
    HashElement<T, K> **hash;
public:
    virtual void Add(IHashableValue<T, K> *element) const = 0;

    virtual IHashableValue<T, K> *Get(K key) const = 0;
};

template<typename T, typename K>
class HashChaining : public IHash<T, K> {
private:
    int HashChangeBaseMethod(int key, size_t hashSize) {
        int hash = 0, base = 1;
        while (key > 0) {
            hash += (key % 10) * base;
            key /= 10;
            base *= 11;
        }
        return hash % hashSize;
    }

public:
    virtual void Add(IHashableValue<T, K> *element) const {
        int addr = HashChangeBaseMethod(element->GetKey(), this->size);
        if (this->hash[addr]) {
            HashElement<T, K> *head = this->hash[addr];
            for (; head && head->next; head = head->next);
            head->next = new HashElement<T, K>(element);
        } else {
            this->hash[addr] = new HashElement<T, K>(element);
        }
    }

    virtual IHashableValue<T, K> *Get(K key) const {
        int addr = HashChangeBaseMethod(key, this->size);

        HashElement<T, K> *head = this->hash[addr];
        for (; head && head->value->GetKey() != key; head = head->next);

        return head ? head->value : nullptr;
    }
};

int main() {
    BinaryTree<int> prvo, drugo;

    prvo.insert(12);
    prvo.insert(9);
    prvo.insert(5);
    prvo.insert(13);
    prvo.insert(15);

    drugo.insert(12);
    drugo.insert(9);
    drugo.insert(14);
    drugo.insert(10);
    drugo.insert(11);
    drugo.insert(15);
    drugo.insert(19);

    prvo.inorder2();
    cout << endl;
    drugo.inorder2();
    cout << endl;

    int changes = prvo.zamijeniVecim(drugo);
    prvo.inorder2();
    cout << endl << "changed: " << changes;

    /* 2 3 6 4 5 2
     * 2 5 6 4 3 2
     * 6 5 2 4 3 2 */

    /* 6 5 2 4 3 2
     * 2 5 2 4 3 6
     * 5 4 2 2 3 6
     * 3 4 2 2 5 6
     * 4 3 2 2 5 6
     * 2 3 2 4 5 6
     * 3 2 2 4 5 6
     * 2 2 3 4 5 6
     * 2 2 3 4 5 6
     * 2 2 3 4 5 6 */

    /* AACCBAAACCBAAC
     * 01000122345673 */

    return 0;
}