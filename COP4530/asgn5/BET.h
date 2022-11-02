#ifndef BET_H
#define BET_H

#include <string>

class BET {
    public:

        // declare & define BinaryNode struct
        struct BinaryNode {
            std::string element;
            BinaryNode* left;
            BinaryNode* right;
            
            // constructor
            BinaryNode(const string& e =  string{}, BinaryNode *l = nullptr, BinaryNode *r = nullptr) : element{e}, left{l}, right{r} {}
        };

        // declare constructors and destructor
        BET();
        BET(const string& postfix);
        BET(const BET&);
        ~BET();

        // declare class functions 
        bool buildFromPostfix(const string& postfix);
        const BET& operator=(const BET &);
        void printInfixExpression();
        void printPostfixExpression();
        
        // declare getter functions
        size_t size();
        size_t leaf_nodes();
        bool empty();

    private:
        // declare helper functions
        void printInfixExpression(BinaryNode *n);
        void makeEmpty(BinaryNode* &t);
        BinaryNode* clone(BinaryNode *t);
        void printPostfixExpression(BinaryNode *n);

        size_t size(BinaryNode *t);
        size_t leaf_nodes(BinaryNode *t);

}

#include "BET.hpp"
#endif