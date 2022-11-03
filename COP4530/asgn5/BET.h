#ifndef BET_H
#define BET_H

#include <string>

namespace cop4530 {

    template <typename T>
    class BET {
        public:

            // declare & define BinaryNode struct
            struct BinaryNode {
                T element;
                BinaryNode* left;
                BinaryNode* right;
                
                // constructor
                BinaryNode(const T& e =  T{}, BinaryNode *l = nullptr, BinaryNode *r = nullptr) : element{e}, left{l}, right{r} {}
            };

            // declare constructors and destructor
            BET();
            BET(const string& postfix);
            BET(const BET& tree);
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

            // stores pointer to tree root
            BinaryNode* root;

    }
}

#include "BET.hpp"
#endif