void land(plane) {
	numArr += 1
	numPplSafe += plane->people;
	numGCSafe += plane->grandChild;
	cargeSafe += plane->cargo;
	numAirWait+= plane-> waitTime
	totalGCWait += numAirWait * (plane -> grandChild);
	inAir.deleteElement(plane -> id);
}
