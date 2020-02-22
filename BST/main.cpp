// BST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BST.h"

using namespace std;

int main()
{
	BST* Tree = new BST();

	cout << Tree->insert("E");
	cout << Tree->insert("B");
	cout << Tree->insert("C");
	cout << Tree->insert("D");
	cout << Tree->insert("F");
	cout << Tree->insert("A");
	cout << Tree->insert("A");
	cout << Tree->insert("Z");
	cout << Tree->insert("J");
	cout << Tree->insert("I");
	cout << Tree->insert("H");
	cout << Tree->insert("G");

	cout << Tree->search("A");
	cout << Tree->search("F");
	cout << Tree->search("D");
	cout << Tree->search("R");
	Tree->list();
	cout << Tree->parent("F");
	cout << Tree->parent("E");
	cout << Tree->child("F");
	cout << Tree->child("C");
	cout << Tree->child("B");
	cout << Tree->child("h");
	cout << Tree->parent("h");
	cout << Tree->next("F");
	cout << Tree->next("d");
	cout << Tree->next("Z");
	cout << Tree->prev("E");
	cout << Tree->prev("A");
	cout << Tree->prev("G");


	cout << Tree->min();
	cout << Tree->max();
	Tree->list();

	cout << Tree->search("A");
	Tree->remove("E");
	Tree->remove("d");
	Tree->remove("D");
	Tree->remove("Z");
	Tree->remove("F");
	Tree->remove("B");
	Tree->remove("a");
	Tree->~BST();
}
