// Author:    Dabney Logan, University of Toledo
// Date:      Feb 17, 2018

#pragma once
#include <string>
using namespace std;

class BST
{
public:
	BST();
	~BST();
	string insert(const string key);
	void remove(const string key);
	string search(const string key);
	string min();
	string max();
	string next(const string key);
	string prev(const string key);
	void list();
	string parent(const string key);
	string child(const string key);
	string help();

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

	void inOrderTraversal(node* p);
	node* postTraversal(node* p);
	node* branchMin(node* p);
	node* branchMax(node* p);
	node* findNode(const string key);
};

