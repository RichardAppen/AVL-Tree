
#include "BinaryTree.h"



    /**
     * Determine the height of a given node
     */
    int height(BinaryTree::Node * node) {
        int rightHeight;
        int leftHeight;
        int trueHeight;

        if (node == nullptr) {
            return 0;
        }

        // Base Case: We are at a leaf, so it's height is 0
        if (node->rightChild == nullptr && node->leftChild == nullptr) {
            return 1;

        // Recursive Case: Recurse left or right, adding 1 to the corresponding
        // height for each layer you go down.
        } else {
            
            // confirm that there is a right child before recursing right
            if (node->rightChild != nullptr) {
                rightHeight = height(node->rightChild) + 1;
            }

            // confirm that there is a left child before recursing left
            if (node->leftChild != nullptr) {
                leftHeight = height(node->leftChild) + 1;
            }
        }

        // Determine which of the two heighs is the true height
        if (rightHeight > leftHeight) {
            trueHeight = rightHeight;
        } else {
            trueHeight = leftHeight;
        }

        // return it
        return trueHeight;

    }

    /**
     * Determine the balance factor of a given node
     */
    int whatIsMyBalanceFactor(BinaryTree::Node * node) {
       int rightHeight;                 
       int leftHeight;
       
       // Set right Hegiht and left Height using the height() method
       rightHeight = height(node->rightChild);
       leftHeight = height(node->leftChild);

        // Balance = (right height) - (left height)
       return rightHeight - leftHeight;

    }

    /**
     * Populate a vector of Node pointers with each and every node inside of
     * a given Binary Tree object. Return void since we are using a reference
     * to the vector we want to change
     */
    void vectorOfNodes(vector<BinaryTree::Node *> & treeVec, BinaryTree::Node * node) {

        // If the passed in node exists, push it into our tree vector
        if (node != nullptr) {
            treeVec.push_back(node);

        }

        // Recurse right, to populate the tree vector with the right subtree
        if (node->rightChild != nullptr) {
            vectorOfNodes(treeVec, node->rightChild);
        } 

        // Recurse left, to populate the tree vector with the left subtree
        if (node->leftChild != nullptr) {
            vectorOfNodes(treeVec, node->leftChild);
        } 

        // If we make it here, return
        return;
        

    }


/**
 * Implement balanceFactors() correctly
 */
unordered_map<string,int> BinaryTree::balanceFactors() {
    unordered_map<string,int> bf;              // the map to return
    vector<Node *> treeVec;                 // vector of all the node pointers in the tree
    int sizeOfTreeVec;
    int currBalanceFactor;                  // Hold the bf of the current iteration
    string currData;                          // Hold the data of the current node

    // Populate the tree vector starting at the root
    vectorOfNodes(treeVec, root);         
    
    // set the size for the loop
    sizeOfTreeVec = treeVec.size();

    // Loop through every node pointer in the tree (by using the tree vector)
    for (int i = 0; i < sizeOfTreeVec; i++) {

        // Set the current balance and data
        currBalanceFactor = whatIsMyBalanceFactor(treeVec[i]);
        currData = treeVec[i]->data;

        // Populate the map
        bf[currData] = currBalanceFactor;
    }

    return bf;


}

/**
 * Implement the BST constructor
 */
BinaryTree::BinaryTree() {
    
    //empty tree has no root and 0 elements
    root = nullptr;
    numElements = 0;
}

/**
 * Implement the BST destructor
 */
BinaryTree::~BinaryTree() {
    
    // Clear all nodes if the tree wasn't empty
    if (numElements != 0) {
        clear();
    }
}



/**
 * Implement size() correctly
 */
unsigned int BinaryTree::size() const {
    
    // Return the number of elements in the BST
    return numElements; 
}

/**
 * Implement clear() correctly without memory leaks
 */
void BinaryTree::clear() {
    Node * curr;            // Hold the current node
    curr = root;            // Start at the root
    bool running = true;

    // Tree is empty so don't delete anything
    if (curr == nullptr) {
        return;
    }

    while (running) {

        // Tree is not empty; start by going all the way left
        if (curr->leftChild != nullptr) {

            curr = curr->leftChild;
            continue;
        } else {

            // then all the way right
            if (curr->rightChild != nullptr) {

                curr = curr->rightChild;
                continue;
            } else {

                // *SPECIAL CASE: if the parent is null then we are at the root
                if (curr->parent == nullptr) {
                    delete(curr);

                    numElements -= 1;
                    
                    running = false;
                    break;
                }

                // Check if the pointer to this node is the left child of the parent
                if (curr->parent->leftChild == curr) {

                    //detach the ptr
                    curr->parent->leftChild = nullptr;

                // If not then it must be the rightChild ptr
                } else {

                    //detach the ptr
                    curr->parent->rightChild = nullptr;
                }

                // delete the node and decrement the count
                delete(curr);

                numElements -= 1;

                curr = root;

                continue;
            }

        }
       
    }
}

/**
 * Implement insert() correctly
 */
bool BinaryTree::insert(string element) {
    Node * curr;            // Hold the current node in the search
    
    // Insert the element as the root in an empty tree
    if (numElements == 0) {

        // root now holds a ptr to the newly created node
        root = new Node(element);

        // increment size
        numElements += 1;

        return true;

    } else {

        // Start searching at the root node
        curr = root; 

        while (true) {

            // Case 1: element to add is already in the tree at the current node
            if (element == curr->data) {
                
                // We have a duplicate so return false
                return false;

            // Case 2: element to add is less than the current node
            } else if (element < curr->data) {

                // no left subtree; make our element to add it's first node
                if (curr->leftChild == nullptr) {
                    
                    curr->leftChild = new Node(element);

                    // initialize our new node's parent since we know it
                    curr->leftChild->parent = curr;

                    // increment size
                    numElements += 1;

                    return true;
                }
            
                // Element to add is smaller than current -> check left subtree
                curr = curr->leftChild;
                
                // do the loop another time in the left subtree
                continue;

            // Case 3: element to add is greator than the current node
            } else if (element > curr->data) {

                // no right subtree; make our element to add it's first node
                if (curr->rightChild == nullptr) {

                    curr->rightChild = new Node(element);

                       // initialize our new node's parent since we know it
                    curr->rightChild->parent = curr;

                    // increment size
                    numElements += 1;
                    
                    return true;
                }

                // Element to add is larger than current -> check right subtree
                curr = curr->rightChild;

                // Do the loop again in the right subtree
                continue;
            }


        }



    }

}

/**
 * Implement remove()
 */
int BinaryTree::remove(const string & query) {
     Node * curr;            // Hold the current node in the search
     Node * successor;
    
    // Return fail if the list is empty
    if (numElements == 0) {

        return 0;

    } else {

        // Start searching at the root node
        curr = root; 

        while (true) {

            // Case 1
            if (query == curr->data) {

                // Node we are to remove is a leaf node
                if (curr->leftChild == nullptr && curr->rightChild == nullptr) {
                    
                    if (curr->parent != nullptr) {
                        
                        // Find what the pointer in the parent is and set it to null
                        if (curr == curr->parent->leftChild) {
                          curr->parent->leftChild = nullptr;
                        } else {
                          curr->parent->rightChild = nullptr;
                        }

                    } else {
                        root = nullptr;
                    }

                } else if (curr->leftChild != nullptr && curr->rightChild == nullptr) {
                    
                    if (curr->parent != nullptr) {
                        // Find what the pointer in the parent is and set it to the left child
                        if (curr == curr->parent->leftChild) {
                            curr->parent->leftChild = curr->leftChild;
                            curr->leftChild->parent = curr->parent;
                        } else {
                            curr->parent->rightChild = curr->leftChild;
                            curr->leftChild->parent = curr->parent;
                        }
                    } else {
                        root = curr->leftChild;
                        curr->leftChild->parent = nullptr;
                    }

                } else if (curr->leftChild == nullptr && curr->rightChild != nullptr) {
                    
                    if (curr->parent != nullptr) {
                        // Find what the pointer in the parent is and set it to the right child
                        if (curr == curr->parent->leftChild) {
                            curr->parent->leftChild = curr->rightChild;
                            curr->rightChild->parent = curr->parent;
                        } else {
                        
                           curr->parent->rightChild = curr->rightChild;
                           curr->rightChild->parent = curr->parent;
                        }
                    } else {
                        this->root = curr->rightChild;
                        curr->rightChild->parent = nullptr;
                    }


                } else {
                    successor = curr->successor();

                    // The sucessor was the left child of it's parent (remove the link)
                    if (successor == successor->parent->leftChild) {
                        successor->parent->leftChild = nullptr;
                    } else {
                        successor->parent->rightChild = nullptr;
                    }

                    // Deal with parental issues
                    if (curr->parent != nullptr) {
                        if (curr == curr->parent->leftChild) {
                           curr->parent->leftChild = successor;
                            successor->parent = curr->parent;
                        } else {
                        
                            curr->parent->rightChild = successor;
                            successor->parent = curr->parent;
                        }
                    } else {
                        root = successor;
                        successor->parent = nullptr;
                    }


                    // Set all links equal to what curr's was
                    successor->leftChild = curr->leftChild;
                    successor->rightChild = curr->rightChild;

                    // If the curr had children set the parents in those children
                    if (successor->leftChild != nullptr) {

                        successor->leftChild->parent = successor;

                    } 

                    if (successor->rightChild != nullptr) {

                        successor->rightChild->parent = successor;
                    }

                    
                }

                delete(curr);

                numElements = numElements - 1;

                return 1;

            // Case 2
            } else if (query < curr->data) {

                // If there is no left subtree the query must not exist
                if (curr->leftChild == nullptr) {
                    return 0;
                }
            
                // Query is smaller than current -> must be in left subtree
                curr = curr->leftChild;
                
                // do the loop another time in the left subtree
                continue;

            // Case 3
            } else if (query > curr->data) {

                // If there is no right subtree the query must not exist
                if (curr->rightChild == nullptr) {
                    return 0;
                }

                // Query is larger than current -> must be in right subtree
                curr = curr->rightChild;

                // Do the loop again in the right subtree
                continue;
            }


        }



    }
}

/**
 * Implement find() correctly
 */
bool BinaryTree::find(const string & query) const {

    Node * curr;            // Hold the current node in the search
    
    // Return false if the list is empty
    if (numElements == 0) {

        return false;

    } else {

        // Start searching at the root node
        curr = root; 

        while (true) {

            // Case 1
            if (query == curr->data) {
                return true;

            // Case 2
            } else if (query < curr->data) {

                // If there is no left subtree the query must not exist
                if (curr->leftChild == nullptr) {
                    return false;
                }
            
                // Query is smaller than current -> must be in left subtree
                curr = curr->leftChild;
                
                // do the loop another time in the left subtree
                continue;

            // Case 3
            } else if (query > curr->data) {

                // If there is no right subtree the query must not exist
                if (curr->rightChild == nullptr) {
                    return false;
                }

                // Query is larger than current -> must be in right subtree
                curr = curr->rightChild;

                // Do the loop again in the right subtree
                continue;
            }


        }



    }
}

/**
 * Implement the getLeftMostNode() function
 */
BinaryTree::Node* BinaryTree::getLeftMostNode() {
    Node * curr;        // hold current node in the search for the left most

    // Empty tree? return a null ptr
    if (numElements == 0) {
        
        return nullptr;
    } else {

        // Start at the root
        curr = root;

        while (true) {
            
            // If the current's left child is null we have reached the leftmost
            if (curr->leftChild == nullptr) {
                return curr;

            // If not then run the loop again, advanced by one left child node
            } else {
                curr = curr->leftChild;
                continue;
            }
        }


    }
}

/**
 * Implement the BST::Node successor function correctly
 * Largest element of the left subtree
 */
BinaryTree::Node* BinaryTree::Node::successor() {
    Node * curr;            // hold the current node in our successor search
    curr = this;

    // If the node is null return null
    if (curr == nullptr) {
        return nullptr;
    }

    // If it has no left child then return null for no sucessor
    if (curr->leftChild == nullptr) {
           return nullptr;
    }

    // Otherwise go left once
    curr = curr->leftChild;
    // Then go all the way left
    while (true) {
        
        // If we haven't hit the left leaf, keep going
        if (curr->rightChild != nullptr) {

            curr = curr->rightChild;
            continue;
        } else {

            // otherwise return the found node
            return curr;
        }


    }


}



void WriteNode(BinaryTree::Node* node) {
        // If the passed in node exists, push it into our tree vector
        if (node != nullptr) {
            cout << "---------------------------------" << endl;
            cout << "Node: " << node->data << endl;

            if (node->parent != nullptr) {
            cout << "It's parent: " << node->parent->data << endl;
            } else {
            cout << "It's parent: nullptr" << endl;
            }
            
            if (node->leftChild != nullptr) {
            cout << "It's leftChild: " << node->leftChild->data << endl;
            } else {
            cout << "It's leftChild: nullptr" << endl;
            }

            if (node->rightChild != nullptr) {
            cout << "It's rightChild: " << node->rightChild->data << endl;
            } else {
            cout << "It's rightChild: nullptr" << endl;
            }

            cout << "---------------------------------" << endl;

        }

        // Recurse left, to populate the tree vector with the left subtree
        if (node->leftChild != nullptr) {
            WriteNode(node->leftChild);
        } 

        // Recurse right, to populate the tree vector with the right subtree
        if (node->rightChild != nullptr) {
            WriteNode(node->rightChild);
        } 

 

        // If we make it here, return
        return;



}

void BinaryTree::Write() {
        WriteNode(root);
}

void BinaryTree::AVLRight(Node * node) {
    Node * leftChild = node->leftChild;
    Node * kinkNode;

    // See if there is a kinkNode where lefChild < (kink) < (passed in node)
    if (leftChild != nullptr) {
            kinkNode = leftChild->rightChild;
    } else {
            kinkNode = nullptr;
    }

    Node * parent = node->parent;

    // Setup parent link
    if (parent != nullptr && node == parent->rightChild) {
        parent->rightChild = leftChild;
    } else if (parent != nullptr && node == parent->leftChild) {
        parent->leftChild = leftChild;
    }

    // Put the kink in it's correct position > leftChild
    node->leftChild = kinkNode;

    //Put passed in node where it should be; > leftChild
    leftChild->rightChild = node;


}

void BinaryTree::AVLLeft(Node * node) {
    Node * rightChild = node->rightChild;
    Node * kinkNode;

    // See if there is a kinkNode where (passed in node) < (kink) < righChild
    if (rightChild != nullptr) {
            kinkNode = rightChild->leftChild;
    } else {
            kinkNode = nullptr;
    }

    Node * parent = node->parent;

    // Setup parent link
    if (parent != nullptr && node == parent->rightChild) {
        parent->rightChild = rightChild;
    } else if (parent != nullptr && node == parent->leftChild) {
        parent->leftChild = rightChild;
    }

    // Put the kink in it's correct position < rightChild
    node->rightChild = kinkNode;

    //Put passed in node where it should be; < rightChild
    rightChild->leftChild = node;


}

void BinaryTree::DoubleAVLLeftKink(Node * node) {
        Node * leftChild;
        leftChild = node->leftChild;
        AVLLeft(leftChild);
        AVLRight(node);
}

void BinaryTree::DoubleAVLRightKink(Node * node) {
        Node * rightChild;
        rightChild = node->rightChild;
        AVLRight(rightChild);
        AVLLeft(node);
}

