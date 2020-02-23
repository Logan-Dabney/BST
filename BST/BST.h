// Author:    Dabney Logan, University of Toledo
// Date:      Feb 17, 2018

#pragma once
#include <string>
using namespace std;

class BST
{
public:
	BST();								// constructs a binary search tree
	~BST();								// destroys tree
	string insert(const string key);	// adds a new node to tree
	void remove(const string key);		// removes a node from tree
	string search(const string key);	// searches for node on tree
	string min();						// finds the minimum node
	string max();						// finds the maximum node
	string next(const string key);		// finds the next node after entered key
	string prev(const string key);		// finds the previous node to entered key
	void list();						// lists all nodes in tree in order
	string parent(const string key);	// returns parent of key entered
	string child(const string key);		// returns children of key entered
	string help();						// list commands 

private:
	struct node 
	{
		string key;
		int count = 1;
		node* parentNode = nullptr;
		node* leftNode = nullptr;
		node* rightNode = nullptr;
	};
	node* root = nullptr;

	int listCount = 1;

	void inOrderTraversal(node* p);		// traverses through node and deals with each node in order
	node* postTraversal(node* p);		// traverses through node and deals with everything in order besides root being dealt with last
	node* branchMin(node* p);			// returns a the smallest node in a branch on the tree
	node* branchMax(node* p);			// returns the largest node in a branch on the tree
	node* findNode(const string key);	// finds node on tree
};

