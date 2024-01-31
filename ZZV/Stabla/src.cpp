//
// Created by Fran on 31 Jan 2024.
//
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {}

    void insert(const T &item) { insert(root, item); }

    bool remove(const T &item) { return remove(root, item); }

    bool search(const T &item) { return search(root, item); }

    int countNodes() { return countNodes(root); }

    int inorder2() { return inorder2(root); }

    int countLevel(int level) { return countLevel(root, 1, level); }

    void freeAllNodes() { return freeAllNodes(root); }

    T nthValue(int n) {
        T num;
        nthValue(root, num, n);
        return num;
    }

    void changeValues() { return changeValues(root); }

    int sumLevel(int level) { return sumLevel(root, 1, level); }

private:
    struct Node {
        T item;
        shared_ptr<Node> left;
        shared_ptr<Node> right;

        Node(const T &newItem) : item(newItem), left(nullptr), right(nullptr) {}
    };

    shared_ptr<Node> root;

    void insert(shared_ptr<Node> &, const T &);

    bool remove(shared_ptr<Node> &, const T &);

    bool search(shared_ptr<Node> &, const T &);

    int countNodes(shared_ptr<Node> &);

    int inorder2(shared_ptr<Node> &);

    int countLevel(shared_ptr<Node> &, int, int &);

    void freeAllNodes(shared_ptr<Node> &);

    void nthValue(shared_ptr<Node> &, T &, int &);

    void changeValues(shared_ptr<Node> &);

    int sumLevel(shared_ptr<Node> &, int, int &);
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
bool BinaryTree<T>::search(shared_ptr<Node> &node, const T &item) {
    if (node) {
        if (node->item < item) {
            return search(node->right, item);
        } else if (node->item > item) {
            return search(node->left, item);
        } else { // found item
            return true;
        }
    }
    return false;
}

template<typename T>
bool BinaryTree<T>::remove(shared_ptr<Node> &node, const T &item) {
    if (node) {
        if (node->item < item) {
            return remove(node->right, item);
        } else if (node->item > item) {
            return remove(node->left, item);
        } else {              // found item
            if (!node->left) { // no left subtree
                node = node->right;
            } else if (!node->right) { // no right subtree
                node = node->left;
            } else {
                shared_ptr<Node> tmp = node->left, prev = nullptr;
                while (tmp->right) { // find the rightmost child in the left subtree
                    prev = tmp;
                    tmp = tmp->right;
                }
                node->item = tmp->item;
                if (prev)
                    prev->right = tmp->left;
                else
                    node->left = tmp->left;
            }
            return true;
        }
    }
    return false;
}

template<typename T>
int BinaryTree<T>::countNodes(shared_ptr<Node> &node) {
    if (!node) return 0;
    int n = 1;
    if (node->left) n += countNodes(node->left);
    if (node->right) n += countNodes(node->right);
    return n;
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
int BinaryTree<T>::countLevel(shared_ptr<Node> &node, int curr, int &level) {
    if (curr > level) return 0;
    if (curr == level) return 1;
    else {
        int n = 0;
        if (node->left) n += countLevel(node->left, curr + 1, level);
        if (node->right) n += countLevel(node->right, curr + 1, level);
        return n;
    }
}

template<typename T>
void BinaryTree<T>::freeAllNodes(shared_ptr<Node> &node) {
    if (!node) return;
    freeAllNodes(node->left);
    freeAllNodes(node->right);
    node = nullptr;
}

template<typename T>
void BinaryTree<T>::nthValue(shared_ptr<Node> &node, T &num, int &n) {
    if (node->right) nthValue(node->right, num, n);
    --n;
    if (n == 0) num = node->item;
    if (node->left) nthValue(node->left, num, n);
}

template<typename T>
void BinaryTree<T>::changeValues(shared_ptr<Node> &node) {
    if (!node) return;
    int sum = 0;
    if (node->left) sum += node->left->item;
    if (node->right) sum += node->right->item;
    node->item = sum;
    changeValues(node->left);
    changeValues(node->right);
}

template<typename T>
int BinaryTree<T>::sumLevel(shared_ptr<Node> &node, int curr, int &level) {
    if (curr > level) return 0;
    if (curr == level) return node->item;
    else {
        int n = 0;
        if (node->left) n += sumLevel(node->left, curr + 1, level);
        if (node->right) n += sumLevel(node->right, curr + 1, level);
        return n;
    }
}

int main() {

    BinaryTree<int> binaryTree;
    binaryTree.insert(5);
    binaryTree.insert(1);
    binaryTree.insert(3);
    binaryTree.insert(7);
    binaryTree.insert(6);
    binaryTree.insert(8);

    cout << "number of nodes: " << binaryTree.countNodes() << endl;
    cout << "inorder: ";
    binaryTree.inorder2();
    cout << endl;
    cout << "count at level: " << binaryTree.countLevel(3) << endl;
    //binaryTree.freeAllNodes();
    cout << "nth largest: " << binaryTree.nthValue(3) << endl;
    //binaryTree.changeValues();
    //binaryTree.inorder2();
    cout << "sum of nth level: " << binaryTree.sumLevel(3) << endl;

    return 0;
}