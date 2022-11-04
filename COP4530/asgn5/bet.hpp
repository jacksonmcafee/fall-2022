#include <string>
#include <iostream>
#include <sstream>
#include <stack>

#include "bet.h"

/* Functions for Expression Comp */
bool isOperator(std::string s);
bool isOperand(std::string s);
int precedence(std::string s);

/* Constructors and Destructor */

template <typename T>
// default constructor, root created
BET<T>::BET() {
    root = new BinaryNode;
}

template <typename T>
// postfix constructor
BET<T>::BET(const std::string& postfix) {
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
bool BET<T>::buildFromPostfix(const std::string& postfix) {
    
    // if string is empty, return false
    if (postfix.size() == 0) {
        std::cout << "Postfix expression is invalid." << std::endl;
        root = nullptr;
        return false;
    }
    
    // prep tokenized string using stringstream
    std::string token;
    std::stringstream ss(postfix);

    // create stack to push nodes to while constructing 
    std::stack<BinaryNode*> t_stack;

    // clear in case tree is not empty at time of calling
    makeEmpty(root);

    // while sstream isn't empty, push new string to token
    while (ss >> token) {
        // create node
        BinaryNode* node = new BinaryNode(token);

		// if operand, push node to stack
        if (isOperand(token)) {
            t_stack.push(node);
        }
		// if operator AND stack doesn't have 2 operands, fail and return false
        else if (isOperator(token) && t_stack.size() < 2) {
            std::cout << "Postfix expression is invalid." << std::endl;
            root = nullptr;
            return false;
        }
        else {
			// push top stack node left and pop it
            node->left = t_stack.top();
            t_stack.pop();
			// push top stack node right and pop it
            node->right = t_stack.top();
            t_stack.pop();
			// push current node
            t_stack.push(node);
        }
    }

	// if there is 1 remaining node, make it tree root
    if ((t_stack.size() == 1)){
        root = t_stack.top();
        t_stack.pop();
    }
    else {
		// if more/less than one node exist, throw and return false
        std::cout << "Postfix expression is invalid." << std::endl;
        return false;
    }

    return true;
}

template <typename T>
// copy operator
const BET<T>& BET<T>::operator=(const BET& tree) {
    // clear base tree, clone other tree
	// could have if (empty()) but you might as well clear it anyways
    makeEmpty(root);
    root = clone(tree.root);
    return *this;
}

template <typename T>
void BET<T>::printInfixExpression() {
	// run recursive infix print on root
    printInfixExpression(root);
    std::cout << std::endl;
}

template <typename T>
void BET<T>::printPostfixExpression() {
	// run recursive postfix print on rot
    printPostfixExpression(root);
    std::cout << std::endl;
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
// if no root, tree is empty
bool BET<T>::empty() {
    if (root == nullptr) {
        return false;
    }
    return true;
}

/* Helper Functions */
template <typename T>
void BET<T>::printInfixExpression(BinaryNode *n) {
    bool isParen = false;

    // inorder transversal of tree to get infix notation
    if (n == nullptr) {
        // if nothing in (sub)tree, return immediately
        return;
    }
    else if (n->left == nullptr && n->right == nullptr) {
        // if size == 1, print current element
        std::cout << n->element << " ";
    }
    else {
        // check to see if parenthesis are needed
		// this code concept was sourced from Baeldung, implemented myself
        if (isOperator(n->element) && isOperator(n->right->element)) {
            if (precedence(n->element) >= precedence(n->right->element)) {
                if (precedence(n->element) == 1) {
                    std::cout << "( ";
                    isParen = true;
                }
            }
        }
        
        // print down right subtree
        printInfixExpression(n->right);

        // print matching parenthesis then reset bool
        if (isParen) {
            std::cout << ") ";
        }
        isParen = false;

        // print out root
        std::cout << n->element << " ";

        // check to see if parenthesis are needed
		// same as above, just swapped for left
        if (isOperator(n->element) && isOperator(n->left->element)) {
            if (precedence(n->element) >= precedence(n->left->element)) {
                if (precedence(n->element) == 1) {
                    std::cout << "( ";
                    isParen = true;
                }
            }
        }

        // print down left subtree
        printInfixExpression(n->left);

        // print matching parenthesis
        if (isParen) {
            std::cout << ") ";
        }
    }
}

template <typename T>
void BET<T>::makeEmpty(BinaryNode* &t) {
    if (t != nullptr) {
        // try to delete left/right subtrees and then delete this node
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
}

template <typename T>
typename BET<T>::BinaryNode* BET<T>::clone(BinaryNode *t) {
    // create new node down t
    if (t != nullptr) {
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
    }
    return nullptr;
}

template <typename T>
void BET<T>::printPostfixExpression(BinaryNode *n) {
    if (n == nullptr) {
        // if nothing in (sub)tree, return immediately
        return;
    }
    else if (n->left == nullptr && n->right == nullptr) {
        // if size == 1, print current element
        std::cout << n->element << std::endl;
    }
    else {
        // run down nodes left and right, then print this node
        printPostfixEspression(n->right);
        printPostfixExpression(n->left);
        std::cout << n->element << " ";
    }
}

template <typename T>
// recursively add nodes
size_t BET<T>::size(BinaryNode *t) {
    if (t == nullptr) {
        return 0;
    }
    else {
        // count this node, then check its left/right nodes
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
		// if no nodes left or right, this node is a leaf
        if ((t->left == nullptr) && (t->right == nullptr)) {
            return 1;
        }
        else {
			// if more nodes left or right, this node isn't a leaf
            return leaf_nodes(t->left) + leaf_nodes(t->right);
        }
    }
	// nullptr passed, so no leaves
    return 0;
}

// check if passed string is an operator, same as in asgn4
bool isOperator(std::string s) {
    if (s == "*" || s == "/" || s == "+" || s == "-") {
        return true;
    }
    return false;
}

// check if passed string is an operand, same as in asgn4
bool isOperand(std::string s){
    for (char ch : s) {
        if (isalnum(ch)) {
            return true;
        }
    }
    return false;
}

// check precedence of passed string, same as in asgn4
int precedence(std::string s) {
    if (s == "(" || s == ")") {
        return 2;
    }
    else if (s == "*" || s == "/") {
        return 1;
    }
    else if (s == "+" || s == "-") {
        return 0;
    }
    return -1;
}
