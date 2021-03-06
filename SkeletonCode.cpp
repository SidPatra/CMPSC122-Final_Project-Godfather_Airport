// Name:		SkeletonCode
// Author:		Donavan Keen
// Purpose:		This program holds skeletons for the project


// Add includes to this skeleton file if you use them in other files
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

// Name:		LinkedList
// Author:		Donavan Keen
// Purpose:		This class holds a List of integers to create a dynamic
//				array.
// Limitations:	This class only can only store integer values.
class LinkedList {};

// Global variables for keeping statistics
int totalTimeWaited = 0;	// Total time all planes have waited
int numCrashes = 0;			// Number of planes that have crashed
int numLandWait = 0;		// Number of planes waiting on land (onGround.getSize())
int numAirWait = 0;			// Number of planes waiting in air (inAir.getSize())
int numDep = 0;				// Number of planes that have departed
int numArr = 0;				// Number of planes that have landed
int numPplSafe = 0;			// Number of people who are safe
int numPplDead = 0;			// Number of people who have died
int numGCSafe = 0;			// Number of grandchildren who are safe
int numGCDead = 0;			// Number of grandchildren who have died
int totalGCWait = 0;		// Total time grandchildren have waited
int totalTime = 0;			// Total time the program has spent running
int totalPlanes = 0;		// Number of planes that have been entered into the program
float cargoSafe = 0;		// Value of cargo that is safe
float cargoDead = 0;		// Value of carge that is dead


//Global Lists
LinkedList inAir;			// Planes currently flying, trying to land
LinkedList onGround;		// Planes currently on ground, trying to take off
LinkedList atRefuel;		// Planes refueling

// Name:		print()
// Author:		
// Purpose:		This function prints the statistics that are required by the god father
// Inputs:		None
// Outputs:		None
void print() {}

// Name:		decRefuel()
// Author:    Matt Dawson		
// Purpose:		This function decrements the refueling attribute of all planes in LinkedList atRefuel,
//				and moves planes with refueling value 0 (after the decrement) to LinkedList onGround
// Inputs:		None
// Outputs:		None
void decRefuel() {}

// Name:		decFuel()
// Author:		Erin Bevilacqua
// Purpose:		This function decrements the fuel of all planes (land and air)
// Inputs:		None
// Outputs:		None
void decFuel() {}

// Name:		checkGroundFuel()
// Author:		Sid Patra
// Purpose:		This function checks the fuel of every plane on the ground and calls refuel()
//				if the fuel iis below 20.
// Inputs:		None
// Outputs:		None
void checkGroundFuel() {}

// Name:		refuel( LinkedList::Node* plane )
// Author:		Donavan Keen
// Purpose:		This function sets the refueling attribute of the plane to 20 and moves it from the onGround list
//				to the atRefuel list.
// Inputs:		Pointer to plane that needs refueled
// Outputs:		None
void refuel(LinkedList::Node* plane) {

}

// Name:		checkAirFuel()
// Author:		Nikhil Nayyar
// Purpose:		This function checks the fuel of every plane in the air and calls crash() 
//				if the fuel is 0.
// Inputs:		None
// Outputs:		None
void checkAirFuel() {}

// Name:		crash( LinkedList::Node* plane )
// Author:		Cole Cugini
// Purpose:		This function adjusts statistics and calls the delete function for the plane that has crashed
// Inputs:		Pointer to plane that has crashed
// Outputs:		None
void crash(LinkedList::Node* plane) {}

// Name:		incWaitTime()
// Author:		Erin Bevilacqua
// Purpose:		This function increments waitTime attribute of every plane in every list
// Inputs:		None
// Outputs:		None
void incWaitTime() {}

// Name:		takeOff( LinkedList::Node* plane )
// Author:		Nikhil Nayyar
// Purpose:		This function adjusts statistics and calls the delete function for the plane that will take off
// Inputs:		Pointer to plane to take off
// Outputs:		None
void takeOff(LinkedList::Node* plane) {}

// Name:		land( LinkedList::Node* plane )
// Author:		Nikhil Nayyar
// Purpose:		This function adjusts statistics and calls the delete function for the plane that will land
// Inputs:		Pointer to plane to land
// Outputs:		None
void land(LinkedList::Node* plane) {}

// Name:		main()
// Author:		Everyone
// Purpose:		This function holds the main logic of the program and calls the appropriate
//				functions regarding algorithm decisions
// Inputs:		None
// Outputs:		None
void main() {}

