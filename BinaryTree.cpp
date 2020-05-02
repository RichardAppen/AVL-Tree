
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

    // Tree is empty so don't delete anything
    if (curr == nullptr) {
        return;
    }

    while (true) {

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
BinaryTree::Node* BinaryTree::remove(const string & query) const {
     Node * curr;            // Hold the current node in the search
    
    // Return false if the list is empty
    if (numElements == 0) {

        return nullptr;

    } else {

        // Start searching at the root node
        curr = root; 

        while (true) {

            // Case 1
            if (query == curr->data) {
                return curr;

            // Case 2
            } else if (query < curr->data) {

                // If there is no left subtree the query must not exist
                if (curr->leftChild == nullptr) {
                    return nullptr;
                }
            
                // Query is smaller than current -> must be in left subtree
                curr = curr->leftChild;
                
                // do the loop another time in the left subtree
                continue;

            // Case 3
            } else if (query > curr->data) {

                // If there is no right subtree the query must not exist
                if (curr->rightChild == nullptr) {
                    return nullptr;
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
 * Implement the getLeftMostNode() function correctly
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
 */
BinaryTree::Node* BinaryTree::Node::successor() {
    Node * curr;            // hold the current node in our successor search
    curr = this;

    // If the node is null return null
    if (curr == nullptr) {
        return nullptr;
    }

    // If it has no right child then return null for no sucessor
    if (curr->rightChild == nullptr) {
           return nullptr;
    }

    // Otherwise go right once
    curr = curr->rightChild;
    // Then go all the way left
    while (true) {
        
        // If we haven't hit the left leaf, keep going
        if (curr->leftChild != nullptr) {

            curr = curr->leftChild;
            continue;
        } else {

            // otherwise return the found node
            return curr;
        }


    }


}

void BinaryTree::Write() {
        BinaryTree::WriteNode(root);
}

void BinaryTree::WriteNode(BinaryTree::Node* node) {
        // If the passed in node exists, push it into our tree vector
        if (node != nullptr) {
            cout << node->data << endl;

        }

        // Recurse right, to populate the tree vector with the right subtree
        if (node->rightChild != nullptr) {
            BinaryTree::Write(node->rightChild);
        } 

        // Recurse left, to populate the tree vector with the left subtree
        if (node->leftChild != nullptr) {
            BinaryTree::Write(node->leftChild);
        } 

        // If we make it here, return
        return;



}
