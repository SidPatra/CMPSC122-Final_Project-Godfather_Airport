void refuel(LinkedList::Node* plane) {
	LinkedList::Node* temp = new LinkedList::Node();
	temp->id = plane->id;
	temp->action = plane->action;
	temp->refueling = 20;
	temp->cargo = plane->cargo;
	temp->waitTime = plane->waitTime;
	temp->fuelCap = plane->fuelCap;
	temp->grandChild = plane->grandChild;
	temp->next = nullptr;
	temp->prev = nullptr;
	onGround.deleteElement(plane->id);
	atRefuel.addElementBack(temp);
}



// Comment from Erin: doesn't it take 10 time units to refuel, not 20?
