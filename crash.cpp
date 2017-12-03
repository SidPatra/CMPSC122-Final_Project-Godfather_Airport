// Name:		crash()
// Author:      Cole Cugini
// Purpose:		crash takes the plane who crashes and updates our global data. Also, crash deletes the plane
//              from the list of planes that exist.
//
//
// Inputs:		The plane that crashed
// Outputs:		None
void crash(LinkedList::Node* plane){

    numCrashes++;			// Number of planes that have crashed
    numPplDead+=plane->people;			// Number of people who have died
    numGCDead+=plane->grandChild;			// Number of grandchildren who have died
    cargoDead-=plane->cargo;			// Value of cargo that crashed
    LinkedList.deleteElement(plane->id);

}