#pragma once
#include <iostream>
#include <vector>

struct ShipDamaging {
	int startRow = -1, startCol = -1;
	int endRow = -1, endCol = -1;
	
	int direct = 0;

	bool finished = true, reversed = false;
};

int** genMap();
void playerPositions(int** map);
void computerPositions(int** map);
bool playerShot(int** map);
int checkWinner(int** mapPlayer, int** mapComputer);
void printMap(int** map);
void printMap(int** mapPlayer, int** mapComputer, bool visible);