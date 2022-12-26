#include "GameProcess.h"

bool isPossible(int** map, int ship, int row, int col, int direct) {
	if (direct == 1) {
		if (row + 4 - ship >= 10)
			return false;

		for (int i = 0; i <= 4 - ship; i++)
			for (int drow = -1; drow <= 1; drow++)
				for (int dcol = -1; dcol <= 1; dcol++) {
					if (row + drow + i >= 0 && row + drow + i < 10 && col + dcol >= 0 && col + dcol < 10 && map[row + i + drow][col + dcol])
						return false;
				}
	}
	else {
		if (col + 4 - ship >= 10)
			return false;

		for (int i = 0; i <= 4 - ship; i++) {
			for (int drow = -1; drow <= 1; drow++) {
				for (int dcol = -1; dcol <= 1; dcol++) {
					if (row + drow >= 0 && row + drow < 10 && col + dcol + i >= 0 && col + dcol + i < 10 && map[row + drow][col + i + dcol])
						return false;
				}
			}
		}
	}

	return true;
}

int** genMap() {
	int** map = new int* [10];

	for (int i = 0; i < 10; i++)
		map[i] = new int[10]{};

	return map;
}

void placeShip(int** map, int ship, int row, int col, int direct) {
	if (direct == 1)
		for (int i = 0; i < 5 - ship; i++)
			map[row + i][col] = 1;
	else
		for (int i = 0; i < 5 - ship; i++)
			map[row][col + i] = 1;
}

void playerPositions(int** map) {
	int choice, count = 10, direct, row, col;
	int ship[4] = { 1, 2, 3, 4 };
	std::cout << "Now you have to place your ships. " << std::endl;

	while (count) {
		printMap(map);

		std::cout << "\t1. Battleship - " << ship[0] << " left. " << std::endl
			<< "\t2. Cruiser - " << ship[1] << " left. " << std::endl
			<< "\t3. Destroyer - " << ship[2] << " left. " << std::endl
			<< "\t4. Submarine - " << ship[3] << " left. " << std::endl;

		//Choose a ship
		do {
			std::cout << "Choose a ship: ";
			std::cin >> choice;

			if (choice < 1 || choice > 4)
				std::cout << "Enter a correct number. " << std::endl;
			else if (!ship[choice - 1])
				std::cout << "None of this type of ships left. " << std::endl;
		} while (choice < 1 || choice > 4 || !ship[choice - 1]);

		//Choose a started point
		do {
			std::cout << "Enter a row and a col to place the started point of the ship respectively (1 - 10): ";
			std::cin >> row >> col;

			if (row > 10 || row < 1)
				std::cout << "Enter the correct row. " << std::endl;
			if (col > 10 || col < 1)
				std::cout << "Enter the correct col. " << std::endl;
		} while (row > 10 || row < 1 || col > 10 || col < 1);
		row--; col--;

		//Choose a direction
		if (choice != 4) {
			do {
				std::cout << "1. Vertical " << std::endl
					<< "2. Horizontal " << std::endl
					<< "0. Choose a ship again" << std::endl;

				std::cout << "Choose a direction: ";
				std::cin >> direct;

				if (direct < 0 || direct > 2)
					std::cout << "Error. Choose a direction again. " << std::endl;
			} while (direct < 0 || direct > 2);


		}
		else {
			direct = 1;
		}

		if (!direct)
			continue;

		if (!isPossible(map, choice, row, col, direct)) {
			std::cout << "It is not possible to place ship in this place. " << std::endl;
			continue;
		}

		placeShip(map, choice, row, col, direct);
		ship[choice - 1]--;
		count--;
	}

	printMap(map);

	std::cout << "Congratulation! All ship are placed. " << std::endl;
}

void computerPositions(int** map) {
	int direct, choice;
	std::vector<int> freeRows{}, freeCols{};

	// Placing battleship
	direct = rand() % 2 + 1; // 1 - vert, 2 - horiz
	for (int row = 0; row < (direct == 1 ? 7 : 10); row++) {
		for (int col = 0; col < (direct == 2 ? 7 : 10); col++) {
			if (isPossible(map, 1, row, col, direct)) {
				freeRows.push_back(row);
				freeCols.push_back(col);
			}
		}
	}

	choice = rand() % freeRows.size();
	placeShip(map, 1, freeRows[choice], freeCols[choice], direct);

	freeRows.clear(); freeCols.clear();

	// Placing cruisers

	for (int i = 0; i < 2; i++) {
		direct = rand() % 2 + 1; // 1 - vert, 2 - horiz
		for (int row = 0; row < (direct == 1 ? 8 : 10); row++) {
			for (int col = 0; col < (direct == 2 ? 8 : 10); col++) {
				if (isPossible(map, 2, row, col, direct)) {
					freeRows.push_back(row);
					freeCols.push_back(col);
				}
			}
		}

		choice = rand() % freeRows.size();
		placeShip(map, 2, freeRows[choice], freeCols[choice], direct);

		freeRows.clear(); freeCols.clear();
	}

	// Placing destroyers

	for (int i = 0; i < 3; i++) {
		direct = rand() % 2 + 1; // 1 - vert, 2 - horiz
		for (int row = 0; row < (direct == 1 ? 9 : 10); row++) {
			for (int col = 0; col < (direct == 2 ? 9 : 10); col++) {
				if (isPossible(map, 3, row, col, direct)) {
					freeRows.push_back(row);
					freeCols.push_back(col);
				}
			}
		}

		choice = rand() % freeRows.size();
		placeShip(map, 3, freeRows[choice], freeCols[choice], direct);

		freeRows.clear(); freeCols.clear();
	}

	// Placing submarines

	for (int i = 0; i < 4; i++) {
		direct = 1;

		for (int row = 0; row < 10; row++) {
			for (int col = 0; col < 10; col++) {
				if (isPossible(map, 4, row, col, 1)) {
					freeRows.push_back(row);
					freeCols.push_back(col);
				}
			}
		}

		choice = rand() % freeRows.size();
		placeShip(map, 4, freeRows[choice], freeCols[choice], direct);

		freeRows.clear(); freeCols.clear();
	}
}

bool playerShot(int** map) {
	int x, y;

	do {
		std::cout << "Enter the row and column positions to shoot respectively (1-10): ";
		std::cin >> x >> y;
		x--; y--;

		if (x < 0 || x > 9 || y < 0 || y > 9)
			std::cout << "Error. Choose positions again. " << std::endl;
		else if (map[x][y] >= 2)
			std::cout << "Error. Choose a nonshot position again. " << std::endl;
	} while (x < 0 || x > 9 || y < 0 || y > 9 || map[x][y] >= 2);

	if (map[x][y] == 1) {
		map[x][y] = 2; //shot
		return true;
	}

	map[x][y] = 3; //missed
	return false;
}

int checkWinner(int** mapPlayer, int** mapComputer) {
	int count = 0;

	//player wins
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (mapComputer[i][j] == 2)
				count++;

	if (count == 20)
		return 1;

	count = 0;

	//computer wins
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (mapPlayer[i][j] == 2)
				count++;

	if (count == 20)
		return 2;

	//game still in process
	return 0;
}

void printMap(int** map) {
	std::cout << "          Player   " << std::endl;
	std::cout << "  +-------------------+" << std::endl;

	for (int row = 0; row < 10; row++) {
		std::cout << (row >= 9 ? "" : " ") << row + 1 << "|";

		for (int col = 0; col < 10; col++)
			if (!map[row][col])
				std::cout << " " << (col < 9 ? " " : "");
			else if (map[row][col] == 1)
				std::cout << char(254) << (col < 9 ? " " : "");
			else if (map[row][col] == 2)
				std::cout << "X" << (col < 9 ? " " : "");
			else
				std::cout << "*" << (col < 9 ? " " : "");

		std::cout << "|" << std::endl;
	}
	std::cout << "  +-------------------+" << std::endl << "   ";

	for (int i = 1; i <= 10; i++)
		std::cout << i << " ";
	std::cout << std::endl << std::endl;
}

void printMap(int** mapPlayer, int** mapComputer, bool visible) {
	std::cout << "         Player 1                Player 2      " << std::endl;
	std::cout << "  +-------------------+   +-------------------+" << std::endl;

	for (int row = 0; row < 10; row++) {
		std::cout << (row >= 9 ? "" : " ") << row + 1 << "|";

		for (int col = 0; col < 10; col++)
			if (!mapPlayer[row][col])
				std::cout << " " << (col < 9 ? " " : "");
			else if (mapPlayer[row][col] == 1)
				std::cout << char(254) << (col < 9 ? " " : "");
			else if (mapPlayer[row][col] == 2)
				std::cout << "X" << (col < 9 ? " " : "");
			else
				std::cout << "*" << (col < 9 ? " " : "");

		std::cout << "| " << (row >= 9 ? "" : " ") << row + 1 << "|";

		if (visible)
			for (int col = 0; col < 10; col++)
				if (!mapComputer[row][col])
					std::cout << " " << (col < 9 ? " " : "");
				else if (mapComputer[row][col] == 1)
					std::cout << char(254) << (col < 9 ? " " : "");
				else if (mapComputer[row][col] == 2)
					std::cout << "X" << (col < 9 ? " " : "");
				else
					std::cout << "*" << (col < 9 ? " " : "");
		else 
			for (int col = 0; col < 10; col++)
				if (mapComputer[row][col] == 2)
					std::cout << "X" << (col < 9 ? " " : "");
				else if (mapComputer[row][col] == 3)
					std::cout << "*" << (col < 9 ? " " : "");
				else
					std::cout << " " << (col < 9 ? " " : "");

		std::cout << "|" << std::endl;
	}

	std::cout << "  +-------------------+   +-------------------+" << std::endl << "   ";

	for (int i = 1; i <= 10; i++)
		std::cout << i << " ";
	std::cout << "   ";
	for (int i = 1; i <= 10; i++)
		std::cout << i << " ";
	std::cout << std::endl << std::endl;
}