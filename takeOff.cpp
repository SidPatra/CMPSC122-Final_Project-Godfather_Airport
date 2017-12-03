void takeOff(plane) {
	numDep += 1;
	numLandWait += plane->waitTime
	totalGCWait += numLandWait * (plane->grandChild);
	onGround.deleteElement(plane->id);
}
