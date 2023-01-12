#include "BinarySearchTree.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

typedef BinarySearchTree::DataType DataType;

BinarySearchTree::Node::Node(DataType val0){
	val = val0;  // value of the node
    left = NULL;    // left child
    right = NULL;  
}

// Implement the functions here.
BinarySearchTree::BinarySearchTree(){
	root_ = NULL;
	size_= 0;
}

void deleting(BinarySearchTree::Node* node)
{
    if (node != NULL)
    {
        deleting(node->left);
        deleting(node->right);
        delete node;
    }
}

// Destructor.
BinarySearchTree::~BinarySearchTree(){
	deleting(root_);
}

// Inserts value "val" into the tree. Returns false if failed (i.e., "val"
// already exists in the tree), and true otherwise.
bool BinarySearchTree::insert(DataType val){
	Node* current = root_;
	Node* resultant = new Node(val);
	// if the tree is empty
	if(root_ == NULL){
		root_ = resultant;
		size_++;
		return 1;
	}
	if (exists(val))
		return 0;
	while(1){
		if (val < current->val){
			if(current->left == NULL){
				current->left = resultant;
				break;
			}
			else
				current = current->left;
		}
		else{
			if(current->right == NULL){
				current->right = resultant;
				break;
			}
			else
				current = current->right;
		}
	}
	size_++;
	return 1;
}
// Removes the node with value "val" from the tree. Returns true if successful,
// false otherwise.
bool BinarySearchTree::remove(DataType val){
	int temp=0;
	if(root_ == NULL || !exists(val)) return 0;

	Node* current = root_;
	Node* previous = root_;
	char Last = ' ';
	while(val != current -> val){

		if(Last == 'L') 
			previous = previous->left;
		else if(Last == 'R')
			previous = previous->right;

		if(val < current->val){
			// it's somewhere on the left
			current = current->left;
			Last = 'L';
		}
		else{
			// it's somewhere on the right
			current = current->right;
			Last = 'R';
		}
	}
	if(current->right == NULL && current->left == NULL){
		if(Last == 'L')
			previous->left = NULL;
		else if(Last == 'R')
			previous->right = NULL;
		// delete current;
		else
			root_ = NULL;
	}

	else if(current->right == NULL && current->left != NULL){
		if(Last == 'L')
			previous->left = current->left;
		else if(Last == 'R')
			previous->right = current->left;
		else{
			root_ = current->left;
		}
	}
	else if(current->left == NULL && current->right != NULL){
		if(Last == 'L'){
			previous->left = current->right;
		}
		else if(Last == 'R')
			previous->right = current->right;
		else{
			root_ = current->right;
		}
	}
	else{
		Node* successor = current->right;
		Node* succPrev = current;
		int g=0;
		while(successor->left != NULL){
			successor = successor->left;
			if(g!=0)
				succPrev = succPrev->left;
			else
				succPrev = succPrev->right;
			g++;
		}
		swap(successor->val, current->val);
		if(g==0){
			if(successor->right != NULL){
				succPrev->right = successor->right;
				successor = NULL;
			}
			else{
				succPrev->right = NULL;
			}
		}
		else
			succPrev->left = NULL;
		// delete successor;
		// successor = NULL;
	}
	size_--;
	return 1;
}

// Returns true if a node with value "val" exists in the tree; false otherwise.
bool BinarySearchTree::exists(DataType val) const {
	Node* current = root_;
	while(current != NULL){
		if(val < current->val)
			current = current->left;
		else if(val > current->val)
			current = current->right;
		else if(val == current->val)
			return 1;
	}
	return 0;
}
// Returns the minimum value of the tree. You can assume that this function
// will never be called on an empty tree.
DataType BinarySearchTree::min() const {
	Node* current = root_;
	while(current->left != NULL){
		current = current->left;
	}
	return current->val;
}
// Returns the maximum value of the tree. You can assume that this function
// will never be called on an empty tree.
DataType BinarySearchTree::max() const {
	Node* current = root_;
	while(current->right != NULL){
		current = current->right;
	}
	return current->val;
}
// Returns the number of nodes in the tree.
unsigned int BinarySearchTree::size() const {
	return size_;
}

int BinarySearchTree::getNodeDepth(Node* n) const{
	if (n == NULL)  
        return 0;  
    else
    {  
        /* compute the depth of each subtree */
        int leftD = getNodeDepth(n->left);  
        int rightD = getNodeDepth(n->right);  
      
        /* use the larger one */
        if (leftD > rightD)  
            return(leftD + 1);  
        else return(rightD + 1);  
    }  
}

// Returns the maximum depth of the tree. A tree with only the root node has a
// depth of 0. You can assume that this function will never be called on an 
// empty tree.
unsigned int BinarySearchTree::depth() const{
	if(root_->left == NULL && root_->right == NULL)
		return 0;
	return getNodeDepth(root_)-1;
}

void printInorder(BinarySearchTree::Node* node) 
{ 
    if (node == NULL) 
        return; 
  
    /* first recur on left child */
    printInorder(node->left); 
  
    /* then print the data of node */
    cout << node->val << " "; 
  
    /* now recur on right child */
    printInorder(node->right); 
} 

// You can print the tree in which ever manner you like, however methods such
// as in-order, level-order, etc. might be the most useful for debugging
// purposes.
void BinarySearchTree::print() const{
	printInorder(root_);
}


