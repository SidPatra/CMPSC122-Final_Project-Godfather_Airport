// Name:		GlencoOliveOilCo
// Authors:		Erin Bevilacqua, Cole Cugini, Matt Dawson, Donavan Keen, Siddharth Patra, Nikhil Nayyar
// Purpose:		This program loads input from a file "input.txt" and runs an air traffic control and scheduling algorithm
//				and keeps stats on crashes and successful actions (landing and taking off).

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Name:		LinkedList
// Author:		Donavan Keen
// Purpose:		This class holds a List of plane structures
class LinkedList
{
public:
	struct Node
	{
		int id;			// id number to keep track of plane (used for deletion specifically)
		int action;		// 0 for departing, 1 for landing
		int refueling;	// 0 for not refueling, 1-9 for time left while refueling
		int score;
		int people;		// Number of people onboard
		float cargo;	// Value of cargo onboard
		int waitTime;	// Time plane has spent waiting
		int fuel;		// Fuel left in the plane
		int fuelCap;	// Fuel capacity of the plane (The initial fuel of the plane)
		int grandChild; // 0 for no grandChild, 1 for grandChild
		Node* next;
		Node* prev;

		// Name:	LinkedList::Node:Node( Node* p, Node* n)
		// Purpose:	Initializes values for the Node
		// Inputs:	Node* p = prev, Node* n = next
		// Outputs:	None
		Node(Node* values)
		{
			id = values->id;
			action = values->action;
			refueling = values->refueling;
			score = values->score;
			people = values->people;
			cargo = values->cargo;
			waitTime = values->waitTime;
			fuel = values->fuel;
			fuelCap = values->fuelCap;
			grandChild = values->grandChild;
			next = nullptr;
			prev = nullptr;
		}
		Node()
		{
			refueling = 0;
			score = 0;
			waitTime = 0;
			next = nullptr;
			prev = nullptr;
		}
	};


	// Name:		LinkedList::LinkedList()
	// Purpose:		This function acts as a constructor for the LinkedList class.
	//				it creates the first node.
	// Inputs:		None
	// Outputs:		None
	LinkedList::LinkedList()
	{
		first = nullptr;
		last = nullptr;
	}

	// Name:		LinkedList::~LinkedList()
	// Purpose:		This function frees the memory of the
	//				list to make sure there are no memory leaks
	// Inputs:		None
	// Outputs:		None
	LinkedList::~LinkedList()
	{
		Node* current = first;
		Node* next;

		for (int i = 0; i < sizeNum - 1; i++)
		{
			next = current->next;
			delete(current);
			current = next;
		}
		if (last != nullptr)
		{
			delete(last);
		}
		sizeNum = 0;
	}

	// Name:		LinkedList::addElementBack(int x)
	// Purpose:		This function adds an element to the bacl of the LinkedList
	// Inputs:		integer, value to be added
	// Outputs:		None
	void LinkedList::addElementBack(LinkedList::Node* plane)
	{
		if (first == nullptr)
		{
			first = plane;
			last = first;
		}
		else
		{
			Node* tmpPtr = last;
			last = plane;				// Adding the element to the back
			last->prev = tmpPtr;		// Assigns new node's prev to old last
			tmpPtr->next = last;		// Assigns old last's next to new node 
		}
		sizeNum++;
	}

	// Name:		LinkedList::deleteElement(int x)
	// Purpose:		This function deletes an element with the value passed to it
	// Inputs:		integer, id to be deleted
	// Outputs:		None
	// Limitations:	This function only deletes the first value found to match the input
	void LinkedList::deleteElement(int x)
	{
		bool deleted = false;
		Node* currentPtr = first;
		int i = 0;

		if (first == nullptr)
		{
			// This block just ensures we don't try to dereference a nullptr.
			// It is here as protection, from here, we check if the value was
			// deleted and print that the value was not found and not deleted.
			cout << "NOT DELETED MUHFUCKA" << endl;
		}

		else if (first->id == x)
		{
			this->removeFront();
			deleted = true;

		}
		else if (last->id == x)
		{
			this->removeBack();
			deleted = true;
		}
		else
		{
			while (!deleted && i < sizeNum - 1)
			{
				if (currentPtr->id == x)
				{

					(currentPtr->prev)->next = currentPtr->next;
					(currentPtr->next)->prev = currentPtr->prev;

					delete(currentPtr);

					currentPtr = nullptr;
					deleted = true;
					sizeNum--;
				}
				else
				{
					currentPtr = currentPtr->next;
				}
				i++;
			}
		}
	}

	// Name:		LinkedList::removeFront()
	// Purpose:		This function deletes the element at the front of the LinkedList
	// Inputs:		None
	// Outputs:		None
	void LinkedList::removeFront()
	{
		if (sizeNum == 0)
		{
		}
		else if (sizeNum == 1)
		{
			// Special case where there is only one node in the list
			delete(first);
			first = nullptr;
			last = nullptr;
			sizeNum--;
		}
		else
		{
			Node* tmpPtr = first->next;
			delete(first);
			first = tmpPtr;
			tmpPtr->prev = nullptr;
			sizeNum--;
		}
	}

	// Name:		LinkedList::removeBack()
	// Purpose:		This function deletes the element at the back of the LinkedList
	// Inputs:		None
	// Outputs:		None
	void LinkedList::removeBack()
	{
		if (sizeNum == 0)
		{
			cout << endl << "The List is Empty." << endl;
		}
		else if (sizeNum == 1)
		{
			// Special case where there is only one node in the list
			delete(first);
			first = nullptr;
			last = nullptr;
			sizeNum--;
		}
		else
		{
			Node* tmpPtr = last->prev;
			delete(last);
			last = tmpPtr;
			tmpPtr->next = nullptr;
			sizeNum--;
		}
	}

	// Name:		LinkedList::getFirst()
	// Purpose:		This function returns a pointer to the first node
	//				of the LinkedList
	// Inputs:		None
	// Outputs:		Pointer to first node in the list
	Node* LinkedList::getFirst()
	{
		return first;
	}

	// Name:		LinkedList::getLast()
	// Purpose:		This function returns a pointer to the last node
	//				of the LinkedList
	// Inputs:		None
	// Outputs:		Pointer to last node in the list
	Node* LinkedList::getLast()
	{
		return last;
	}


	// Name:		LinkedList::getSize()
	// Purpose:		This function returns the size of the LinkedList
	// Inputs:		None
	// Outputs:		int, sizeNum
	int LinkedList::getSize()
	{
		return sizeNum;
	}

private:
	Node* first;
	Node* last;
	int sizeNum = 0;
};


// Global variables for keeping statistics
int totalTimeWaitedAir = 0;		// Total time waited for planes in the air
int totalTimeWaitedGround = 0;	// Total time waited for planes on the ground
int numCrashes = 0;				// Number of planes that have crashed
int numLandWait = 0;			// Number of planes waiting on land (onGround.getSize())
int numAirWait = 0;				// Number of planes waiting in air (inAir.getSize())
int numDep = 0;					// Number of planes that have departed
int numArr = 0;					// Number of planes that have landed
int numPplSafe = 0;				// Number of people who are safe
int numPplDead = 0;				// Number of people who have died
int numGCSafe = 0;				// Number of grandchildren who are safe
int numGCDead = 0;				// Number of grandchildren who have died
int totalGCWait = 0;			// Total time grandchildren have waited
int totalTime = 0;				// Total time the program has spent running
int totalPlanes = 0;			// Number of planes that have been entered into the program
float cargoSafe = 0;			// Value of cargo that is safe
float cargoDead = 0;			// Value of carge that is dead

//Global Lists
LinkedList inAir = LinkedList();			// Planes currently flying, trying to land
LinkedList onGround = LinkedList();			// Planes currently on ground, trying to take off
LinkedList atRefuel = LinkedList();			// Planes refueling
LinkedList::Node* takeAction[2];			// Holds planes with two highest scores

// Name:		print()
// Author:		Erin Bevilacqua
// Purpose:		This function prints the statistics that are required by the god father
// Inputs:		None
// Outputs:		None
void print() {
	cout << "Average take off wait time: ";
	if (numDep == 0)
		cout << "NA" << endl;
	else
		cout << ((float)totalTimeWaitedAir) / ((float)numDep) << endl;
	cout << "Average landing wait time: ";
	if (numArr == 0)
		cout << "NA" << endl;
	else
		cout << ((float)totalTimeWaitedGround) / ((float)numArr) << endl;
	cout << "Number of crashed planes: " << numCrashes << endl;
	cout << "Number of departed planes: " << numDep << endl;
	cout << "Number of arrived planes: " << numArr << endl;
	cout << "Number of people safe: " << numPplSafe << endl;
	cout << "Number of people killed: " << numPplDead << endl;
	cout << "Number of grandchildren safe: " << numGCSafe << endl;
	cout << "Number of grandchildren killed: " << numGCDead << endl;
	cout << "Average wait time for a grandchild Arriving or Departing: ";
	if (numGCSafe == 0)
		cout << "NA" << endl;
	else
		cout << ((float)totalGCWait) / ((float)numGCSafe) << endl;
	cout << "Amount of cargo that landed safely: " << cargoSafe << endl;
	cout << "Amount of destroyed Cargo: " << cargoDead << endl;
	cout << "Amount of time it takes to process a input: " << totalTime << endl;
}

// Name:		decRefuel()
// Author:    		Erin Bevilacqua		
// Purpose:		This function decrements the refueling attribute of all planes in LinkedList atRefuel,
//				and moves planes with refueling value 0 (after the decrement) to LinkedList onGround
// Inputs:		None
// Outputs:		None
void decRefuel() {
	LinkedList::Node* currentPtr = atRefuel.getFirst();
	while (currentPtr != nullptr)
	{
		currentPtr->refueling--;
		if (currentPtr->refueling == 0)
		{
			LinkedList::Node* temp = new LinkedList::Node(currentPtr);
			currentPtr = temp->next;
			temp->fuel = temp->fuelCap;
			onGround.addElementBack(temp);
			atRefuel.deleteElement(temp->id);
		}
		else
		{
			currentPtr = currentPtr->next;
		}
	}
}

// Name:		decFuel()
// Author:		Matthew Dawson
// Purpose:		This function decrements the fuel of all planes in the land and air (excluding those in refuel) 
// Inputs:		None
// Outputs:		None
void decFuel() {
	LinkedList::Node* currentPtr;
	// Traverse the onGround LinkedList and decrement each plane's fuel by one. This occurs every time period. 
	currentPtr = onGround.getFirst();
	while (currentPtr != nullptr) {
		currentPtr->fuel--;
		currentPtr = currentPtr->next;
	}
	// Traverse the inAir LinkedList and decrement each plane's fuel by one. This occurs every time period. 
	currentPtr = inAir.getFirst();
	while (currentPtr != nullptr) {
		currentPtr->fuel--;
		currentPtr = currentPtr->next;
	}
}

// Name:		refuel( LinkedList::Node* plane )
// Author:		Donavan Keen
// Purpose:		This function sets the refueling attribute of the plane to 20 and moves it from the onGround list
//				to the atRefuel list.
// Inputs:		Pointer to plane that needs refueled
// Outputs:		None
void refuel(LinkedList::Node* plane) {
	LinkedList::Node* temp = new LinkedList::Node(plane);
	onGround.deleteElement(plane->id);
	atRefuel.addElementBack(temp);
}

// Name:		checkGroundFuel()
// Author:		Sid Patra
// Purpose:		This function checks the fuel of every plane on the ground and calls refuel()
//				if the fuel is below 20.
// Inputs:		None
// Outputs:		None
void checkGroundFuel()
{
	LinkedList::Node* currentPtr = onGround.getFirst();
	while (currentPtr != nullptr)
	{
		if (currentPtr->fuel < 20)
		{
			LinkedList::Node* temp = currentPtr->next;
			currentPtr->refueling = 9;
			refuel(currentPtr);		// is this how I am supposed to do this?
			currentPtr = temp;
		}
		else
		{
			currentPtr = currentPtr->next;
		}
	}
}

// Name:		crash( LinkedList::Node* plane )
// Author:		Cole Cugini
// Purpose:		This function adjusts statistics and calls the delete function for the plane that has crashed
// Inputs:		Pointer to plane that has crashed
// Outputs:		None
void crash(LinkedList::Node* plane) {
	numCrashes++;							// Number of planes that have crashed
	numPplDead += plane->people;			// Number of people who have died
	numGCDead += plane->grandChild;			// Number of grandchildren who have died
	cargoDead += plane->cargo;				// Value of cargo that crashed
	inAir.deleteElement(plane->id);
}

// Name:		checkAirFuel()
// Author:		Nikhil Nayyar
// Purpose:		This function checks the fuel of every plane in the air and calls crash() 
//				if the fuel is 0.
// Inputs:		None
// Outputs:		None
void checkAirFuel() {
	LinkedList::Node* currentPtr = inAir.getFirst();
	while (currentPtr != nullptr) {
		if (currentPtr->fuel == 0) {
			LinkedList::Node* tmpPtr = currentPtr;
			currentPtr = currentPtr->next;
			crash(tmpPtr);
		}
		else
		{
			currentPtr = currentPtr->next;
		}
	}
}

// Name:		incWaitTime()
// Author:      Erin Bevilacqua
// Purpose:		This function increments waitTime attribute of every plane in every list
// Inputs:		None
// Outputs:		None
void incWaitTime() {
	LinkedList::Node* temp;

	// Traverse through inAir, onGround, and atRefuel and increment waitTime by one.
	temp = inAir.getFirst();
	while (temp != nullptr) {
		temp->waitTime++;
		temp = temp->next;
	}

	temp = onGround.getFirst();
	while (temp != nullptr) {
		temp->waitTime++;
		temp = temp->next;
	}

	temp = atRefuel.getFirst();
	while (temp != nullptr) {
		temp->waitTime++;
		temp = temp->next;
	}
}

// Name:		takeOff( LinkedList::Node* plane )
// Author:		Nikhil Nayyar
// Purpose:		This function adjusts statistics and calls the delete function for the plane that will take off
// Inputs:		Pointer to plane to take off
// Outputs:		None
void takeOff(LinkedList::Node* plane) {
	numDep += 1;
	numLandWait += plane->waitTime;
	numGCSafe += plane->grandChild;
	totalGCWait += plane->waitTime * (plane->grandChild);
	onGround.deleteElement(plane->id);
}

// Name:		land( LinkedList::Node* plane )
// Author:		Nikhil Nayyar
// Purpose:		This function adjusts statistics and calls the delete function for the plane that will land
// Inputs:		Pointer to plane to land
// Outputs:		None
void land(LinkedList::Node* plane) {
	numArr += 1;
	numPplSafe += plane->people;
	numGCSafe += plane->grandChild;
	cargoSafe += plane->cargo;
	numAirWait += plane->waitTime;
	totalGCWait += plane->waitTime * (plane->grandChild);
	inAir.deleteElement(plane->id);
}

// Name:		calcScore( LinkedList::Node* plane )
// Author:		
// Purpose:		Calculates score based on weights GC + 1000, Cargo: (int) cargo * .001, People: + people
//				divided by fuel.
// Inputs:		Pointer to plane whose score is being calculated
// Outputs:		None
void calcScore(LinkedList::Node* plane) {
	if (plane->fuel != 0)
	{
		plane->score = ((1000 * plane->grandChild) + (int)(plane->cargo*.001 + plane->people)) / plane->fuel;
	}
}

// Name:		main()
// Author:		Everyone
// Purpose:		This function holds the main logic of the program and calls the appropriate
//				functions regarding algorithm decisions
// Inputs:		None
// Outputs:		None
void main() {
	string line;
	ifstream file;
	file.open("input.txt");
	bool brokeLoop = false;
	int time = 0;
	if (file.is_open())
	{
		getline(file, line);
		line += ",";
		string planeTime = "";
		int timeFindCounter = 2;
		char timeFindChar = line.at(timeFindCounter);
		while (timeFindChar != ',')
		{
			planeTime += timeFindChar;
			timeFindCounter++;
			timeFindChar = line.at(timeFindCounter);
		}
		while (!(file.eof()) || brokeLoop || ((inAir.getSize() + onGround.getSize() + atRefuel.getSize()) != 0 ))
		{
			// This while loop handles reading the input and performing the proper action.
			// If the time of action for a plane is greater than current time, 
			while ((line.length() == 2 || stoi(planeTime) <= time))
			{
				if (file.eof() && !(brokeLoop))
				{
					break;
				}

				if (totalPlanes > 0 && !(brokeLoop))
				{
					getline(file, line);
					line += ",";
					if (line.length() > 2)
					{
						planeTime = "";
						timeFindCounter = 2;
						timeFindChar = line.at(timeFindCounter);
						while (timeFindChar != ',')
						{
							planeTime += timeFindChar;
							timeFindCounter++;
							timeFindChar = line.at(timeFindCounter);
						}
					}
					
				}
				else
				{
					brokeLoop = false;
				}


				if (line == "P,")
				{
					print();
				}
				else if (line == "W,")
				{
					cout << endl << "Waiting...";
					cin.get();
				}
				else if (stoi(planeTime) > time)
				{
					brokeLoop = true;
					break;
				}
				else if (stoi(planeTime) == time)
				{
					LinkedList::Node* newPlane = new LinkedList::Node();
					newPlane->id = totalPlanes;
					totalPlanes++;

					int tokenNum = 0;
					string token = "";

					for (char c : line)
					{
						if (c == ',')
						{
							switch (tokenNum)
							{
							case 0:
								break;
							case 1:
								break;
							case 2:
								if (token == "A")
									newPlane->action = 1;
								else if (token == "D")
									newPlane->action = 0;
								break;
							case 3:
								newPlane->fuel = stoi(token);
								newPlane->fuelCap = newPlane->fuel;
								break;
							case 4:
								newPlane->people = stoi(token);
								break;
							case 5:
								newPlane->cargo = stof(token);
								break;
							case 6:
								if (token == "Y")
									newPlane->grandChild = 1;
								else if (token == "N")
									newPlane->grandChild = 0;
								break;
							}
							token = "";
							tokenNum++;
						}
						else
						{
							token += c;
						}
					} // End: for (char c : line)

					if (newPlane->action == 1)
					{
						inAir.addElementBack(newPlane);
					}
					else
					{
						if (newPlane->fuel < 20)
						{
							cout << endl<< "BAD INPUT YOU LOSE!" << endl;
							goto STOP;
						}
						onGround.addElementBack(newPlane);
					}

				}
			} // End: while (line.length == 1 || line[2] == time)



			int highScore1 = 0;
			int highScore2 = 0;
			int inTakeAction = 0;

			// Iterate through inAir looking for scores
			LinkedList::Node* currentPtr = inAir.getFirst();
			while (currentPtr != nullptr)
			{
				calcScore(currentPtr);

				// Case where the takeAction array is empty
				if (inTakeAction == 0)
				{
					takeAction[0] = currentPtr;
					highScore1 = currentPtr->score;
					inTakeAction++;
				}
				// Case where one spot in the takeAction array is empty
				else if (inTakeAction == 1)
				{
					takeAction[1] = currentPtr;
					highScore2 = currentPtr->score;
					inTakeAction++;
				}
				// Special case where current score is larger than both scores, must find lowest score and replace
				else if (currentPtr->score > highScore1 && (currentPtr->score > highScore2))
				{
					if (highScore1 < highScore2)
					{
						takeAction[0] = currentPtr;
						highScore1 = currentPtr->score;
					}
					else
					{
						takeAction[1] = currentPtr;
						highScore2 = currentPtr->score;
					}
				}
				else if (currentPtr->score > highScore1)
				{
					takeAction[0] = currentPtr;
					highScore1 = currentPtr->score;
				}
				else if (currentPtr->score > highScore2)
				{
					takeAction[1] = currentPtr;
					highScore2 = currentPtr->score;
				}
				currentPtr = currentPtr->next;
			} // End: while (currentPtr != nullptr)

			  // Iterate through onGround looking for scores
			currentPtr = onGround.getFirst();
			while (currentPtr != nullptr)
			{
				calcScore(currentPtr);

				// Case where the takeAction array is empty
				if (inTakeAction == 0)
				{
					takeAction[0] = currentPtr;
					highScore1 = currentPtr->score;
					inTakeAction++;
				}
				// Case where one spot in the takeAction array is empty
				else if (inTakeAction == 1)
				{
					takeAction[1] = currentPtr;
					highScore2 = currentPtr->score;
					inTakeAction++;
				}
				// Special case where current score is larger than both scores, must find lowest score and replace
				else if (currentPtr->score > highScore1 && (currentPtr->score > highScore2))
				{
					if (highScore1 < highScore2)
					{
						takeAction[0] = currentPtr;
						highScore1 = currentPtr->score;
					}
					else
					{
						takeAction[1] = currentPtr;
						highScore2 = currentPtr->score;
					}
				}
				else if (currentPtr->score > highScore1)
				{
					takeAction[0] = currentPtr;
					highScore1 = currentPtr->score;
				}
				else if (currentPtr->score > highScore2)
				{
					takeAction[1] = currentPtr;
					highScore2 = currentPtr->score;
				}
				currentPtr = currentPtr->next;
			} // End: while (currentPtr != nullptr)

			for (int i = 0; i < inTakeAction; i++)
			{
				if (takeAction[i]->action == 0)
				{
					takeOff(takeAction[i]);
				}
				else
				{
					land(takeAction[i]);
				}
			}

			decFuel();
			decRefuel();
			checkAirFuel();
			checkGroundFuel();
			incWaitTime();
			time++;

		} // End: while (!(file.eof()) && (inAir.getSize() + onGround.getSize() + atRefuel.getSize()) != 0)
		STOP:
		totalTime = time;
		print();
	} // End: if (file.is_open())
}
