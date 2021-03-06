/* 
==========================================================================================================
	This code implements a binary search tree that contains nodes. Each node has a key, leftnode, 
	rightnode, parentnode and count. The nodes allow for forward and backwards stepping. The key allows
	a node to be identified and the count keeps track of the amount of times a node has been entered 
	onto the tree. All this allows various fuhnctions to be enacted on a binary search tree. They are 
	detailed below

	Author:    Dabney Logan, University of Toledo
	Date:      Feb 17, 2018 
===========================================================================================================
*/

#include "BST.h"
#include <iostream>

//Intializes an object for the BST Class
BST::BST()
{
	root = nullptr; //Sets the root to the tree to null when intialized
}

// calls a the post traversal function to delete the tree
BST::~BST()
{
	delete postTraversal(root);
}


// This function inserts nodes on a Binary search tree. It runs through
// all the possiblities: no root, left branch of parent node, right branch of parent node
string BST::insert(const string key)
{
	node* p = root;
	node* lag = nullptr;

	// If the pointer is not null, it checks to see if the pointers key is equal to the entered key
	// if it is increment the count that node and return the name and count. If it is not it will
	// check to see if the pointer is greater than the key. If so, it sets p equal to the left node otherwise
	// it sets p to the rightnode. This continues untill p is a nullptr and the lag pointer will contain p's 
	// prevous reference.
	while (p != nullptr)
	{
		if (p->key == key)
		{
			return p->key + " " + to_string(++p->count) + "\n";
		}

		lag = p;
		p = (p->key > key) ? p->leftNode : p->rightNode;

	}

	// Creates a newNode with entered key
	node* newNode = new node();
	newNode->key = key;

	if (lag == nullptr)		// if the lag point is equal to null that means the
	{						// root started of null so set the root as the new node.
		root = newNode;
		return root->key + " " + to_string(root->count) + "\n";
	}
	else if (newNode->key > lag->key)		// if the newNode's key is larger than the lag's key set 
	{										// lag's rightNode to newNode and set newNode's parentNode to lag
		lag->rightNode = newNode;
		newNode->parentNode = lag;
		return newNode->key + " " + to_string(newNode->count) + "\n";
	}
	else							// the only remaining option is if newNode's key is smaller than the
	{								// lag's key. Set lag's leftNode to newNode and newNode's parentNode to lag
		lag->leftNode = newNode;
		newNode->parentNode = lag;
		return newNode->key + " " + to_string(newNode->count) + "\n";
	}
}


// Based on the key entered by the user it searches the tree and outputs the node's key and count 
// that matches the key entered. If none match output a blank line.
string BST::search(const string key)
{
	node* p = findNode(key);

	if (p == nullptr) return "\n";							// if p comes back null return a blank line
	else return p->key + " " + to_string(p->count) + "\n";	// prints key and count of node found

}


// Goes down the left most brach from root to find the smallest value in tree
string BST::min()
{
	node* p = root;
	node* lag = nullptr;	// lag point
	while (p != nullptr)	// while pointer is not null continue to set lag to p and p to it's left child. 
	{
		lag = p;
		p = p->leftNode;
	}

	if (lag != nullptr) return lag->key + "\n";		// if lag isn't null then print out lag node's key
	return "\n";									// iff lag is null print out a blank line
}


// Traverses down right most branch from root to find the largest value in tree
string BST::max()
{
	node* p = root;
	node* lag = nullptr;

	while (p != nullptr)		// while the pointer isn't null continue down right branch
	{
		lag = p;
		p = p->rightNode;		// setting point to it's right child
	}

	if (lag != nullptr) return lag->key + "\n";		// if lag isn't null return lag

	return "\n";									// only happens if root is null to begin with
}


// Iterates through the list and prints all node's in order 
void BST::list()
{
	if (root == nullptr) cout << "Set is empty\n";		// if root starts off null returns Set is empty
	else
	{
		cout << "Set contains:";
		inOrderTraversal(root);		// called inOrderTraversal
		cout << "\n";
	}
	listCount = 1;					// resets count to 1
}


// Based on key entered by user this function will return the next key in the tree. 
// Also takes into acount for possible cases that would cause errors: if pointer starts off null,
// if it is tree max, if it's right node isnt null and if it's right node is null
string BST::next(const string key)
{
	node* p = findNode(key);
	if (p == nullptr) return "\n";					// if the node is not found retrun blank line

	if (branchMax(root)->key == key) return "\n";	// if the key is the max branch there is not next print blank line

	if (p->rightNode != nullptr) return branchMin(p->rightNode)->key + "\n";	// if pointers right node isn't null return it's branch's min 

	while (p == p->parentNode->rightNode) {						// iterate backwards through tree aslong as pointer is equal to it's parent's right child
		p = p->parentNode;
		if (p->parentNode == nullptr) return p->key + "\n";		//if it reaches the root print it 
	}
	return p->parentNode->key + "\n";							// other wise it was parent's left child so print out the parent
}


// Based on a key entered by user this function will return the previous key in the tree. 
// Also takes into acount for possible cases that would cause errors: if pointer starts off null,
// if it is tree min, if it's left node isn't null and if the left node is null
string BST::prev(const string key)
{

	node* p = findNode(key);

	if (p == nullptr) return "\n";		// if the node doesn't exist output blank line

	if (branchMin(root)->key == key) return "\n";	// if key is the smallest element there is no previous outout blank line

	if (p->key == key && p->leftNode != nullptr) return branchMax(p->leftNode)->key + "\n"; // if the pointers key is equal to key and it's leftnode
																							// is not null find the left node's max
	while (p == p->parentNode->leftNode) {						// iterate back up the tree as long as pointer is equal to it's parent's left child
		p = p->parentNode;
		if (p->parentNode == nullptr) return p->key + "\n";		// if it reaches the root print the key;
	}
	return p->parentNode->key + "\n";							//pointer ended up being it's parent's right child so print out parent
}


// Finds node containing the key and returns the key of the that node.
// If the node is the root or is not in the list it returns a blank line 
string BST::parent(const string key)
{
	if (root->key == key) return "\n";	// if the root is the key return blank line

	node* p = findNode(key);

	if (p == nullptr) return "\n";		// if p falls off tree, key does not exist and return a blank 

	return p->parentNode->key + "\n";	// if p is found return parent node
}


// returns the children of a node that contains the key entered by the user.
// If no node is found, then it returns a blank line.
string BST::child(const string key)
{
	node* p = findNode(key);

	if (p == nullptr) return "\n";														// no node was found return blank line
	else if (p->leftNode == nullptr && p->rightNode == nullptr) return "NULL, NULL\n";	// both children are null
	else if (p->leftNode == nullptr) return "NULL, " + p->rightNode->key + "\n";		// left child is null
	else if (p->rightNode == nullptr) return p->leftNode->key + ", NULL\n";				// right child is null
	else return p->leftNode->key + ", " + p->rightNode->key + "\n";						// both children have a key
}


// Find's node in the tree and then removes. There are a variety of cases that it deals with:
// node not in tree, node with higher than one, root, node with no children, node with one child (both sides),
// node with 2 children
void BST::remove(const string key)
{
	node* p = findNode(key);

	if (p == nullptr) cout << key + " -1\n";										// if node is not found return key -1
	else if (p->count > 1) cout << p->key + " " + to_string(--p->count) + "\n";		// if the node found has more than 1 in count decrement count and return key with new count
	else if (p->leftNode == nullptr && p->rightNode == nullptr)						// node has no children
	{
		cout << p->key + " 0\n";

		if (p == root) root = nullptr;												// if point equals root set it to null because still need the root
		else
		{
			if (p->parentNode->leftNode == p) p->parentNode->leftNode = nullptr;	// if the node is the left child of parent node set equal to null
			else p->parentNode->rightNode = nullptr;								// if the node is the right child of parent node set equal to null

			delete p;
		}
	}
	else if (p->leftNode != nullptr && p->rightNode != nullptr) // has both children
	{
		if (p->rightNode->leftNode == nullptr)	// if the successor is the right child of the node (has no left children)
		{
			if (p == root)
			{
				cout << root->key + " 0\n";

				root->rightNode->leftNode = root->leftNode;
				root = root->rightNode;
				root->leftNode->parentNode = root;
				root->parentNode = nullptr;
			}
			else if (p == p->parentNode->rightNode)			// if the pointer is the right child of it's parent 
			{
				p->parentNode->rightNode = p->rightNode;	// set pointer's parent node right child to pointers right node
				p->rightNode->parentNode = p->parentNode;	// set pointer's right node parent to pointer's parentnode
				p->rightNode->leftNode = p->leftNode;		// set pointer's right node left child to p's left child
				p->leftNode->parentNode = p->rightNode;		// set pointers left childs parent to p's right child

				cout << p->key + " 0\n";
				delete p;
			}
			else											// if the pointer is the left child of it's parent
			{
				p->parentNode->leftNode = p->rightNode;		// set pointer's  parent node left child to pointers right node
				p->rightNode->parentNode = p->parentNode;	// set pointer's right node parent to pointer's parent
				p->rightNode->leftNode = p->leftNode;		// set pointer's right node left child to p's left child
				p->leftNode->parentNode = p->rightNode;		// set pointers left childs parent to p's right child

				cout << p->key + " 0\n";
				delete p;
			}
		}
		else // if the successor is in the pointer's right child's left branch
		{
			cout << p->key + " 0\n";

			node* pSuccessor = branchMin(p->rightNode); // finds pointers successor 
			p->key = pSuccessor->key;
			p->count = pSuccessor->count;

			if (pSuccessor->rightNode != nullptr) // if the successors right node isn't null
			{
				pSuccessor->parentNode->leftNode = pSuccessor->rightNode;	// set the successors parent node left child to successors right node
				pSuccessor->rightNode->parentNode = pSuccessor->parentNode; // set the successors right node parent to successors parent node 
				delete pSuccessor;
			}
			else // if the successors right node is null
			{
				pSuccessor->parentNode->leftNode = nullptr;
				delete pSuccessor;
			}
		}
	}
	else if (p->leftNode != nullptr || p->rightNode != nullptr) // if there is only one child
	{
		node* childNode = (p->leftNode == nullptr) ? p->rightNode : p->leftNode; // finds which child it is and sets it to a child node to be used later

		if (p == root) // if it's the root print that it is being delete then set root to the child and it's parent to nullpter
		{
			cout << root->key + " 0\n";

			root = childNode;
			root->parentNode = nullptr;
		}
		else if (p->parentNode->leftNode == p)			// if the pointer node is the left child of it's parent
		{
			p->parentNode->leftNode = childNode;		// set the parent's left node to the pointer's child
			childNode->parentNode = p->parentNode;		// set the pointers child's parent node to the pointer's parent

			cout << p->key + " 0\n";
			delete p;
		}
		else											// if the node is the right child of it's parent
		{
			p->parentNode->rightNode = childNode;	// set the parent's right node to the pointer's child
			childNode->parentNode = p->parentNode;	// set the pointer's child parent node to the pointer's parent

			cout << p->key + " 0\n";
			delete p;
		}
	}
}


// returns functions the user can do on tree
string BST::help()
{
	return "Commands that can be computed on a BST:\ninsert \"key\"\ndelete \"key\"\nsearch \"key\"\n"
		"next \"key\"\nprev \"key\"\nparent \"key\"\nchild \"key\"\nlist\nmin\nmax\nquit\n";
}


// traverses through a tree, finds the node that matches the key entered and returns the node. If no node
// return nullptr
BST::node* BST::findNode(const string key)
{
	node* p = root;
	if (p != nullptr)							// if root starts off null retur null pointer
	{
		while (p->key != key)					//iterates through tree to find node once found exit loop
		{
			p = (p->key > key) ? p->leftNode : p->rightNode;

			if (p == nullptr) return nullptr;	// if node is not found return null
		}
		return p;
	}
	return nullptr;
}

// similar to exposed min function but returns a node instead
BST::node* BST::branchMin(node* p)
{
	node* lag = nullptr;
	while (p != nullptr)
	{
		lag = p;
		p = p->leftNode;
	}

	if (lag != nullptr) return lag;

	return nullptr;
}

// similar to exposed max function but returns node instead of a key
BST::node* BST::branchMax(node* p)
{
	node* lag = nullptr;

	while (p != nullptr)
	{
		lag = p;
		p = p->rightNode;
	}

	if (lag != nullptr) return lag;

	return nullptr;
}

// makes one pass through the loop but specifically made for list function
// if the list count is greater than one it will add commmas before node is printed
void BST::inOrderTraversal(node* p)
{
	if (p->leftNode != nullptr) inOrderTraversal(p->leftNode);
	if (listCount > 1) cout << ",";
	cout << " (" + to_string(listCount++) + ") " + p->key + " " + to_string(p->count);
	if (p->rightNode != nullptr) inOrderTraversal(p->rightNode);
}

// makes one pass through the list returning all nodes in order but passes the root last
BST::node* BST::postTraversal(node* p)
{
	if (p != nullptr)
	{
		if (p->leftNode != nullptr) postTraversal(p->leftNode);
		if (p->rightNode != nullptr) postTraversal(p->rightNode);
		return p;
	}

	return root = new node();
}


// prev attempt
	//node* parent = p;
	//while (parent != nullptr && p == parent->leftNode) {
	//	p = parent;
	//	parent = parent->parentNode;
	//}

	//return parent->key + " " + to_string(parent->count) + "\n";


// min going to be left most value
//		while x.left not Null
//		x = x.left as far as possible
//		return x


// max going to be the right mose value
//		while x.right not Null
//		x = x.right
//		return x

// Predecessor
// symmetric to the successor 
// flip left and right
// do not depend on key values jsut structure of the tree



//Successors
// no successor of the maximum value
// if node x has a right child, then x's successor is the left most descendat of the this right child 
// if node x doesn't have a right child, then x's successor is x's most recent (lowest)
// ancestor  whose left child is also an acestor of x
// (if you go back up a left link, or hit the root, youve found the successor)
// if x.right != null then return x
// else 
// y = x.parent
// while y != null and x==y.right
//		x= y
//		y = y.parent
//	return y

//Insert
// if already in tree before making new node increment count and return
// z= new node;
// z.key = v;
// z.left = null;
// z.right = null;
// x= T.root
// y = null
// while x != null
//	y = x
//	if z.key < x.key
//		x = x.left
//	else x = x.right
// z.p = y
// if y== null
//	t.Root = z
// else if z.key < y.key
//		y.left = z
// else y.right = z

//delete
// cases
// decriment count
// if only one 
//		z is a leaf, just make the parent point that points at z null
//		z has only one child just cut out z and reatach
//		z has 2 children


// Insert Attempts
	/*if (p == nullptr)
	{
		p->key = key;
		p->count = 1;
		return p->key + " " + to_string(p->count);

	} else
	{
		while (p != nullptr)
	{
			//Check the nodes key if the key to be entered is smaller than the key go to left child
			//if it is bigger go to right node until can't go father then enter the node. If there are no
			//nodes add the node
			//
			if (stoi(p->key) == stoi(key))
			{
				p->count += 1;
				return p->key + " " + to_string(p->count);
			} else
			{
			p = (stoi(p->key) > stoi(p->leftNode->key)) ? p->rightNode : p->leftNode;
			}

			/*if (stoi(p->key) > stoi(p->leftNode->key)) // if root key is greater that leftnode's key go to rightnode
			{

			}
			else if (stoi(p->key) < stoi(p->rightNode->key)) // if root key is less than rightnode's key go left node
			{

			}
			else // key's match increment count
			{

			}
		}
		p->key = key;
		p->count = 1;
		return p->key + " " + to_string(p->count);
	}*/

	//else if (p == root)
	//{

	// TO-DO Later
	//if (root->leftNode == nullptr && root->rightNode == nullptr)
	//{
	//	cout << root->key + " 0\n";
	//	root == nullptr;
	//}
	//else if (root->rightNode != nullptr)
	//{
	//	if (root->rightNode.leftNode == nullptr) 
	//	{

	//	}

	//}
	//
	//}

	//else if (p->leftNode != nullptr && p->rightNode == nullptr)		// left node is not null but right is
	//{
	//	if (p == root) 
	//	{
	//		cout << root->key + " 0\n";

	//		root = root->leftNode;
	//		root->parentNode = nullptr;
	//	}
	//	else if (p->parentNode->leftNode == p)			// if the pointer node is the left child of it's parent
	//	{
	//		p->parentNode->leftNode = p->leftNode;		// set the parent's left node to the pointer's left node
	//		p->leftNode->parentNode = p->parentNode;	// set the pointer's left node parent to the pointer's parent

	//		cout << p->key + " 0\n";
	//		delete p;
	//	}
	//	else											// if the node is the right child of it's parent
	//	{
	//		p->parentNode->rightNode = p->leftNode;		// set the parent's right node to the pointers left node
	//		p->leftNode->parentNode = p->parentNode;	// set the pointer's left node parent to the pointer's parent

	//		cout << p->key + " 0\n";
	//		delete p;
	//	}
	//}
	//else if (p->rightNode != nullptr && p->leftNode == nullptr) // right node is not null but left is
	//{
	//	if (p == root) 
	//	{
	//		cout << root->key + " 0\n";

	//		root = root->rightNode;
	//		root->parentNode = nullptr;
	//	}
	//	else if (p->parentNode->leftNode == p)			// if the pointer node is the left child of it's parent
	//	{
	//		p->parentNode->leftNode = p->rightNode;		// set the parent's left node to the pointer's left node
	//		p->rightNode->parentNode = p->parentNode;	// set the pointer's right node parent node to the pointer's parent

	//		cout << p->key + " 0\n";
	//		delete p;
	//	}
	//	else											// if the node is the right child of it's parent
	//	{
	//		p->parentNode->rightNode = p->rightNode;	// set the parent's right node to the pointer's right node
	//		p->rightNode->parentNode = p->parentNode;	// set the pointer's right node parent node to the pointer's parent

	//		cout << p->key + " 0\n";
	//		delete p;
	//	}
	//}