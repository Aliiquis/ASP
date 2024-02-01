//
// Created by Fran on 1 Feb 2024.
//
#include <iostream>
#include <memory>

using namespace std;

template<class T>
class Stack {
private:
    static const int MAX = 100;
    T stack[MAX];
    int top = -1;

public:
    bool push(T item) {
        if (top >= MAX)
            return false;
        stack[++top] = item;
        return true;
    }

    bool pop(T &item) {
        if (top < 0)
            return false;
        item = stack[top--];
        return true;
    }
};

template<typename T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {}

    void insert(const T &item) { insert(root, item); }

    int inorder2() { return inorder2(root); }

    bool odrediPut(Stack<T> &put, const T &el) { return odrediPut(put, el, root); }

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

    bool odrediPut(Stack<T> &, const T &, shared_ptr<Node> &);
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
bool BinaryTree<T>::odrediPut(Stack<T> &put, const T &el, shared_ptr<Node> &node) {
    if (node) {
        if (node->item == el) {
            put.push(node->item);
            return true;
        } else if (odrediPut(put, el, node->left) || odrediPut(put, el, node->right)) {
            put.push(node->item);
            return true;
        }
    }
    return false;
}

template<typename T, typename K>
class IHashableValue {
public:
    virtual K GetKey() const = 0;
};

template<typename T, typename K>
class IHash {
protected:
    size_t size;
    IHashableValue<T, K> **hash;
public:
    IHashableValue<T, K> *Get(K key);

    void Add(IHashableValue<T, K> *element);

    float AvgCollisions();
};

template<typename T, typename K>
class HashDoubleHashing : public IHash<T, K> {
public:
    virtual void Add(IHashableValue<T, K> *element) const {
        int h1 = HashMultiplicationMethod1(element->GetKey());
        int h2 = HashMultiplicationMethod2(element->GetKey());

        for (size_t i = 0; i < this->size; i++) {
            int addr = (h1 + i * h2) % this->size;

            if (!this->hash[addr]) {
                this->hash[addr] = element;
                break;
            }
        }
    }

    virtual IHashableValue<T, K> *Get(K key) const {
        int h1 = HashMultiplicationMethod1(key);
        int h2 = HashMultiplicationMethod2(key);

        for (size_t i = 0; i < this->size; i++) {
            int addr = (h1 + i * h2) % this->size;

            if (!this->hash[addr]) return nullptr;
            if (this->hash[addr]->GetKey() == key) return this->hash[addr];
        }
    }

    float AvgCollisions() {
        int numOfColls = 0, numOfElems = 5;

        for (size_t i = 0; i < this->size; i++) {
            int h1 = HashMultiplicationMethod1(this->hash[i]->GetKey());
            int h2 = HashMultiplicationMethod2(this->hash[i]->GetKey());

            if ((h1 + 0 * h2) % this->size != i) {
                numOfElems++;

                size_t j = 0;
                while ((h1 + j * h2) % this->size != i) {
                    numOfColls++;
                    j++;
                }
            }
        }

        return numOfElems ? 1. * numOfColls / numOfElems : 0;
    }
};

int main() {
    BinaryTree<int> binaryTree;
    Stack<int> put;

    binaryTree.insert(4);
    binaryTree.insert(-3);
    binaryTree.insert(1);
    binaryTree.insert(2);
    binaryTree.insert(5);
    binaryTree.insert(10);
    binaryTree.insert(8);

    if (binaryTree.odrediPut(put, 8)) {
        int el;
        while (put.pop(el)) cout << el << ' ';
    } else cout << "Element nije u stablu.";
    return 0;
}