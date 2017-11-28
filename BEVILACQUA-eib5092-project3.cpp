/*
** Name: BEVILACQUA-eib5092-project3.cpp
**
** Purpose: To create a dynamically allocated array through a link list. A link list is a series of elements
** which each contain a value, and pointers to the next value and previous value in the array.
**
** Author: Erin Bevilacqua, email: eib5092@psu.edu, phone: (814) 470-9648
**	
** Limitations: Insert limited by size of the link list.
**
** Revision History: Version 1.0 10.17.2017
*/

#include "stdafx.h"
#include <iostream>
#include <sstream>
using namespace std;


/* Name: element
** Purpose: a structure to contain each element of the link list and what it links to.
** The parts of the structure are: value, which is the content of that piece of the array,
** *nextElement, which is a pointer to the next element
** and *prevElement, which is a pointer to the previous element.
*/
struct element {
	int value;
	element *nextElement, *prevElement;
};

/* Name: LinkList
** Purpose: Create a dynamic array class that will be able to store and manipulate the array as per the user's
** commands, using a link list system.
** Limitations:
** Inputs/Outputs: Differ by function within the class.
*/
class LinkList {
private:
	element *firstElement = nullptr;     // pointer to the first element of the link list, initializes to null
	element *lastElement = nullptr;      // pointer to the last element of the link list, initializes to null
	int n = 0;                               // length of the array
public:
	/* Name: construct
	** Purpose: to construct an array of length 0, i.e. clear any data contained and construct a new array
	** Only used when the array is not already length 0.
	*/
	LinkList() {
		element *firstElement = nullptr;
		element *lastElement = nullptr;
		n = 0;
	}
	/* Name: addElementFront
	** Purpose: to add an element to the front of the array
	** Inputs: a value for the element to be added to the front of the array
	** Algorithm: Creates a new element, which next points to the previous first element (or null if firstElement is null)
	** and whose prev points to null. Increments n.
	*/
	void addElementFront(int inputValue) {
		element *newElement = new element;   // Create a new element for the array to go to the front
		newElement->value = inputValue;
		newElement->prevElement = nullptr;
		if (n == 0) {
			newElement->nextElement = nullptr;  // If n=0, no element following, must point to null
			lastElement = newElement;  // newElement is both first and last Element
		}
		else {
			newElement->nextElement = firstElement;   // The element following new is the previous firstElement
			firstElement->prevElement = newElement;   // The newElement is now the previous element for firstElement
		}
		firstElement = newElement;  //reset firstElement as the newElement
		n++;
	}
	/* Name: addElementBack
	** Purpose: to add an element to the back of the array
	** Inputs: a value for the element to be added to the back of the array
	** Algorithm: Creates a new element, which prev points to the previous last element (or null if lastElement is null)
	** and whose next points to null. Increments n.
	*/
	void addElementBack(int inputValue) {
		element *newElement = new element;   //Create a new element for the array to go to the back
		newElement->value = inputValue;
		newElement->nextElement = nullptr;
		if (n == 0) {
			newElement->prevElement = nullptr;  // If n=0, no element prior, must point to null
			firstElement = newElement;  // newElement is both the first and last element
		}
		else {
			newElement->prevElement = lastElement;   // The element before new is the previous lastElement
			lastElement->nextElement = newElement;   // New is now the next element for lastElement
		}
		lastElement = newElement;  //reset lastElement as the newElement
		n++;
	}
	/* Name: insertElement
	** Purpose: to insert an element at the specified location
	** Limitations: will only insert an element from the first position in the array to one beyond the last position
	** Inputs: a value for the element and a location for the element
	** Algorithm: If attempting to insert somewhere greater than 1 and less than or equal to the size, will
	** create a temporary element that is set as the first element to iterate through the list to the position
	** one before where the element is to be inserted. Then, it will make the element following this one next
	** and will create a new element called newElement for. newElement->value will be in the inputValue,
	** newElement->prevElement will be set to tmp, newElement->nextElement will be set to next.
	** To complete the insertion. tmp->nextElement will be set to the newElement, as will next->prevElement.
	*/
	void insertElement(int inputValue, int inputLocation) {
		if (inputLocation < 1 || inputLocation > size() + 1) {
			cout << "Location is out of range. Please use location between 1 and " << size() + 1 <<".\n";
		}
		else if (inputLocation == 1) {    // Same as adding the element to the front
			addElementFront(inputValue);
		}
		else if (inputLocation == size() + 1) {    // Same as adding the element to the back
			addElementBack(inputValue);
		}
		else {
			element *tmp = firstElement;   // Temporary element set as the firstElement to iterate through the list with
			for (int i = 0; i < inputLocation - 2; i++) {  // Find element one before location to insert
				tmp = tmp->nextElement;
			}
			element *next = tmp->nextElement;   // Next is the element previously at the location to insert
			element *newElement = new element;  // Allocate memory for the newElement that will contain inputValue and
												// Will be inserted at inputLocation
			newElement->value = inputValue;
			newElement->prevElement = tmp;
			newElement->nextElement = next;
			tmp->nextElement = newElement;
			next->prevElement = newElement;
			n++;
		}
	}
	/* Name: deleteElement
	** Purpose: to delete the first occurrence of an element with given inputValue
	** Limitations: only deletes the first occurrence
	** Inputs: the value that is to be deleted
	** Algorithm: if there are elements in the list, tmp will iterate through the list until it finds
	** an element with the value to be deleted. Then, an element next will be created which is tmp->nextElement
	** and an element prev will be create which is tmp->prevElement. As long as next is not null, its prevElement
	** will be set to prev. Same for prev with next. If next is null, then lastElement will be set to prev,
	** and if prev is null, then firstElement will be set to next. Then, tmp will be deleted to free memory space.
	*/
	void deleteElement(int inputValue) {
		if (size() == 0) {
			cout << "There are no elements to delete.\n";
		}
		else {
			element *tmp = firstElement;   // Make a temporary element set to first to iterate through the list
			while (tmp) {
				if (tmp->value == inputValue) {    // Look for value to be deleted, break if found
					break;
				}
				tmp = tmp->nextElement;  // Continue to iterate through the list if not broken
			}
			if (tmp == nullptr) {   // Iterated through full list but did not find value
				cout << "Value not found in the array.\n";
			}
			else {
				element *next = tmp->nextElement;  // Make temporary element for element following tmp
				element *prev = tmp->prevElement;  // Make temporary element for element before tmp
				if (next) {   // If next is not null, then make next prevElement point to the element before tmp
					next->prevElement = prev;
				}
				else {   // If next is null, make the element before tmp be the last element
					lastElement = prev;
				}
				if (prev) {   // If prev is not null, make prev nextElement point to the element after tmp
					prev->nextElement = next;
				}
				else {   // If prev is null, make the element after tmp be the last element
					firstElement = next;
				}
				delete tmp;    // Delete data stored in tmp
				n--;

			}
		}

	}
	/* Name: removeFront
	** Purpose: delete the first element in the link list
	** Algorithm: If size is one, will make a temporary element set to first, and then will set both first and last
	** to nullptr, as after removing the front the list will be empty. Then, n is set to 0 and tmp is deleted.
	** If size is greater than one, will make a temporary element set to first. Then, firstElement will become firstElement->
	** nextElement (as the element following the first will be the first after the first is deleted), and 
	** the new firstElement->prevElement will be set to nullptr. n will be decremented and tmp is deleted.
	*/
	void removeFront() {
		if (size() == 0) {
			cout << "There are no elements to delete.\n";
		}
		else if (size() == 1) {
			element *tmp = firstElement;     // Make a temporary element set to first so it can be deleted
			firstElement = nullptr;      // Set both first and last to nullptr because the array will be empty
			lastElement = nullptr;
			n = 0;
			delete tmp;   //Delete data stored in tmp
		}
		else {
			element *tmp = firstElement;    // Make a temporary element set to first so it can be deleted
			firstElement = firstElement->nextElement; // Make firstElement be the old 2nd element
			firstElement->prevElement = nullptr;  // Make the new firstElement prev be null
			n--;
			delete tmp;
		}

	}
	/* Name: removeBack
	** Purpose: delete the last element in the link list
	** Algorithm: Very similar to removeFront, just switch the first/last and next/prev.
	*/
	void removeBack() {
		if (size() == 0) {
			cout << "There are no elements to delete.\n";
		}
		else if (size() == 1) {
			element *tmp = lastElement;  // Make a temporary element set to first so it can be deleted
			firstElement = nullptr;
			lastElement = nullptr;
			n = 0;
			delete tmp;
		}
		else {
			element *tmp = lastElement;  // Make a temporary element set to first so it can be deleted
			lastElement = lastElement->prevElement;
			lastElement->nextElement = nullptr;
			n--;
			delete tmp;
		}
	}
	/* Name: size
	** Purpose: to return the size of the array
	** Outputs: returns n, the number of elements in the array
	*/
	int size() {
		return n;
	}
	/* Name: print
	** Purpose: to print out all of the elements stored in the array
	** Outputs: prints the elements out for the user
	*/
	void print() {
		if (size() != 0) {
			element *tmp = firstElement;  //
			while (tmp) {
				cout << tmp->value << "    ";
				tmp = tmp->nextElement;
			}
			cout << endl;
			delete tmp;
		}
		else {
			cout << "The array is empty.\n";
		}
	}
	/* Name: ~LinkList
	** Purpose: destructor, deletes the LinkList when called
	** Limitations:
	** Inputs:
	** Outputs:
	*/
	~LinkList() {
		element *tmp = firstElement;  // Make a temporary element to iterate through the list

		while (tmp != nullptr) {
			element *next = tmp->nextElement;
			delete tmp;
			tmp = next;
		}
		firstElement = nullptr;

	}
};


/* Name: makeLower
** Purpose: to make a string all lower case so it can be used regardless of case
** Inputs: takes a string that may be both capital and lowercase
** Outputs: returns a string that is all lowercase
*/
string makeLower(string mixedInput) {
	for (int i = 0; i < mixedInput.length(); i++) {
		mixedInput[i] = tolower(mixedInput[i]);
	}
	return mixedInput;
}

/* Name: isInt
** Purpose: to check if a string only contains input, and as such can be used by the functions in DynamicArray
** Inputs: takes a string
** Outputs: a bool that is true if the string is all ints or is false if the string contains non integers
*/
bool isInt(string str) {
	bool allInt = true;
	if ((str[0] < '0' || str[0] > '9') && str[0] != '-') {
		allInt = false;
	}
	for (int i = 1; i < str.length(); i++) {
		if (str[i] < '0' || str[i] > '9') {
			allInt = false;
		}
	}
	return allInt;
}

void splitInput(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] = ' ') {

		}
	}
}

/* Name: RunProgram
** Purpose: run through the array and allow user to manipulate
*/
class RunProgram {
private:
	LinkList MyArray;  // Create an array of class LinkList named MyArray
	string inputMethod = "";  // Create a string to collect user's input
	string strElement, strPosition;  // Creates strings to store the elements and positions entered by user
	int element, position;  // Creates ints to store integer versions of above strings as long as they are all int
public:
	/* Name: directory
	** Purpose: to output all options available to a user so they know what they are able to do to the array.
	** Output: a directory of methods available to the user.
	*/
	void directory() {
		cout << "\n************************************************************************************************************\n";
		cout << "*                                              ~USER OPTIONS~                                              *\n";
		cout << "*             NOTE: User commands are NOT case sensitve. <location> and <num> MUST be integers.            *\n";
		cout << "*'Create' creates a new linklist and deletes the old list as long as the list has already been allocated.  *\n";
		cout << "*'AddFront <num>' adds the specified number to the front of the linklist.                                  *\n";
		cout << "*'AddBack <num>' adds the specified number to the back of the linklist.                                    *\n";
		cout << "*'Insert <location>, <num>' inserts the specified num into the specified location, assuming it's in range. *\n";
		cout << "*'Del <num>' deletes the first instance of the specified num in the linklist.                              *\n";
		cout << "*'DelFront' deletes the number stored in the front of the linklist.                                        *\n";
		cout << "*'DelBack' deletes the number stored in the back of the linklist.                                          *\n";
		cout << "*'Size' outputs the current size of the linklist.                                                          *\n";
		cout << "*'Print' prints the linklist.                                                                              *\n";
		cout << "*'Exit' exits the program.                                                                                 *\n";
		cout << "*'Help' outputs the directory.                                                                             *\n";
		cout << "************************************************************************************************************\n\n";
	}
	
	
	/* Name: run
	** Purpose: to allow user to manipulate the array through output and input statements that correspond to actions
	** Limitations: user must correctly enter data, or they have to start over a reinput what method they want to use
	** Inputs: asks for on of 'create' 'addFront' 'addBack' 'insert' 'del' 'delFront' 'delBack' 'size' 'print' 'exit'
	** Followed by integers, depending on the function called
	** Outputs: Depends on function called
	*/
	void run() {
		while (inputMethod != "exit") {   // continues to run until user manually tells program to exit
			cout << "What would you like to do to the link list array? Type 'help' for directory and 'exit' to exit.\n";
			cin >> inputMethod;
			inputMethod = makeLower(inputMethod);  // allows for any capitalization
			if (inputMethod == "help") {
				directory();
			}
			else if (inputMethod == "create") {  // deletes old link list and constructs new one, as long as old one > 0.
				if (MyArray.size() > 0) {
					MyArray.~LinkList(); 
					MyArray = LinkList();
				}
			}
			else if (inputMethod == "addfront") {
				cin >> strElement;
				if (isInt(strElement)) {   // Checks if number entered is actually integer
					element = stoi(strElement);   // Converts to integer if above is true
					MyArray.addElementFront(element);   // Uses function in class to add the element
				}
				else {   // If not integer, asks for an integer instead and returns to ask for input
					cout << "Invalid input. Please use an integer.\n";
				}
			}
			else if (inputMethod == "addback") {
				cin >> strElement;
				if (isInt(strElement)) {    // Checks if number entered is actually integer
					element = stoi(strElement);   // Converts to integer if above is true
					MyArray.addElementBack(element);   // Uses function in class to add the element
				}
				else {
					cout << "Invalid input. Please use an integer.\n";
				}
			}
			else if (inputMethod == "insert") {
				cin >> strPosition;
				// If the last character of strPosition is comma, as directed for input, will delete the comma
				// and produce a new strPosition without a comma, which can be used as an integer.
				// However, if user enters something like "insert 10 3" the strPosition will not be edited,
				// and this can still be used. 
				if (strPosition[strPosition.length() - 1] == ',') {   
					strPosition = strPosition.substr(0, strPosition.length() - 1);
				}
				cin >> strElement;
				if (isInt(strPosition) && isInt(strElement)) {    // Checks if numbers entered are actually integers
					position = stoi(strPosition);
					element = stoi(strElement);
					MyArray.insertElement(element, position);   // Uses function in class to inert element
				}
				else {
					cout << "Invalid input. Please use two integers.\n";
				}

			}
			else if (inputMethod == "del") {
				cin >> strElement;
				if (MyArray.size() == 0) {
					cout << "There is nothing to delete.\n";
				}
				else {
					if (isInt(strElement)) {    // Checks if number entered is actually integer
						element = stoi(strElement);
						MyArray.deleteElement(element);    // Uses function in class to delete element
					}
					else {
						cout << "Invalid input. Please use an integer.\n";
					}
				}

			}
			else if (inputMethod == "delfront") {    // Calls function in class to delete front
				MyArray.removeFront();
			}
			else if (inputMethod == "delback") {     // Calls function in class to delete back
				MyArray.removeBack();
			}
			else if (inputMethod == "size") {
				int size = MyArray.size();    // Creates an int to store the size returned from MyArray.size();
				cout << "The size of the array is " << size << ".\n";    // Outputs for user
																		 // Output not in class because size is used to return the size without printing it.
			}
			else if (inputMethod == "print") {     // Calls function in class to print
				MyArray.print();
			}
			else if (inputMethod != "exit") {    // User types something other than the above, will request that user inputs new function
				cout << "Invalid input. Please refer to directory for allowed input.\n";
			}
		}
	}
};

/* Name: main()
** Purpose: to create an instance of the class RunProgram and then use the function in RunProgram to run it
*/
int main()
{
	RunProgram myRun;
	myRun.run();
}
