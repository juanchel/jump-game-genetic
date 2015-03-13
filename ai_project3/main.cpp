#include <iostream>
#include <set>
#include <ctime>
#include <stdio.h>
#include <time.h>
#include "puzzle.h"
using namespace std;


int main (int argc, char* argv[]) {

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int max = atoi(argv[4]);
	int min = atoi(argv[3]);

	bool genetic = true;

	if (argc == 7)
		genetic = false;

	srand (time(NULL));

	int leastFit[4];
	int mostFit[4];

	time_t stop = time(NULL) + atoi(argv[5]);

	cout << "Width:    " << argv[1] << endl;
	cout << "Height:   " << argv[2] << endl;
	cout << "Move Min: " << argv[3] << endl;
	cout << "Move Max: " << argv[4] << endl;
	cout << "Time:     " << argv[5] << endl;
	cout << "Please wait while the algorithm runs" << endl;

	Puzzle population[8] = {Puzzle(width,height,min,max), Puzzle(width,height,min,max), Puzzle(width,height,min,max), Puzzle(width,height,min,max),
		Puzzle(width,height,min,max), Puzzle(width,height,min,max), Puzzle(width,height,min,max), Puzzle(width,height,min,max)};
	for (int i=0; i<8; i++) {
		population[i].randomize();
		population[i].pathSearch();
	}

	int generation = 0;

	while (true) {
		generation++;

		if (generation%100 == 0) {
			if (time(NULL) > stop) {
				break;
			}
		}

		for (int i=0; i<4; i++) {
			int leastFitness = 9999;
			int currentLeast = -1;
			for (int j=0; j<8; j++) {
				if (population[j].solveDist < leastFitness) {
					leastFitness = population[j].solveDist;
					currentLeast = j;
				}
			}
			population[currentLeast].solveDist = 9999;
			leastFit[i] = currentLeast;
		}

		int itr=0;
		for (int i=0; i<8; i++) {
			bool addFit = true;
			for (int j=0; j<4; j++) {
				if (leastFit[j]==i) 
					addFit = false;
			}
			if (addFit) {
				mostFit[itr] = i;
				itr++;
			}
		}

		for (int i=0; i<4; i++) {
			population[leastFit[i]].combine(population[mostFit[i]], (genetic?population[mostFit[(i+1)%4]]:population[mostFit[i]]));
			population[leastFit[i]].pathSearch();
		}
	}

	cout << "Generations: " << generation << endl;
	cout << "Longest Path Found: " << population[mostFit[0]].solveDist << endl;
	cout << "Puzzle: " << endl;
	population[mostFit[0]].printOut();
	population[mostFit[0]].reconstructPath();

}
