// Name:		  print()
// Author:    Erin Bevilacqua
// Purpose:		This function prints the statistics.
// Inputs:		None
// Outputs:		None



void print() {
    cout << "Average take off wait time: " << ((float) totalTimeWaitedAir)/((float) numDep) << endl;
    cout << "Average landing wait time: " << ((float) totalTimeWaitedGround)/((float) numArr) << endl;
    cout << "Number of crashed planes: " << numCrashes << endl;
    cout << "Number of departed planes: " << numDep << endl;
    cout << "Number of arrived planes: " << numArr << endl;
    cout << "Number of people safe: " << numPplSafe << endl;
    cout << "Number of people killed: " << numPplDead << endl;
    cout << "Number of grandchildren safe: " << numGCSafe << endl;
    cout << "Number of grandchildren killed: " << numGCDead << endl;
    cout << "Average wait time for a grandchild Arriving or Departing: ";
    cout << ((float) totalGCWait)/((float) numGCSafe) << endl;
    cout << "Amount of cargo that landed safely: " << cargoSafe << endl;
    cout << "Amount of destroyed Cargo: " << cargoDead << endl;
    cout << "Amount of time it takes to process a input: " << totalTime << endl;
    
}
