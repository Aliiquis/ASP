//
// Created by Fran on 1 Feb 2024.
//
#include <iostream>
#include <memory>

#define c1 0.5
#define c2 0.5
#define D 256
#define PRIME 251
using namespace std;

template<typename T, typename K>
class IHashableValue {
public:
    virtual K GetKey() const = 0;
};

template<typename T, typename K>
class IHash {
protected:
    size_t size;
    IHashableValue<T, K> **table;
public:
    virtual void Add(IHashableValue<T, K> *element) const = 0;

    virtual IHashableValue<T, K> *Get(K key) const = 0;
};

template<typename T, typename K>
class HashQuadraticProbing : public IHash<T, K> {
public:
    HashQuadraticProbing(size_t size) {
        this->size = size;
        this->table = new IHashableValue<T, K> *[this->size];
        for (size_t i = 0; i < this->size; i++) {
            this->table[i] = nullptr;
        }
    }

    virtual IHashableValue<T, K> *Get(K key) const {
        int index = HashMultiplicationMethod(key);
        for (size_t i = 0; i < this->size; i++) {
            int addr = (int) fmod((index + c1 * i + c2 * i * i), this->size);
            if (!this->table[addr]) return nullptr;
            if (this->table[addr].GetKey() == key) {
                return this->table[addr];
            }
        }
    }
};

int ReHash(int oldHash, char leadingDigit, char lastDigit, int mostSigDigitValue) {
    int oldHashTemp = oldHash - leadingDigit * mostSigDigitValue;
    int newHashTemp = oldHashTemp * D;
    int newHash = (newHashTemp + lastDigit) % PRIME;
    if (newHash < 0) newHash += PRIME;
    return newHash;
}

template<typename T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {}

    void insert(const T &item) { insert(root, item); }

    int inorder2() { return inorder2(root); }

    void zamijeniSMax() {
        T max = INT_MIN;
        zamijeniSMax(root, max);
    }

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

    void zamijeniSMax(shared_ptr<Node> &, T &);
};

template<typename T>
void BinaryTree<T>::insert(shared_ptr<Node> &node, const T &newItem) {
    if (node) {
        if (node->item < newItem) {
            insert(node->right, newItem);
        } else if (node->item > newItem) {
            insert(node->left, newItem);
        } else {
            throw std::invalid_argument("Error: Item " + std::to_string(newItem) +
                                        " already exists in the tree.");
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
void BinaryTree<T>::zamijeniSMax(shared_ptr<Node> &node, T &max) {
    if (node) {
        zamijeniSMax(node->left, max);
        if (node->item >= max) max = node->item;
        zamijeniSMax(node->right, max);
        if (node->item >= max) max = node->item;
        node->item = max;
    }
}

int main() {
    BinaryTree<int> binaryTree;
    binaryTree.insert(3);
    binaryTree.insert(1);
    binaryTree.insert(0);
    binaryTree.insert(2);
    binaryTree.insert(5);
    binaryTree.insert(7);
    binaryTree.insert(9);

    binaryTree.zamijeniSMax();
    binaryTree.inorder2();
    return 0;
}