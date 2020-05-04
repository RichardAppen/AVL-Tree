#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * Class to implement a Binary Search Tree (BST)
 */
class BinaryTree {
    public:
        /**
         * Nested helper Node class
         */
        class Node {
            public:
                /**
                 * The data stored within a node
                 */
                string data;

                /**
                 * Pointer to the node's left child
                 */
                Node* leftChild;

                /**
                 * Pointer to the node's right child
                 */
                Node* rightChild;

                /**
                 * Pointer to the node's parent
                 */
                Node* parent;

                /**
                 * Node constructor, which initializes everything
                 */
                Node(string d) : data(d), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}

                /**
                 * Find the successor of this Node
                 *
                 * @return Node* Pointer to the successor of this Node, or nullptr if none exists
                 */
                Node* successor();
        };

        /**
         * BST Constructor, which should initialize an empty BST
         */
        BinaryTree();

        /**
         * BST Destructor, which should deallocate anything dynamic
         */
        ~BinaryTree();

        /**
         * Insert a new element to this BST
         *
         * @param element The new element to insert
         * @return true if the insertion was successful, otherwise false (e.g. duplicate)
         */
        bool insert(string element);

        /*
         * Remove an existing element
         *
         * @param query to be rmeoveed
         * @return 1 for success 0 for failure
         */
        int remove(const string & query);

        /**
         * Find a query element in this BST
         *
         * @param query The query element to find
         * @return true if query exists in this BST, otherwise false
         */
        bool find(const string & query) const;

        /**
         * Return the left-most node in this BST
         *
         * @return The left-most node in this BST
         */
        Node* getLeftMostNode();

        /**
         * Remove all elements from the BST
         */
        void clear();

        /**
         * Return the number of elements in the BST
         *
         * @return The number of elements in the BST
         */
        unsigned int size() const;


        unordered_map<string,int> balanceFactors();

        void Write();

        void AVLLeft(Node * node);
        void AVLRight(Node * node);
        void DoubleAVLLeftKink(Node * node);
        void DoubleAVLRightKink(Node * node);

    private:
        /**
         * Pointer to the root node of this BST
         */
        Node* root;

        /**
         * Total number of elements currently in the BST
         */
        unsigned int numElements;
};
#endif
