// Name:		decRefuel()
// Author:      Erin Bevilacqua
// Purpose:		This function decrements the refueling attribute of all planes in LinkedList atRefuel,
//				and moves planes with refueling value 0 (after the decrement) to LinkedList onGround.
//              Also, it changes fuel to 100...not sure if that was part of this function or what value we actually
//              wanted to change fuel to but that's the function now.
// Inputs:		None
// Outputs:		None
void decRefuel() {
    LinkedList::Node* temp;

    // Traverse through Refuel and decrement refuel time

    temp = atRefuel.getFirst();
    while (temp != nullptr) {
        temp->refueling--;

        // If refueling is 0, add plane to onGround linkList
        // delete from atRefuel linkList
        // and change fuel to 100.
        
        if (temp->refueling == 0) {
            LinkedList::Node* temp2;
            temp2 = temp;
            temp2->fuel = 100;
            temp = temp->next;
            onGround.addElementBack(temp2);
            atRefuel.deleteElement(temp2->id);
        }
        
        // If refueling not at 0, traverse through to next element.
        else {
            temp = temp->next;
        }
    }


}
