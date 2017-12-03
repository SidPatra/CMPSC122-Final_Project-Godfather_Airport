// Name:		incWaitTime()
// Author:      Erin Bevilacqua
// Purpose:		This function increments waitTime attribute of every plane in every list
// Inputs:		None
// Outputs:		None
void incWaitTime() {
    LinkedList::Node* temp;

    // Traverse through inAir, onGround, and atRefuel and increment waitTime by one.
    temp = inAir.getFirst;
    while (temp!=nullptr) {
        temp->waitTime++;
        temp = temp->next;
    }
    temp = onGround.getFirst;
    while (temp!=nullptr) {
        temp->waitTime++;
        temp = temp->next;
    }
    temp = atRefuel.getFirst;
    while (temp!=nullptr) {
        temp->waitTime++;
        temp = temp->next;
    }
}
