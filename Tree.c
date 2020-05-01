/******************************************************************************

                                                        Richard Appen 
                                                        CSE 12, Fall 2019
                                                        November 23, 2019
                                                        cs12fa19ad
                                Assignment Eight

File Name:      Tree.c
Description:  	This program creates a binary tree data structure. It allows 
		the user to create a linked tree with nodes that have a 
		left and/or right child. the user can insert a new element 
		into the tree as well as remove an existing node, or perform a search on the 
		tree to find a specific element. 
******************************************************************************/
#include <cstdlib>
#include <string>
#include "Tree.h"
using namespace std;

// messages
static const char AND[] = " and ";
static const char CHECK[] = " - Checking ";
static const char COMPARE[] = " - Comparing ";
static const char DEALLOCATE[] = " - Deallocating]\n";
static const char INSERT[] = " - Inserting ";
static const char REPLACE[] = " - Replacing ";
static const char UPDATE[] = " - Updating ";

template <class Whatever>
int Tree<Whatever>::debug = 0;   // debug field

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define THRESHOLD 2

template <class Whatever>
ostream & operator << (ostream &, const TNode<Whatever> &);

/*****************************************************************************
% 				Class TNode
%
% Description: Implements the node of the binary search tree data structure.
%     Each node contains two children, the left child which contains
%     data "less than" the data of the current node, and the right child
%     which contains data "greater than" the data of the current node.
%
% Data Fields:
%     data  - holds the data stored in the current node
%     left (Node *)  - the left child
%     right (Node *) - the right child
%     occupancy (long) - (Reference) How many TNodes in the tree
%     blanace (long) - left child's height minus right child's height
%     height (long) - 1 + height of tallest child, or 0 for leaf
%     tree_count (long) - (Reference) to the tree number this node is in
%
% Public functions:
%     TNode - Construcotr for a TNode object
%     ~TNode - Destructor for a TNode object
%     delete_AllNodes - deletes all the children of the current node
%     Write_AllNodes - display the current node and all its children
%     RemoveAndReplaceMin - Remove a node with two children
%     SetHeightAndBalance - Set the height and balance of the current node
%     Insert - Insert a new TNode or recursively call Insert
%     Remove - Remove a TNode or recursively call Remove
%     Lookup - Find a TNode or recursively call lookup
%
*****************************************************************************/
template <class Whatever>
struct TNode {
        long balance;    // left childs height minus right childs height
        Whatever data;   // Reference to the data stored in the TNoe
        long height;     // 1 + the height of the tallest child
        TNode<Whatever> * left;  // Pointer to the left child TNode
        long & occupancy;        // Reference to the occupancy field
        TNode<Whatever> * right; // Pointer to the right child TNode
        unsigned long & tree_count;  // Number of nodes in tree
       
	/***************************************************************************
	% Routine Name : TNode (public)
	% File :         Tree.c
	% 
	% Description :  Initializes all TNode data fields to zero while 
	%		 setting the data field to the passed in element reference.
	%		 Specifically for creating a node on the RTS since it will
	%		 have no parent TNode, but just connection to a tree
	%		 reference. 
	***************************************************************************/
        TNode (const Whatever & element, Tree<Whatever> & theTree)
                : balance (0), data (element), height (0), left (0), 
                occupancy (theTree.occupancy), right (0), 
                tree_count (theTree.tree_count) {

		// Increment occupancy
		occupancy = occupancy + 1;
        }
   
	/***************************************************************************
	% Routine Name : TNode (public)
	% File :         Tree.c
	% 
	% Description :  Initializes all TNode data fields to zero while 
	%		 setting the data field to the passed in element reference.
	% 		 For actual integration into a tree since it connects the new
	%		 TNode to a parent TNode. 
	***************************************************************************/   
        TNode (const Whatever & element, TNode<Whatever> & parentTNode)
        : balance (0), data (element), height (0), left (0), 
                occupancy (parentTNode.occupancy), right (0), 
                tree_count (parentTNode.tree_count) {

		// Increment occupancy
		occupancy = occupancy + 1;

        }

	/***************************************************************************
	% Routine Name : ~TNode  (public)
	% File :         Tree.c
	% 
	% Description :  deallocates memory associated with the TNode. Decrement
	%                the occupancy field.
	***************************************************************************/
        ~TNode (void) {

		// Decrement occupancy
		occupancy = occupancy - 1;

        }

	/*********************************************************************
	% Routine Name : delete_AllTNodes (public)
	% File :         Tree.c
	%
        % Description :  Deletes all TNodes children of the TNode by calling
        % 		 this recursive method which performs an post-order
        % 		 traversal of the entire tree to delete all nodes in
   	%		 the right order, as determined by the keys stored in 
	%		 each node. If no left or right child, it deletes itself 
	*********************************************************************/  
	void delete_AllTNodes (void) {
		// Go left
		if (left)
			left->delete_AllTNodes();

		// Go right
		if (right)
			right->delete_AllTNodes();
		
		// Visit
		delete this;
	}

        unsigned long Insert (const Whatever & element, 
                              TNode<Whatever> *& PointerInParent);

        unsigned long Lookup(Whatever & element) const;

 
        /***************************************************************************
	% Routine Name : ReplaceAndRemoveMin  (public)
	% File :         Tree.c
	% 
	% Description :  How to specifically deal with removing a TNode with
	%		 two children. Finds the smallest TNode in the right
	%		 subtree to replace the TNode we are removing.
	%
	% Parameters descriptions :
	% 
	% name               description
	% ------------------ ------------------------------------------------------
	% targetTNode        The TNode in the tree with 2 children
	% PointerInParent    A pointer to the current TNode this method is being
	%		     called from. How we got to the current TNode from its
	%		     parent.
	***************************************************************************/
	void ReplaceAndRemoveMin (TNode<Whatever> & targetTNode, 
                TNode<Whatever> *& PointerInParent) {

		// Debug message
		if (Tree<Whatever>::debug) {
			cerr << TREE << tree_count << CHECK << (const char *)data << "] \n"; 
		}

		// Find the sucessor node by going as far left as possible
		if (left != NULL) {
			left->ReplaceAndRemoveMin(targetTNode, left);

			SetHeightAndBalance(PointerInParent);
		} else {

			// Debug message
			if (Tree<Whatever>::debug) {
				cerr << TREE << tree_count << REPLACE << (const char *)data << "] \n"; 
			}

			// Replace the data of the target equal to that of the successor we found
			targetTNode.data = data;

			// Reset the PIP to the replaced node's child and delete the current node
			PointerInParent = right;
			delete this;
		}
        }

	/***************************************************************************
	% Routine Name : Remove  (public)
	% File :         Tree.c
	% 
	% Description :  Removes a node with the specified data, if it is actually
	%		 in the tree. Deals with different cases like removing a 
	%		 leaf node, or a node with one child, or if it's a node
	%		 with two children, it delegates to RARM. Only call SHAB
	%		 If it's not called from SHAB.
	%
	% Parameters descriptions :
	% 
	% name               description
	% ------------------ ------------------------------------------------------
	% elementTNode       A reference to a TNode on the RTS that contains data
	%		     with the same name as the TNode we want to remove
	%	 	     from the Tree
	% PointerInParent    A pointer to the current TNode this method is being
	%		     called from. How we got to this current TNode from its
	%		     parent
	% fromSHB	     Tell remove whether or not to call SHAB
	***************************************************************************/
        unsigned long Remove (TNode<Whatever> & elementTNode, 
                TNode<Whatever> *& PointerInParent,
                long fromSHB = FALSE) {

		// Case: node we made it to is NULL, so no item
		if (this == NULL) {
			return 0;
		}
		
		// Case: It's the TNode we first passed in
		if (elementTNode.data == data) {
			// Debug message
			if (Tree<Whatever>::debug) {
				cerr << TREE << tree_count << COMPARE << (const char *)elementTNode.data << AND << (const char *)data << "] \n";
			}

			// When removing a leaf node, where to set the PointerInParent
			if (left == NULL && right == NULL) {
				PointerInParent = NULL;

			// When removing a node with just a left child
			} else if (left != NULL && right == NULL) {
				PointerInParent = left;

			// When removing a node with just a right child
			} else if (right != NULL && left == NULL) {
				PointerInParent = right;

			// Call RARM when removing a node with two children
			} else if (right != NULL && left != NULL) {
				// Set RTS TNode's data to data of the real Node going away
				elementTNode.data = data;

				// Delegate
				right->ReplaceAndRemoveMin(*this, right);

				// Call SHAB
				if (!fromSHB) {
					SetHeightAndBalance(PointerInParent);
				}

				// Return successful early so not to delete the current node
				return 1;
			}

			// Set RTS TNode's  data to the data of the real Node going away
			elementTNode.data = data;

			// Deallocate this TNode
			delete this;

			// Return successful
			return 1; 
			
		// Case: It's less than current TNode
		} else if (elementTNode.data < data) {
			// Debug message
			if (Tree<Whatever>::debug) {
				cerr << TREE << tree_count << COMPARE << (const char *)elementTNode.data << AND << (const char *)data << "] \n"; 
			}

			// Since item is < current but nothing is to the left; item not in tree
			if (left == NULL) {

				// So return unsuccessful
				return 0;
			}

			// Recursively call remove on the next node to the left
			if (left->Remove(elementTNode, left) == 0) {
				return 0;
			}

			// If we weren't called from SHAB, call SHAB as we go back up the tree
			if (!fromSHB) {
				SetHeightAndBalance(PointerInParent);
			}

		// Case: It's more than the current TNode
		} else {
			// Debug message
			if (Tree<Whatever>::debug) {
				cerr << TREE << tree_count << COMPARE << (const char *)elementTNode.data << AND << (const char *)data << "] \n"; 
			}

			// since item is less than curr but nothing is to right; itme not in tree
			if (right == NULL) {
				return 0;
			}

			// Recursively call remove on the next node to the right
			if (right->Remove(elementTNode, right) == 0) {
				return 0;
			}

			// If we weren't called from SHAB, call SHAB as we go back up the tree
			if (!fromSHB) {
				SetHeightAndBalance(PointerInParent);
			}

		}

		// If we made it to here we were successful
     		return 1; 
        }

	/***************************************************************************
	% Routine Name : SetHeightAndBalance  (public)
	% File :         Tree.c
	% 
	% Description :  Set the height and balance of the node the method was
	%		 called from based on their definitions. If the balance
	%		 is over the threshold of 2 then we will remove and
	%		 reinsert the out of balance node.
	%
	% Parameters descriptions :
	% 
	% name               description
	% ------------------ ------------------------------------------------------
	% PointerInParent    A pointer to the current TNode this method is being
	%		     called from. How we got to this current TNode from its
	%		     parent
	***************************************************************************/
        void SetHeightAndBalance (TNode<Whatever> *& PointerInParent) {
 		int locLeftHeight = -1;   // Assume there is no left child
		int locRightHeight = -1;  // Assume there is no right child
		Whatever elementToSave(data);   // Save the data we will remove

		//Debug message
		if (Tree<Whatever>::debug) {
			cerr << TREE << tree_count << UPDATE << (const char *)PointerInParent->data << "] \n";
		}

		// If there is a right child update its height var
		if (right != NULL) {
			locRightHeight = right->height;
		}

		// If there is a left child update its height car
		if (left != NULL) {
			locLeftHeight = left->height;
		}
				
		// Setup height and balance based on definitions
		if (locLeftHeight > locRightHeight) {
			height = locLeftHeight + 1;
		} else {
			height = locRightHeight + 1;
		}
		balance = locLeftHeight - locRightHeight; 

		// Check balance isn't above the threshold of 2
		if (abs(balance) > THRESHOLD) {
			//save the data
			elementToSave = PointerInParent->data;
			//Remove out of balance TNode
			Remove(*PointerInParent, PointerInParent, TRUE);
			//Reinsert
			PointerInParent->Insert(elementToSave, PointerInParent);
		}
        }

	/*********************************************************************
	% Routine Name : Write_AllTNodes (public)
	% File :         Tree.c
	%
        % Description :  Writes all TNodes children by calling
        % 		 this recursive method which performs an in-order
        % 		 traversal of the entire tree to print all nodes in
        % 		 sorted order, as determined by the keys stored in each
        % 		 node. To print itself, the current node will call the
        % 		 << function on itself. 
	*********************************************************************/
        ostream & Write_AllTNodes (ostream & stream) const {
                if (left)
                        left->Write_AllTNodes (stream);
                stream << *this;
                if (right)
                        right->Write_AllTNodes (stream);

                return stream;
        }
};

/***************************************************************************
% Routine Name : Tree<Whatever> :: Set_Debug_On (public)
% File :         Tree.c
% 
% Description :  This function sets debug mode on
***************************************************************************/
template <class Whatever>
void Tree<Whatever> :: Set_Debug_On (void) {
	debug = 1;
}

/***************************************************************************
% Routine Name : Tree<Whatever> :: Set_Debug_On (public)
% File :         Tree.c
% 
% Description :  This function sets debug mode off
***************************************************************************/
template <class Whatever>
void Tree<Whatever> :: Set_Debug_Off (void) {
	debug = 0;
}

/***************************************************************************
% Routine Name : TNode<Whatever> :: Lookup  (public)
% File :         Tree.c
% 
% Description : Determine if the current node this method is being called
%		from is the node holding the element we are looking for,
%		if it's not, then recursively call this method on the next
%		most logical next node
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element            A reference to the object that we are looking for in
% 		     the tree
***************************************************************************/
template <class Whatever>
unsigned long TNode<Whatever> :: Lookup(Whatever & element) const {
	// If the element we are looking for is < the current
       	if (element < data) {
		// Debug message
		if (Tree<Whatever>::debug) {
			cerr << TREE << tree_count << COMPARE << (const char *)element << AND << (const char *)data << "] \n"; 
		}

		// Must not be in the tree, since it's less than but nothing is to the left
		if (left == NULL) {

			return 0;

		// Otherwise keep checking by recursively calling lookup
		} else { 
 			return left->Lookup(element);
		}

	// We found it
	} else if (element == data) {
		// Debug message
		if (Tree<Whatever>::debug) {
			cerr << TREE << tree_count << COMPARE << (const char *)element << AND << (const char *)data << "] \n";
		} 

		// Replace elements reference with found TNode's data
		element = data;

		// Return successful
		return 1;

	// Otherwise what we are searching for is larger
	} else {
		// Debug messages
		if (Tree<Whatever>::debug) {
			cerr << TREE << tree_count << COMPARE << (const char *)element << AND << (const char *)data << "] \n";

		}

		// Must not be in the tree, since it's more than but nothing it to the right
		if (right == NULL) {

			return 0;
		
		// Otherwise keep checking by recursively calling lookup	
		} else { 
			return right->Lookup(element);
		}
	}

}

/***************************************************************************
% Routine Name : TNode<Whatever> :: Insert  (public)
% File :         Tree.c
% 
% Description :  Inserts a new element into the tree if there is a free
%		 space, if not then recursively call this same method
%		 After the insertion then call SHAB as return back up
%		 the tree.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element            A reference to the object that the new TNode being 
%		     inserted will hold
% PointerInParent    A pointer to the current TNode this method is being
%		     called from. How we got to this current TNode from its
%		     parent
***************************************************************************/
template <class Whatever>
unsigned long TNode<Whatever> :: Insert (const Whatever & element, 
                                         TNode<Whatever> *& PointerInParent) {

	// If the element we are inserting is less than current
       	if (element < data) {
		// Debug message
		if (Tree<Whatever>::debug) {
			cerr << TREE << tree_count << COMPARE << (const char *)element << AND << (const char *)data << "] \n"; 
		}

		// If there is nothing to the left, then we can insert
		if (left == NULL) {
			// Debug message
			if (Tree<Whatever>::debug) {
				cerr << TREE << tree_count << INSERT << (const char *)element << "] \n";
			} 

			// Integrate the new TNode at the left
			left = new TNode<Whatever>(element, *this);
			SetHeightAndBalance(PointerInParent);

		// If there is something to the left, recursivelly call insert on that node
		} else { 
 			left->Insert(element, left);
			SetHeightAndBalance(PointerInParent);
		}

	// If the element we want to insert is already in the tree just replace the data
	} else if (element == data) {
		// Debug message
		if (Tree<Whatever>::debug) {
			cerr << TREE << tree_count << COMPARE << (const char *)element << AND << (const char *)data << "] \n";
			cerr << TREE << tree_count << INSERT << (const char *)element << "] \n";
		} 

		data = element;

	// If the element we are inserting is more than current
	} else {
		// Debug message
		if (Tree<Whatever>::debug) {
			cerr << TREE << tree_count << COMPARE << (const char *)element << AND << (const char *)data << "] \n";

		}

		// If there is nothing to the right, then we can insert
		if (right == NULL) {
			// Debug message
			if (Tree<Whatever>::debug) {
				cerr << TREE << tree_count << INSERT << (const char *)element << "] \n";
			} 

			// Integrate the new TNode at the right
			this->right = new TNode<Whatever>(element, *this);
			SetHeightAndBalance(PointerInParent);

		// If there is something to the right, recursivelly call insert on that node
		} else { 
			this->right->Insert(element, right);
			SetHeightAndBalance(PointerInParent);
		}
	}

	// If we made it here then we are successful
        return 1;
}

/***************************************************************************
% Routine Name : << (public)
% File :         Tree.c
% 
% Description : This function determines how the << operator should work
%		on a TNode, and how to write that TNode to the passed
% 		in stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% nnn                A reference to the TNode to write
***************************************************************************/
template <class Whatever>
ostream & operator << (ostream & stream, const TNode<Whatever> & nnn) {
        stream << "at height:  :" << nnn.height << " with balance:  "
                << nnn.balance << "  ";
        return stream << nnn.data << "\n";
}

/*****************************************************************************
%				Class Tree
%
% Description: A binary tree data structure that holds elements in it's 
% nodes that are connected in a tree like structure. This tree will self
% balance when it gets to spindly
%
% Data Fields:
%     root (TNode)  - The first Tree Node in the tree
%     occupancy (long) - How many Tree Nodes are in the tree
%     tree_count (String) - The name of the specific tree
%     debug (boolean) - static variables to determine if debug
%     			 messages should be printed
%
% Public functions:
%  Set_Debug_On - To set debug on
%  Set_Debug_Off - To set debug off
%  Tree - constructor to initialize and allocate the binary tree
%  ~Tree - destructor to deallocate the tree
%  Insert - insert a root into an empty tree or delegate to TNode's 
%  insert
%  Lookup - Delegate to TNode's lookup if the tree isn't empty
%  Remove - Create a TNode on the RTS to match in the tree, then
%  delegate to TNode's remove to remove the matching node
%  Write - How a binary tree should be written to a stream
% 
****************************************************************************/

/***************************************************************************
% Routine Name : Tree<Whatever> :: Insert  (public)
% File :         Tree.c
% 
% Description :  Inserts a new element into the tree by delegating the work
%		 to TNode's insert calling it from the tree's root. If
% 		 is no root, i.e. the tree is empty, set the new TNode
%		 to be the tree's root
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element            A reference to the object that the new TNode being 
%		     inserted will hold
***************************************************************************/
template <class Whatever>
unsigned long Tree<Whatever> :: Insert (const Whatever & element) {

	
	// Inserting the first element
	if (root == NULL) {

		// Debug message
		if (debug) {
			cerr << TREE << tree_count << INSERT << (const char *)element << "] \n";
		} 

		// Set it as the root of the tree
		root = new TNode<Whatever>(element, *this);
	
	// Inserting all other elements by calling TNode's insert on root
	} else {
		root->Insert(element, root);	

	}

	// Return successful if we made it to here
        return 1;
}

/***************************************************************************
% Routine Name : Tree<Whatever> :: Lookup  (public)
% File :         Tree.c
% 
% Description :  Looks for an element in the tree by delegating the work
%		 to TNode's lookup calling it from the tree's root. If
% 		 is no root, i.e. the tree is empty, return unsuccessful
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element            A reference to the object that the new TNode being 
%		     inserted will hold
***************************************************************************/
template <class Whatever>
unsigned long Tree<Whatever> :: Lookup (Whatever & element) const {

	// Tree is empty
	if (root == NULL) {

		// Return unsuccessful
		return 0;
	
	// Delegate to TNode's lookup
	} else {
		return root->Lookup(element);

	}

}

/***************************************************************************
% Routine Name : Tree<Whatever> :: Remove  (public)
% File :         Tree.c
% 
% Description :  Looks for an element in the tree by delegating the work
%		 to TNode's remove  calling it from the tree's root. If
% 		 is no root, i.e. the tree is empty, return unsuccessful.
%		 Creates a TNode on the RTS to match in the tree, to tell 
%		 TNode's remove what to remove.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element            A reference to the object that the new TNode being 
%		     inserted will hold
***************************************************************************/
template <class Whatever>
unsigned long Tree<Whatever> :: Remove (Whatever & element) {

	int success;   // save the success of the remove call

	// If the list is empty return unsuccessful
	if (occupancy == 0) {
		return 0;
	}

	// Call remove
	TNode<Whatever> toRemove = TNode<Whatever>(element, *this);
	success = root->Remove(toRemove, root, FALSE);

	// Reset our element to the one we found and removed
	element = toRemove.data;

	// return success
        return success;
}

template <class Whatever>
Tree<Whatever> :: Tree (void): occupancy (0), root (NULL)
/***************************************************************************
% Routine Name : Tree<Whatever> :: Tree  (public)
% File :         Tree.c
%
% Description :  Guarantee initialization of occupancy and root. It also
%                initializes the tree_count using a static counter.
***************************************************************************/

{

        static long counter;
        tree_count = ++counter;

        if (debug) {
		cerr << TREE << tree_count << ALLOCATE;
	}
}

template <class Whatever>
Tree<Whatever> :: ~Tree (void)
/***************************************************************************
% Routine Name : Tree<Whatever> :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/
{
	// Delete all TNode's in the tree as long as it isn't empty
	if (root != NULL) {
        	root->delete_AllTNodes();
	}

	 if (debug) {
		cerr << TREE << tree_count << DEALLOCATE;
	}
}

template <class Whatever>
ostream & Tree<Whatever> :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : Tree<Whatever> :: Write (public)
% File :         Tree.c
% 
% Description : This function will output the contents of the Tree table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/
{
        stream << "Tree " << tree_count << ":\n"
                << "occupancy is " << occupancy << " elements.\n";

        return (root) ? root->Write_AllTNodes (stream) : stream;
}


