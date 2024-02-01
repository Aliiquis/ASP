//
// Created by Fran on 1 Feb 2024.
//
#include <iostream>
#include <memory>
#include <list>

using namespace std;

template<typename T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {}

    void insert(const T &item) { insert(root, item); }

    int inorder2() { return inorder2(root); }

    int brJednoDijete() { return brJednoDijete(root); }

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

    int brJednoDijete(shared_ptr<Node> &);
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
int BinaryTree<T>::brJednoDijete(shared_ptr<Node> &node) {
    if (!node) return 0;
    int n = 0;
    if (!node->left && node->right || node->left && !node->right) n += 1;
    return n + brJednoDijete(node->left) + brJednoDijete(node->right);
}

class Graph {
    int brojVrhova;
    list<int> *listeSusjeda; // polje listi susjeda
    bool *obidjen; // polje u kome je sadržana informacija je li pojedini vrh već obidjen
public:
    Graph(int vrhovi);

    void dodajBrid(int izvor, int odrediste); // dodavanje bridova
    void postavi(); // postavljanje svih članova polja obidjen u false
    void DFS(int vrh);
};

// Inicijaliziraj graf
Graph::Graph(int vrhovi) {
    this->brojVrhova = vrhovi;
    this->listeSusjeda = new list<int>[vrhovi];
    this->obidjen = new bool[vrhovi];
}

// DFS algorithm
void Graph::DFS(int vrh) {
    cout << vrh << ' ';
    obidjen[vrh] = true;

    list<int> susjedi = listeSusjeda[vrh];
    list<int>::iterator i;

    for (i = susjedi.begin(); i != susjedi.end(); i++) {
        if (!obidjen[*i]) DFS(*i);
    }
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
    virtual void Add(IHashableValue<T, K> *element) const = 0;

    virtual IHashableValue<T, K> *Get(K key) const = 0;
};

template<typename T, typename K>
class HashDoubleHashing : public IHash<T, K> {
public:
    HashDoubleHashing(size_t size) {
        this->size = size;
        this->hash = new IHashableValue<T, K> *[this->size];
        for (size_t i = 0; i < this->size; i++) {
            this->hash[i] = nullptr;
        }
    }

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
            if (this->hash[i]->GetKey() == key) return this->hash[i];
        }
    }
};

int main() {
    BinaryTree<int> binaryTree = BinaryTree<int>();

    binaryTree.insert(3);
    binaryTree.insert(1);
    binaryTree.insert(0);
    binaryTree.insert(2);
    binaryTree.insert(5);
    binaryTree.insert(7);
    binaryTree.insert(9);
    //binaryTree.insert(8);

    cout << binaryTree.brJednoDijete();
    return 0;
}