void land(plane) {
	numArr += 1
	numPplSafe += plane->people;
	numGCSafe += plane->grandChild;
	cargeSafe += plane->cargo;

	inAir.deleteElement(plane -> id);
}