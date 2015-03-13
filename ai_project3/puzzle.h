#ifndef PUZZLE_H
#define PUZZLE_H

#include <queue>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "cell.h"
using namespace std;

class Puzzle {

public:

	int width, height, moveMin, moveMax;
	int solveDist;
	Cell ** board;

	Puzzle(int w, int h, int n, int x): width(w), height(h), moveMin(n), moveMax(x) {
		
		board = new Cell*[width];
		for (int i=0; i<width; i++) {
			board[i] = new Cell[height];
		}

		for (int i=0; i<width; i++) {
			for (int j=0; j<height; j++) {
				
				int limit=x;

				for (int k=n; k<=x; k++) {
					int count = 0;
					if (i-k < 0)
						count++;
					if (i+k >= width)
						count++;
					if (j-k < 0)
						count++;
					if (j+k >= height)
						count++;
					
					if (count>=3) {
						limit = k-1;
						break;
					}
				}

				board[i][j].setPossVal(n, limit);
				board[i][j].setCoor(i, j);
			}
		}
	}

	~Puzzle () {
		for (int i=0; i<width; i++)
			delete [] board[i];
		delete [] board;
	};

	void randomize () {
		
		for (int i=0; i<width; i++) {
			for (int j=0; j<height; j++) {
				board[i][j].randomize();
			}
		}
	}

	void pathSearch () {
		queue<Cell> searchQueue;
		board[0][0].distFromStart = 0;
		searchQueue.push(board[0][0]);

		while (!searchQueue.empty()) {
			Cell c = searchQueue.front();
			
			solveDist = c.distFromStart;

			if (c.xCoor==width-1 && c.yCoor==height-1) {
				break;
			}

			if (c.xCoor + c.val < width) {
				if (board[c.xCoor+c.val][c.yCoor].distFromStart == -1) {
					board[c.xCoor+c.val][c.yCoor].distFromStart = c.distFromStart+1;
					searchQueue.push(board[c.xCoor+c.val][c.yCoor]);
				}
			}

			if (c.xCoor - c.val >= 0) {
				if (board[c.xCoor-c.val][c.yCoor].distFromStart == -1) {
					board[c.xCoor-c.val][c.yCoor].distFromStart = c.distFromStart+1;
					searchQueue.push(board[c.xCoor-c.val][c.yCoor]);
				}
			}

			if (c.yCoor + c.val < height) {
				if (board[c.xCoor][c.yCoor+c.val].distFromStart == -1) {
					board[c.xCoor][c.yCoor+c.val].distFromStart = c.distFromStart+1;
					searchQueue.push(board[c.xCoor][c.yCoor+c.val]);
				}
			}

			if (c.yCoor - c.val >= 0) {
				if (board[c.xCoor][c.yCoor-c.val].distFromStart == -1) {
					board[c.xCoor][c.yCoor-c.val].distFromStart = c.distFromStart+1;
					searchQueue.push(board[c.xCoor][c.yCoor-c.val]);
				}
			}

			if (searchQueue.size()==1) {
				solveDist = 0;
			}
			searchQueue.pop();
		}
	}

	void combine (Puzzle &a, Puzzle &b) {

		solveDist = 0;
		int rness = rand()%50;

		for (int i=0; i<width; i++) {
			for (int j=0; j<height; j++) {
				board[i][j].distFromStart=-1;
				if (rand()%100<rness) {
					board[i][j].randomize();
				} else if (rand()%2==0) {
					board[i][j].val = a.board[i][j].val;
				} else {
					board[i][j].val = a.board[i][j].val;
				}
			}
		}
	}

	void printOut () {
		
		for (int i=0; i<width; i++) {
			for (int j=0; j<height; j++) {
				cout << setw(3) << board[i][j].val;
			}
			cout << endl;
		}
	}

	void reconstructPath () {
		queue<Cell> searchQueue;

		for (int i=0; i<width; i++) {
			for (int j=0; j<height; j++) {
				board[i][j].distFromStart = -1;
			}
		}

		board[0][0].distFromStart = 0;
		searchQueue.push(board[0][0]);

		string ** paths;
		paths = new string*[width];
		for (int i=0; i<width; i++) {
			paths[i] = new string[height];
		}

		while (!searchQueue.empty()) {
			Cell c = searchQueue.front();
			
			solveDist = c.distFromStart;

			if (c.xCoor==width-1 && c.yCoor==height-1) {
				cout << paths[c.xCoor][c.yCoor] << endl;
				break;
			}

			if (c.xCoor + c.val < width) {
				if (board[c.xCoor+c.val][c.yCoor].distFromStart == -1) {
					board[c.xCoor+c.val][c.yCoor].distFromStart = c.distFromStart+1;
					paths[c.xCoor+c.val][c.yCoor].assign(paths[c.xCoor][c.yCoor]);
					paths[c.xCoor+c.val][c.yCoor].append(" D");
					searchQueue.push(board[c.xCoor+c.val][c.yCoor]);
				}
			}

			if (c.xCoor - c.val >= 0) {
				if (board[c.xCoor-c.val][c.yCoor].distFromStart == -1) {
					board[c.xCoor-c.val][c.yCoor].distFromStart = c.distFromStart+1;
					paths[c.xCoor-c.val][c.yCoor].assign(paths[c.xCoor][c.yCoor]);
					paths[c.xCoor-c.val][c.yCoor].append(" U");
					searchQueue.push(board[c.xCoor-c.val][c.yCoor]);
				}
			}

			if (c.yCoor + c.val < height) {
				if (board[c.xCoor][c.yCoor+c.val].distFromStart == -1) {
					board[c.xCoor][c.yCoor+c.val].distFromStart = c.distFromStart+1;
					paths[c.xCoor][c.yCoor+c.val].assign(paths[c.xCoor][c.yCoor]);
					paths[c.xCoor][c.yCoor+c.val].append(" R");
					searchQueue.push(board[c.xCoor][c.yCoor+c.val]);
				}
			}

			if (c.yCoor - c.val >= 0) {
				if (board[c.xCoor][c.yCoor-c.val].distFromStart == -1) {
					board[c.xCoor][c.yCoor-c.val].distFromStart = c.distFromStart+1;
					paths[c.xCoor][c.yCoor-c.val].assign(paths[c.xCoor][c.yCoor]);
					paths[c.xCoor][c.yCoor-c.val].append(" L");
					searchQueue.push(board[c.xCoor][c.yCoor-c.val]);
				}
			}

			if (searchQueue.size()==1) {
				solveDist = 0;
			}
			searchQueue.pop();
		}
	}
};

#endif
