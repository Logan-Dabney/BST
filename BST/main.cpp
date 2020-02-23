// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "BST.h"

using namespace std;

int main()
{
	BST* Tree = new BST();
	string command, key;

	while (command != "quit")	// while command isn't quit, run the program
	{
		getline(cin, command);	// get the line entered by the user 

		if (command != "") 
		{
			int i;
			for (i = 0; i < command.length(); i++)		// iterate through command entered
			{
				command.at(i) = tolower(command.at(i));	//set command to lower case

				if (command.at(i) == ' ') {				// if there is a space in command entered
					key = command.substr(i + 1, ((int)command.length() - 1) - i);	// obtains key from command that is after the space
					command = command.substr(0, i);									// makes command to everything before the space. Ultimately changing
				}																	// command.length() and forcing for loop to stop
			}

			if (key != "") // if key has a value test the following command options
			{
				if (command == "insert") cout << Tree->insert(key);
				else if (command == "search") cout << Tree->search(key);
				else if (command == "delete") Tree->remove(key);
				else if (command == "prev") cout << Tree->prev(key);
				else if (command == "next") cout << Tree->next(key);
				else if (command == "parent") cout << Tree->parent(key);
				else if (command == "child") cout << Tree->child(key);
			}
			else // if is doesn't test these command options
			{
				if (command == "min") cout << Tree->min();
				else if (command == "max") cout << Tree->max();
				else if (command == "list") Tree->list();
				else if (command == "help") cout << Tree->help();
			}
		}

		key = ""; // set key equal to nothing 
	}

	Tree->~BST(); // once command equals quit the loop is exited and the tree destructor is executed 
	return 0;
}