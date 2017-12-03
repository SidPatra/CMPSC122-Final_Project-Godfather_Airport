void checkAirFuel() {
	LinkedList::Node* currentPtr = inAir.getFirst();
	while (currentPtr != nullptr) {
		if (Node->fuel == 0) { 
			LinkedList::Node* tempPtr = currentPtr;
			currentPtr = currentPtr->next;
			crash(tmpPtr);
		}
		else
		{
			currentPtr = currentPtr->next;
		}
	}
}