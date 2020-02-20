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
	//cout << Tree->search("A");
	//cout << Tree->search("F");
	//cout << Tree->search("D");
	//cout << Tree->search("R");
	//cout << Tree->remove("A");
	//Tree->list();
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



	//cout << Tree->min();
	//cout << Tree->max();
	//Tree->list();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
