void takeOff(plane) {
	numDep += 1;
	totalTimeWaited += plane->waitTime
	totalGCWait += totalTimeWaited * (plane->grandChild);
	onGround.deleteElement(plane->id);
}
