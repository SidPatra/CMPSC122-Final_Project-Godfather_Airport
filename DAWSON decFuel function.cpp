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