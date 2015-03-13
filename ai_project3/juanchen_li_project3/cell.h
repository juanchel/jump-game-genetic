#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <stdio.h>
using namespace std;

class Cell {
public:
	int xCoor, yCoor;
	int minPossVal;
	int maxPossVal;
	int val;
	int distFromStart;

	Cell(): val(1), distFromStart(-1) {}
	
	void setPossVal (int n, int x) {
		minPossVal=n;
		maxPossVal=x;
	}

	void setCoor (int x, int y) {
		xCoor = x;
		yCoor = y;
	}

	void randomize () {
		val = minPossVal + rand()%(maxPossVal - minPossVal + 1);
	}
};

#endif
