#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "String.h"
#include <assert.h>

struct BST {
private:
	struct Node {
		String var_name;
		int value;
		Node* left;
		Node* right;
		Node* parent;

		// value constructor
		Node(String name, int x) {
			var_name = name;
			value = x;
			left = right = parent = nullptr;
		}

		// copy constructor
		Node(const Node& rhs) {
			value = rhs.value;
			if (rhs.right) { 
				right = new Node{ *rhs.right }; // list initialization.  Recursive call to Node(const Node& rhs)
				right->parent = this;
			} else {
				right = nullptr;
			}
			if (rhs.left) {
				left = new Node{*rhs.left};
				left->parent = this;
			} else {
				left = nullptr;
			}
		}

		// destructor
		~Node(void) { 
			delete left;  // calls delete of left, which recursively calls delete on its left and right
			delete right;
		}
	}; // end of struct Node

private:
	void printRecursive(Node* my_root) {
		if (my_root == nullptr) { return ; } // base case
		printRecursive(my_root->left);       // first do the left branch
		printf("%s ", my_root->var_name.c_str());  // then print the root's value
		printRecursive(my_root->right);       // then do the right branch
	}

	static void recursiveDelete(Node* root) {
		if (root == nullptr) { return;  }
		recursiveDelete(root->left);
		recursiveDelete(root->right);
		delete root; // calls Node's destructor
	}

	static Node* recursiveCopy(Node* root) {
		if (root == nullptr) { return 0; }

		Node* result = new Node(root->var_name, root->value);
		result->var_name = root->var_name;
		result->value = root->value;
		result->parent = nullptr;

		Node* left = recursiveCopy(root->left);
		Node* right = recursiveCopy(root->right);

		result->left = left;
		result->right = right;
		if (left != nullptr) { left->parent = result; }
		if (right != nullptr) { right->parent = result; }

		return result;
	}

	static Node* successor(Node* p) {
		if (p->right != 0) { // p has a right subtree
							 /* successor to p will be smallest node in right subtree */
			Node* next = p->right;
			while (next->left != 0) {
				next = next->left;
			}
			return next;
		}
		else { // p does not have a right subtree
			   /* successor to p will be closest ancestor where we go up a left branch */
			Node* parent = p->parent;
			while (parent != 0 && parent->right == p) {
				p = parent;
				parent = p->parent;
			}
			return parent;
		}
	}

	void remove(Node* p) {
		if (p == 0) { 
			return;
		}

		if (p->right == nullptr) { // easy case!, victim p has only a left child
			Node* child = p->left;  
			Node* parent = p->parent;
			if (parent == nullptr) { // victim is child of root
				if (child != nullptr) {  // victim has child
					child->parent = nullptr; // since parent is nullptr
				}
				root = child; // child is root, since no parent
				p->left = p->right = nullptr; // isolate victim, then delete victim
				delete p;
				return;
			}
			if (p == parent->left) { // if victim's parent is not nullptr
				parent->left = child; // if victim is parent's left child, bypass victim and connect parent to child
			}
			else { // if victim is parent's right child, do the same
				parent->right = child;
			}
			if (child != nullptr) { // if child is not nullptr, connect victim's child to victim's parent
				child->parent = parent;
			}
			delete p; // delete victim
		}
		else { // nasty case! 
			Node* victim = successor(p); // node to be actually deleted is victim's successor
			p->value = victim->value; // replace p's value by victim's
			Node* parent = victim->parent;
			Node* child = victim->right;
			if (parent->left == victim) { // if victim is parent's left child
				parent->left = child; // bypass victim and point parent to victim's child
			}
			else {
				parent->right = child; // do the same as above
			}
			if (child != nullptr) { // connect victim's child to victim's parent 
				child->parent = parent;
			}
			victim->right = victim->left = nullptr; // isolate victim before deleting it
			delete victim;
		}
	}

	/* recursive version of find */
	static Node* find(Node* root, String name) {
		if (root == nullptr){return root;}
		if (root->var_name == name){return root;}
		if (name < root->var_name) {
			return find(root->left, name);
		}
		return find(root->right, name);
	}
	Node* root;

public:
	BST(void) { root = nullptr; }

	~BST(void) {
		delete root;
	}

	/* copy constructor */
	BST(const BST& that) {
		root = recursiveCopy(that.root);
		//if (that.root) {
		//	root = new Node{ *that.root };
		//} else {
		//	root = nullptr;
		//}
	}

	/* assignment operator */
	BST& operator=(const BST& that) {
		if (this != &that) {
			delete root;
			root = recursiveCopy(that.root);
			//if (that.root) {
			//	root = new Node{ *that.root };
			//} else {
			//	root = nullptr;
			//}
		}
		return *this;
	}

	void insert(String name, int x) {
		Node* child = new Node(name, x); // create new Node which will be inserted

		if (root == nullptr) {
			root = child; // new child becomes root
			return;
		}

		Node* parent = nullptr;
		Node* p = root;			// start from p = root
		while (p != nullptr) {	// keep searching for empty spot to insert our new Node
			parent = p;
			if(name == p->var_name){
				break;
			}else if (name < p->var_name) {
				p = p->left;
			}
			else {
				p = p->right;
			}
		}	// while loop exits when p->left or p->right = null ptr
		if(name == parent->var_name){
			assert(parent->left != nullptr);
			parent->value = x;
			delete child;
		}else if (name < parent->var_name) {
			assert(parent->left == nullptr);	// double-check to see if while loop worked correctly
			parent->left = child;	// insert our new node
		}
		else { // same as above
			assert(parent->right == nullptr); 
			parent->right = child;
		}
		child->parent = parent;
	}

	/* remove with value as parameter, not Node* */
	void remove(String name) {
		Node* p = find(root, name);
		remove(p);
	}

	bool is_present(String name){
		if(find(root, name)){
			return true;
		}
		return false;
	}

	void change_value(String name, int y){
		Node *p = find(root, name);
		p->value = y;
	}

	int get_value(String name){
		Node* p = find(root, name);
		return p->value;
	}

	/* print the tree in sorted order (in-order); left, root, right 
	 * spec is the format String to be used for values.
	 * In our case, spec is always %s, since our BST only holds Strings
	 */
	void print() {
		if (root == nullptr) { return; } // special case for empty tree
		Node* p;

		/* set p to smallest */
		p = root;
		while (p->left != nullptr) {
			p = p->left;
		}

		const char* prefix = "";
		while (p != nullptr) {
			printf("%s", prefix);
			printf("%s(%d)", p->var_name.c_str(), p->value);
			prefix = ", ";
			p = successor(p);
		}
		printf("\n");
	}

    /* print the tree using in-order traversal -- left branch, root, right branch
     * Try printing in reverse order, and try other kinds of traversal, such as pre-order
     * The spec String is %p, %s, etc. depending on what kind the
     * The printRecursive method without a parameter is called from main.
     * The printRecursive method with a Node parameter is called from within the first one.
     * Remember that root is a private variable, and hence main
     * cannot call printRecursive(Node* my_root). So printRecursvie(Node* my_root) is also
     * made private in BST.
     */
	// public method
	void printRecursive() {
		printRecursive(root);
	}
};