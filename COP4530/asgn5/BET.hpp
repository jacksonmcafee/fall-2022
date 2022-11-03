#include <stack>
#include "Bet.h"

using namespace cop4530;

/* Constructors and Destructor */

template <typename T>
// default constructor, root created
BET<T>::BET() {
    root = new BinaryNode;
}

template <typename T>
// postfix constructor
BET<T>::BET(const string& postfix) {
    root = new BinaryNode;
    buildFromPostfix(postfix);
}

template <typename T>
// copy constructor
BET<T>::BET(const BET& tree) {
    // use clone function to copy to root from tree.root
    root = clone(tree.root);
}

template <typename T>
// destructor
BET<T>::~BET() {
    // use makeEmpty to recursively destroy tree subtrees
    makeEmpty(root);
}

/* Class Functions */

template <typename T>
bool BET<T>::buildFromPostfix(const string& postfix) {

}

template <typename T>
const BET& BET<T>::operator=(const BET& tree) {
    // clear base tree, clone other tree
    makeEmpty(root);
    root = clone(tree.root);
}

template <typename T>
void BET<T>::printInfixExpression() {

}

template <typename T>
void BET<T>::printPostfixExpression() {

}

/* Getter Functions */
template <typename T>
size_t BET<T>::size() {
    // get size of tree recursively by calling helper size on root
    return size(root);
}

template <typename T>
size_t BET<T>::leaf_nodes() {
    // get count on leaves by calling helper leaf_nodes on root
    return leaf_nodes(root);
}

template <typename T>
bool BET<T>::empty() {
    if (root == nullptr) {
        return false;
    }
    return true;
}


/* Helper Functions */
template <typename T>
void BET<T>::printInfixExpression(BinaryNode *n) {

}

template <typename T>
void BET<T>::makeEmpty(BinaryNode* &t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
}

template <typename T>
BinaryNode* BET<T>::clone(BinaryNode *t) {
    // create new node down T
    if (t != nullptr) {
        return new BinaryNode(t->data, clone(t->left), clone(t->right));
    }
    return nullptr;
}

template <typename T>
void BET<T>::printPostfixExpression(BinaryNode *n) {

}

template <typename T>
// recursively add nodes
size_t BET<T>::size(BinaryNode *t) {
    if (t == nullptr) {
        return 0;
    }
    else {
        size_t s = 1;
        s += size(t->left);
        s += size(t->right);
        return s;

        // return (1 + size(t->left) + size(t->right));
    }
}

template <typename T>
// recursively count leaves
size_t BET<T>::leaf_nodes(BinaryNode *t) {
    if (t != nullptr) {
        if ((t->left == nullptr) && (t->right == nullptr)) {
            return 1;
        }
        else {
            return leaf_nodes(t->left) + leaf_nodes(t->right);
        }
    }
    return 0;
}