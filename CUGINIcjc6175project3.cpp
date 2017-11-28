// CUGINI-cjc6175-project2.cpp : Defines the entry point for the console application.
// 
//
// The purpose of this program is to allow the user to create and manipulate a linked list using the functions
// construct, addElementFront, addElementBack, insertElement, deleteElement, removeFront, removeBack, size, and print.
//
//
// Cole Cugini
//
// The limits of this program are based around only being able to manipulate the linked list based around the predefined functions for this
// assignment. I also restricted the user to entering only positive integers.
//
//
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
int sizeOfLL=0; // the number of valid elements in the array
int param1 = -666; // the first parameter of an entry
int param2 = -666; // the second parameter of an entry (only insert)
bool created = false; //whether or not there is a mainArray

//declares what a dataBlock is
struct dataBlock {
	int value;
	dataBlock *next;
	dataBlock *previous;
};

class linkedList {

public:
	dataBlock *firstBlock;


	//construct takes nothing in or out but creates the main array

	//construct checks if there's a current list already and deconstructs it if there is
	//otherwise it just sets the first block to NULL
	void construct() {
		if (created && sizeOfLL>0 && param1 == -666) {//if there already is a list
			dataBlock *temp;
			temp = firstBlock;
			while (temp->next != NULL) {//delete each node
				temp = temp->next;
				delete temp->previous;
			}
			delete temp;
			created = false;
		}
		if (!created && param1 == -666) {//checks if there is a list or a invalid parameter
			created = true;//sets the bool to true signifying a list has been created
			firstBlock = NULL;
		}
	}


	//getInput fetches the user input, trims the input to be usable and returns the fixed input
	//nothing in and the trimmed input out
	string getInput() {
		string input;
		getline(cin, input);
		input = fixInput(input);
		return input;
	}

	//fixInput takes in an untrimmed string and outputs a trimmed string

	//fixInput takes in the untrimmed user input and trims out spaces, makes everything lowercase and
	//trims spaces and commas around the parameters and stores them into param1 and param2
	string fixInput(string input) {
		string tempParam1;//used to edit the parameters before storing them into the global ones
		string tempParam2;
		int firstNonSpace = input.find_first_not_of(" "); //finds the first non space
		int lastNonSpace = input.find_last_not_of(" \t\f\v\n\r");//finds the last non space
		if (lastNonSpace == -1 || firstNonSpace == -1)//if theres nothing but spaces ask for valid input
			return "Please enter a valid input.";
		else
		{
			input = input.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);//used the substring between the outer spaces effictively getting rid of the leading/trailing spaces
			for (int x = 0; x < input.length(); x++)//makes everything lowercase
				input[x] = tolower(input[x]);
		}
		if (input.find(" ") != -1 && ((input.find_first_of(" ") != input.find_last_of(" ")) || input.find(",") != -1)) {//if there are spaces seperating the parameters from the command
			tempParam1 = input.substr(input.find_first_of(" ") + 1, input.find_last_of(",") - input.find(" ") - 1);//removes unneeded characters from the parameters
			tempParam2 = input.substr(input.find_last_of(",") + 1, input[input.length() - 1]);//same as previous line but is slightly different becuase it's the end of the string
			for (int x = 0; x < tempParam1.length(); x++)//gets rid of spaces
				if (tempParam1[x] == ' ')
					tempParam1.erase(x, 1);
			for (int x = 0; x < tempParam2.length(); x++)//gets rid of spaces
				if (tempParam2[x] == ' ')
					tempParam2.erase(x, 1);
			if ((tempParam1[0] > 47 && tempParam1[0] < 58) && (tempParam2[0] > 47 && tempParam2[0] < 58)) {//makes sure the parameters are integers and converts them from strings to ints
				param1 = stoi(tempParam1);
				param2 = stoi(tempParam2);
			}
			input = input.substr(0, input.find_first_of(" "));//saves the command
		}
		else if (input.find(" ") != -1) {//this does the same as the previous if statement but accounts for one parameter instead of two
			tempParam1 = input.substr(input.find_first_of(" ") + 1, input[input.length() - 1]);
			if ((tempParam1[0] > 47 && tempParam1[0] < 58))
				param1 = stoi(tempParam1);
			input = input.substr(0, input.find_first_of(" "));
		}
		return input;
	}

	//addElementFront takes nothing in or out, just modifies the dataBlock pointers

	//addElementFront adds a value to the front of the list by first checking if there are already elements in the list.
	//If there are no elements, start the list with this entry. Otherwise add a new node and change the previous firstBlock's pointers
	//to point to the new firstBlock and then update firstBlock to the new firstBlock.
	void addElementFront() {
		if (created) {//checks if the create function was used
			if (param1 != -666) {//checks for valid parameters
				int input = param1;
				param1 = -666;
				if (firstBlock == NULL) {//if the list is empty
					firstBlock = new dataBlock;//start the list with this node
					firstBlock->value = input;
					firstBlock->next = NULL;
					firstBlock->previous = NULL;
					return;
				}
				dataBlock *newItem = new dataBlock;//otherwise this is the new node
				newItem->value = input;//store the value
				firstBlock->previous = newItem;//have the previous of the old head of the list point to the newItem
				newItem->next = firstBlock;//the newItem's next points to the old head
				firstBlock = newItem;//now reset the head to the newItem
				newItem->previous = NULL;//and have the newItem's previous be NULL signifying the beginning of the list
				size();
			}
			else
				cout << "Please enter a valid command.\n";
		}
		else
		{
			cout << "Please use the Create function first.\n";
			param1 = param2 = -666;
		}
	}

	//addElementBack takes nothing in or out, just modifies the dataBlock pointers

	//addElementBack adds a value to the end of the list by first checking if there are already elements in the list.
	//If there are no elements, start the list with this entry. Otherwise I use a temp pointer to find the last node in the list,
	//then have the old last item's next point to the newItem.
	void addElementBack() {
		if (created) {//checks if create was used
			if (param1 != -666) {//checks for valid parameter
				int input = param1;//stores param1 then resets it
				param1 = -666;
				if (firstBlock == NULL) {//if the list is empty
					firstBlock = new dataBlock;//initialize this as the first block
					firstBlock->value = input;
					firstBlock->next = NULL;
					firstBlock->previous = NULL;
					return;
				}
				dataBlock *temp;//I use this to find the end
				dataBlock *newItem = new dataBlock;//this is the dataBlock to be added to the list
				newItem->value = input;
				temp = firstBlock;//starts temp at the head

				while (temp->next != NULL) {//finds the end
					temp = temp->next;
				}
				temp->next = newItem;//sets the new end to be the newItem
				newItem->previous = temp;//sets the newItem's previous to be the old end
				newItem->next = NULL;//sets the newItem's next as NULL signifying the end
				size();
			}
			else
				cout << "Please enter a valid command.\n";
		}
		else
		{
			cout << "Please use the Create function first.\n";
			param1 = param2 = -666;
		}
	}


	//insertElement takes nothing in or out, just modifies the dataBlock pointers

	//insertElement inserts a value at a specific location by first checking if there are already elements in the list.
	//If there are no elements, start the list with this entry. First I update the size of the LL if the user wants to insert
	//at the beginning or end I use my other predefined functions. Otherwise I iterate over the LL position amount of times
	//and insert the new node there, changing the surrounding pointers to accommodate.
	void instertElement() {
		if (created) {//checks if create was used
			int pos = param1;
			int input = param2;
			param1 = param2 = -666;//stores the parameters and resets them
			size();//runs the size function to get an accuarate value for sizeOfLL
			if (input != -666 && pos>=0 && pos<=sizeOfLL) {//checks to make sure the parameters are valid
				if (firstBlock == NULL) {//if the list is empty start it
					firstBlock = new dataBlock;//initialize the firstBlock
					firstBlock->value = input;
					firstBlock->next = NULL;
					firstBlock->previous = NULL;
					return;
				}
				if (pos == 0) {//if the user wants to add a value in the first position I use addElementFront
					param1 = input;
					addElementFront();
					return;
				}
				if (pos == sizeOfLL) {//if the user wants to add a value to the last position I use addElementBack
					param1 = input;
					addElementBack();
					return;
				}
				dataBlock *tempNext = firstBlock->next;//otherwise (the list is larger than 2) I set tempNext to the second node
				dataBlock *tempPrev = firstBlock;//and tempPrev to the first so when I iterate over the list they are in the correct spots
				dataBlock *newItem = new dataBlock;//this it the node that will be added to the list
				newItem->value = input;//stores the value the user wanted into the new node

				for (int x = 1; x < pos; x++) {//iterates until the desired position
					tempNext = tempNext->next;
					tempPrev = tempPrev->next;
				}//now tempNext is the node after the insertion and tempPrev is the node before
				tempNext->previous = newItem;//these 4 statements reassign the next and previous pointers to insert a new node in between
				tempPrev->next = newItem;
				newItem->next = tempNext;
				newItem->previous = tempPrev;
				size();
			}
			else
				cout << "Parameter(s) invalid.\n";
		}
		else
		{
			cout << "Please use the Create function first.\n";
			param1 = param2 = -666;
		}
	}

	//deleteElement takes nothing in or out, only modifies the list of dataBlocks

	//deleteElement checks if the list was created, then checks for valid parameters.
	//Then I made 3 temp dataBlock pointers one is the one we're removing, one is previous to the one we're removing and one
	//is next to the one we're removing. I think iterate over the list to find the node that has the value we're looking for.
	//if it gets to the end without finding the value it accounts for that. Otherwise I store the nodes before and after the node
	//that holds the value to skip the node that has the value. Then I delete that node.
	void deleteElement() {
		if (created) {//checks if create was ran
			if (param1 != -666) {//checks parameters
				int input = param1;
				param1 = -666;//resets parameter 1
				if (firstBlock == NULL) {//makes sure the list isn't empty
					cout << "The list is empty.\n";
					return;
				}
				dataBlock *temp;
				dataBlock *tempNext;
				dataBlock *tempPrev;
				temp = firstBlock;//starts at the first node of the list
				while (temp->value != input) {//finds the value
					if (temp->next == NULL) {//if it cycles through all the values and doesn't find the number
						cout << "The value is not in the list.\n";
						return;
					}
					temp = temp->next;//otherwise look for the value
				}
				if (temp->next == NULL) {//if it's the last element
					removeBack();
					return;
				}
				else if (temp->previous == NULL) {//if it's the first element
					removeFront();
					return;
				}
				tempNext = temp->next;//otherwise assign tempNext to the next element
				tempPrev = temp->previous;//tempprev to the previous element
				delete temp;
				tempPrev->next = tempNext;//reassign surrounding pointers
				tempNext->previous = tempPrev;
				size();
			}
			else
				cout << "Please enter a valid command.\n";
		}
		else
		{
			cout << "Please use the Create function first.\n";
			param1 = param2 = -666;
		}
	}

	//removeFront takes nothing in or out, only modifies the list of dataBlocks

	//I first check to make sure the parameters are right and the list was created
	//then I make sure the list isn't empty or that there's more than one item
	//otherwise I just reassign the head of the list, NULL the new head's previous pointer,
	//and delete the old head
	void removeFront() {
		if (created) {//checks if create was ran
			if (param1 == -666) {//checks parameters
				int input = param1;
				param1 = -666;//resets param1
				if (firstBlock == NULL) {//makes sure we have a list to work with
					cout << "The list is empty.\n";
					return;
				}
				else if (firstBlock->next == NULL) {//if there was only one item
					delete firstBlock;
					firstBlock = NULL;
					size();
					return;
				} 
				firstBlock = firstBlock->next;//otherwise assign the firstblock to the second node
				delete firstBlock->previous;
				firstBlock->previous = NULL;//and clear the firstblock's previous pointer
				size();
			}
			else
				cout << "Please enter a valid command.\n";
		}
		else
		{
			cout << "Please use the Create function first.\n";
			param1 = param2 = -666;
		}
	}



	//removeBack takes nothing in or out, only modifies the list of dataBlocks

	//I first check to make sure the parameters are right and the list was created
	//then I make sure the list isn't empty or that there's more than one item.
	//I then cycle through the list using a temp dataBlock until I get to the last item denoted by its next being NULL
	//then I just set the previous dataBlock's next to be NULL which creates a new end to the list and delete the old end.
	void removeBack() {
		if (created) {//checks if the create function was used
			if (param1 == -666) {//checks parameter 1
				int input = param1;
				param1 = -666;//resets param1
				if (firstBlock == NULL) {//makes sure the list isn't empty
					cout << "The list is empty.\n";
					return;
				}
				else if (firstBlock->next == NULL) {//makes sure there's more than one node
					delete firstBlock;
					firstBlock = NULL;
					size();
					return;
				}
				dataBlock *temp;
				temp = firstBlock;//sets the temp to the head of the list

				while (temp->next != NULL)//cycles through until it reaches the end
					temp = temp->next;

				temp->previous->next = NULL;//sets a new end
				delete temp;
				size();
			}
			else
				cout << "Please enter a valid command.\n";
		}
		else
		{
			cout << "Please use the Create function first.\n";
			param1 = param2 = -666;
		}
	}


	//size takes nothing in and out but sets the right size for the global variable sizeOfLL

	//I first check to make sure the parameters are right and the list was created
	//I then assign a temp dataBlock to the head of the list and cycle through all nodes until I get to the end
	//which is denoted by its next being NULL. Every time I go to the next node I add one to the size.
	void size() {
		if (created) {//makes sure the create function was used
			if (firstBlock != NULL) {//checks if the list is empty
				if (param1 == -666 && param2 == -666) {//checks parameters
					int theSize = 1;//starts the size at one because we start at the first block
					dataBlock *temp = firstBlock;//starts at firstblock
					while (temp->next != NULL) {//iterates over list adding one for every node and ending when the next is NULL (the end)
						theSize++;
						temp = temp->next;
					}
					sizeOfLL = theSize;//sets the global var to the correct size
				}
				else {
					cout << "Please enter a valid command.\n";
					param1 = param2 = -666;
				}

			}
			else
				sizeOfLL = 0;
		}
		else
			cout << "Please use the Create function first.\n";
	}

	

	//print just prints the linked list
	//print takes nothing in or out, only prints

	//first I check to make sure the list was created and is populated
	//I iterate over the list starting from the head (firstBlock) and going until the next pointer is NULL
	//each time I print the value stored there and reassign the temp to the next node
	void print() {
		if (created) {//checks if create function was used
			if (firstBlock == NULL) {//checks if the list is empty
				cout << "The list is empty.\n";
				return;
			}
			dataBlock *temp = firstBlock;//starts at the head of the list
			cout << "[";
			while (temp->next != NULL) {//iterates and prints until the last value
				cout << temp->value << ", ";
				temp = temp->next;
			}
			cout << temp->value << "]\n";//prints the last value

		}
		else
			cout << "Please use the Create function first.\n";
	}

	
};

class implement {

public:
	linkedList list;

	//determine takes a string in and outputs an integer
	//determine takes in the command the user entered and outputs an integer
	//correlating to a function
	int determine(string input) {

		int decision = -1;
		if (input == "create")
			decision = 1;
		else if (input == "addfront")
			decision = 2;
		else if (input == "addback")
			decision = 3;
		else if (input == "insert")
			decision = 4;
		else if (input == "size")
			decision = 5;
		else if (input == "delfront")
			decision = 6;
		else if (input == "delback")
			decision = 7;
		else if (input == "del")
			decision = 8;
		else if (input == "print")
			decision = 9;
		else if (input == "exit")
			decision = 10;
		return decision;
	}


	//executer takes in a string and outputs nothing
	//executer uses the string and runs determine to get an integer and runs the specified function
	void executer(string input) {
		int decider = determine(input);//runs determine to determine the function that needs to be called
		switch (decider)//chooses the desired function
		{
		case 1:
			if (param1==-666 && param2==-666)//makes sure no parameters were passed
				list.construct();
			else {
				cout << "Please enter a valid command.\n";
				param1 = param2 = -666;
			}
			break;
		case 2:
			list.addElementFront();
			break;
		case 3:
			list.addElementBack();
			break;
		case 4:
			list.instertElement();
			break;
		case 5:
			list.size();
			cout << "The size of the linked list is " << sizeOfLL << ".\n";
			break;
		case 6:
			list.removeFront();
			break;
		case 7:
			list.removeBack();
			break;
		case 8:
			list.deleteElement();
			break;
		case 9:
			list.print();
			break;
		case 10:
			cout << "Have a nice day.\n";//exit
			break;
		default:
			cout << "Please enter a valid command.\n";//if nothing matches the command
			param1 = param2 = -666;
		}
	}

};


int main()
{
	string input = "Please enter a valid input.";//defaults the string input to invalid
	linkedList list;
	implement implementer;
	while (input != "exit") {//keeps running unless the user wants to exit
		cout << "Enter a command (Only positive integers): ";
		input = list.getInput();//fetches and trimms the input to pass into the executer
		implementer.executer(input);//runs executer to run the functions
	}

	return 0;
}