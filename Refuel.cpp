void refuel(LinkedList::Node* plane) {
	LinkedList::Node* temp = new LinkedList::Node(plane);
	onGround.deleteElement(plane->id);
	atRefuel.addElementBack(temp);
}



// Comment from Erin: doesn't it take 10 time units to refuel, not 20?
