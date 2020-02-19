/*

*/
#include "BST.h"
#include <iostream>

//Intializes an object for the BST Class
BST::BST()
{
	root = nullptr; //Sets the root to the tree to null when intialized
}

BST::~BST()
{

}

// This function inserts nodes on a Binary search tree. It runs through
// all the possiblities (no root, left branch of parent node, right branch of parent node)
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
			p->count += 1;
			return p->key + " " + to_string(p->count) + "\n";
		}

		lag = p;
		p = (p->key > key) ? p->leftNode : p->rightNode;

	}
	
	// Creates a newNode with entered key
	node* newNode = new node();
	newNode->key = key;

	// if the lag point is equal to null that means the root started of null so set the root as the new node.
	if (lag == nullptr)
	{
		root = newNode;
		return root->key + " " + to_string(root->count) + "\n";
	}
	else if (newNode->key > lag->key)
	{
		// if the newNode's key is larger than the lag's key set lag's rightNode to newNode and set 
		// newNode's parentNode to lag
		lag->rightNode = newNode;
		newNode->parentNode = lag;
		return newNode->key + " " + to_string(newNode->count) + "\n";
	}
	else
	{
		// the only remaining option is if newNode's key is smaller than the lag's key. Set lag's leftNode to newNode
		// and newNode's parentNode to lag
		lag->leftNode = newNode;
		newNode->parentNode = lag;
		return newNode->key + " " + to_string(newNode->count) + "\n";
	}
}

string BST::search(const string key)
{
	node* p = root;
	while (p != nullptr)
	{
		if (p->key == key) return p->key + " " + to_string(p->count) + "\n";
		p = (p->key > key) ? p->leftNode : p->rightNode;
	}
	return "Not in the tree. Would you like to add? Type insert " + key + " Then press enter.\n";
}

string BST::min()
{
	node* p = root;
	node* lag = nullptr;

	while (p != nullptr)
	{
		lag = p;
		p = p->leftNode;
	}
	if (lag != nullptr)
	{
		return lag->key + "\n";
	}
	return "\n";
}

string BST::max()
{
	node* p = root;
	node* lag = nullptr;
	while (p != nullptr)
	{
		lag = p;
		p = p->rightNode;
	}
	if (lag != nullptr)
	{
		return lag->key + "\n";
	}
	return "\n";
}

void BST::list()
{
	if (root == nullptr) {
		cout << "There is nothing in the list.\n";
	}
	else {
		traverse(root);
	}
}

void BST::traverse(node* p)
{
	if (p->leftNode != nullptr) traverse(p->leftNode);
	cout << p->key + " " + to_string(p->count) + " ";
	if (p->rightNode != nullptr) traverse(p->rightNode);
}

//string BST::search(const string key)
//{
//	node* p = root;
//	while (p != nullptr)
//	{
//		if (p->key == key) return p->key + " " + to_string(p->count) + "\n";
//		p = (p->key > key) ? p->leftNode : p->rightNode;
//	}
//}

string BST::next(const string key)
{
	node* p = root;

	while (p->key != key) 
	{
		p = (p->key > key) ? p->leftNode : p->rightNode;
		if (p == nullptr) return " ";
	}

	if (p->key == key && p->rightNode != nullptr)
	{
		return branchMin(p->rightNode)->key + "\n";
	}

	node* parent = p;
	while (parent != nullptr && p == parent->rightNode) {
		p = parent;
		parent = parent->parentNode;
	}
	return parent->key + " " + to_string(parent->count) + "\n";
}

BST::node* BST::branchMin(node* p)
{
	node* lag = nullptr;
	while (p != nullptr)
	{
		lag = p;
		p = p->leftNode;
	}
	if (lag != nullptr)
	{
		return lag;
	}
	return nullptr;
}

string BST::prev(const string key)
{
	node* p = root;

	while (p->key != key)
	{
		p = (p->key > key) ? p->leftNode : p->rightNode;
		if (p == nullptr) return " ";
	}

	if (p->key == key && p->leftNode != nullptr)
	{
		return branchMax(p->leftNode)->key + "\n";
	}

	node* parent = p;
	while (parent != nullptr && p == parent->leftNode) {
		p = parent;
		parent = parent->parentNode;
	}
	return parent->key + " " + to_string(parent->count) + "\n";
}

BST::node* BST::branchMax(node* p)
{
	node* lag = nullptr;
	while (p != nullptr)
	{
		lag = p;
		p = p->rightNode;
	}
	if (lag != nullptr)
	{
		return lag;
	}
	return nullptr;
}

string BST::parent(const string key) 
{
	node* p = root;
	while (p->key != key)
	{
		if (p == nullptr)
		{
			return "\n";
		}
		p = (p->key > key) ? p->leftNode : p->rightNode;
	}
	return p->parentNode->key;
}

string BST::child(const string key)
{
	node* p = root;
	while (p->key != key)
	{
		if (p == nullptr)
		{
			return "\n";
		}
		p = (p->key > key) ? p->leftNode : p->rightNode;
	}
	return p->leftNode->key + ", " + p->rightNode->key;
}

string BST::remove(const string key)
{
	node* p = root;
	while (p->key != key)
	{
		if (p == nullptr)
		{
			return key + "-1";
		}
		p = (p->key > key) ? p->leftNode : p->rightNode;
	}
	if (p->count > 1)
	{
		p->count--;
		return p->key + to_string(p->count);
	}
	else if (p->leftNode == nullptr && p->rightNode == nullptr) 
	{
		if (p->parentNode->leftNode->key == p->key) p->parentNode->leftNode = nullptr;
		else p->parentNode->rightNode = nullptr;
	}
}

string BST::help() 
{
	return "The commands that can be computed on a BST is insert, remove, search, min, max, next, prev, list, parent, child, help and quit";
}

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