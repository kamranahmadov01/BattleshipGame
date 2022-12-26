#include "ComputerAI.h"

inline void shipStatsInit(ShipDamaging& ship) {
	ship.startRow = -1;
	ship.startCol = -1;

	ship.endRow = -1;
	ship.endCol = -1;

	ship.direct = 0;

	ship.finished = true;
	ship.reversed = false;
}

void fillAdjacent(int** map, ShipDamaging ship) {
	if (ship.startRow == -1 && ship.startCol == -1)
		return;

	if (ship.endRow == -1 && ship.endCol == -1) {
		ship.endRow = ship.startRow;
		ship.endCol = ship.startCol;
	}

	int minRow, maxRow, minCol, maxCol;

	if (ship.startRow < ship.endRow) {
		minRow = ship.startRow;
		maxRow = ship.endRow;
	}
	else {
		minRow = ship.endRow;
		maxRow = ship.startRow;
	}

	if (ship.startCol < ship.endCol) {
		minCol = ship.startCol;
		maxCol = ship.endCol;
	}
	else {
		minCol = ship.endCol;
		maxCol = ship.startCol;
	}

	for (int row = minRow; row <= maxRow; row++)
		for (int col = minCol; col <= maxCol; col++)
			for (int drow = -1; drow <= 1; drow++)
				for (int dcol = -1; dcol <= 1; dcol++)
					if (row + drow >= 0 && row + drow < 10 && col + dcol >= 0 && col + dcol < 10 && !map[row + drow][col + dcol])
						map[row + drow][col + dcol] = 3;
}

int findDirect(int** map, ShipDamaging& ship) {
	switch (ship.direct) {
	case 0:
		if (ship.startCol + 1 < 10 && map[ship.startRow][ship.startCol + 1] <= 1) {
			if (map[ship.startRow][ship.startCol + 1]) {
				map[ship.startRow][ship.startCol + 1] = 2;

				ship.endRow = ship.startRow;
				ship.endCol = ship.startCol + 1;
				return 0;
			}

			map[ship.startRow][ship.startCol + 1] = 3;
			ship.direct++;
			return -1;
		}
	case 1:
		if (ship.startRow - 1 >= 0 && map[ship.startRow - 1][ship.startCol] <= 1) {
			if (map[ship.startRow - 1][ship.startCol]) {
				map[ship.startRow - 1][ship.startCol] = 2;
				ship.endRow = ship.startRow - 1;
				ship.endCol = ship.startCol;
				return 1;
			}
			
			map[ship.startRow - 1][ship.startCol] = 3;
			ship.direct++;
			return -1;
		}
	case 2:
		if (ship.startCol - 1 >= 0 && map[ship.startRow][ship.startCol - 1] <= 1) {
			if (map[ship.startRow][ship.startCol - 1]) {
				map[ship.startRow][ship.startCol - 1] = 2;
				ship.endRow = ship.startRow;
				ship.endCol = ship.startCol - 1;
				return 2;
			}

			map[ship.startRow][ship.startCol - 1] = 3;
			ship.direct++;
			return -1;
		}
	case 3:
		if (ship.startRow + 1 < 10 && map[ship.startRow + 1][ship.startCol] <= 1) {
			if (map[ship.startRow + 1][ship.startCol]) {
				map[ship.startRow + 1][ship.startCol] = 2;
				ship.endRow = ship.startRow + 1;
				ship.endCol = ship.startCol;
				return 3;
			}

			map[ship.startRow + 1][ship.startCol] = 3;

			ship.endRow = ship.startRow;
			ship.endCol = ship.startCol;
			ship.finished = true;
			return -1;
		}
		break;
	default:
		break;
	}

	ship.endRow = ship.startRow;
	ship.endCol = ship.startCol;
	ship.finished = true;
	return -2;
}

int attackWithDirection(int** map, ShipDamaging& ship) {
	switch (ship.direct) {
	case 0:
		if (ship.endCol + 1 < 10 && map[ship.endRow][ship.endCol + 1] <= 1) {
			if (map[ship.endRow][ship.endCol + 1]) {
				map[ship.endRow][++ship.endCol] = 2;
				return 1;
			}

			map[ship.endRow][ship.endCol + 1] = 3;
			ship.direct = (ship.direct + 2) % 4;
			return 0;
		}
		break;
	case 1:
		if (ship.endRow - 1 >= 0 && map[ship.endRow - 1][ship.endCol] <= 1) {
			if (map[ship.endRow - 1][ship.endCol]) {
				map[--ship.endRow][ship.endCol] = 2;
				return 1;
			}

			map[ship.endRow - 1][ship.endCol] = 3;
			ship.direct = (ship.direct + 2) % 4;
			return 0;
		}
		break;
	case 2:
		if (ship.endCol - 1 >= 0 && map[ship.endRow][ship.endCol - 1] <= 1) {
			if (map[ship.endRow][ship.endCol - 1]) {
				map[ship.endRow][--ship.endCol] = 2;
				return 1;
			}

			map[ship.endRow][ship.endCol - 1] = 3;
			ship.direct = (ship.direct + 2) % 4;
			return 0;
		}
		break;
	case 3:
		if (ship.endRow + 1 < 10 && map[ship.endRow + 1][ship.endCol] <= 1) {
			if (map[ship.endRow + 1][ship.endCol]) {
				map[++ship.endRow][ship.endCol] = 2;
				return 1;
			}

			map[ship.endRow + 1][ship.endCol] = 3;
			ship.direct = (ship.direct + 2) % 4;
			return 0;
		}
		break;
	default:
		break;
	}

	ship.direct = (ship.direct + 2) % 4;
	ship.reversed = true;

	return -1;
}

int attackWithDirectionReversed(int** map, ShipDamaging& ship) {
	switch (ship.direct) {
	case 0:
		if (ship.startCol + 1 < 10 && map[ship.startRow][ship.startCol + 1] <= 1) {
			if (map[ship.startRow][ship.startCol + 1]) {
				map[ship.startRow][++ship.startCol] = 2;
				return 1;
			}

			map[ship.startRow][ship.startCol + 1] = 3;
			ship.finished = true;
			return 0;
		}
		break;
	case 1:
		if (ship.startRow - 1 >= 0 && map[ship.startRow - 1][ship.startCol] <= 1) {
			if (map[ship.startRow - 1][ship.startCol]) {
				map[--ship.startRow][ship.startCol] = 2;
				return 1;
			}

			map[ship.startRow - 1][ship.startCol] = 3;
			ship.finished = true;
			return 0;
		}
		break;
	case 2:
		if (ship.startCol - 1 >= 0 && map[ship.startRow][ship.startCol - 1] <= 1) {
			if (map[ship.startRow][ship.startCol - 1]) {
				map[ship.startRow][--ship.startCol] = 2;
				return 1;
			}

			map[ship.startRow][ship.startCol - 1] = 3;
			ship.finished = true;
			return 0;
		}
		break;
	case 3:
		if (ship.startRow + 1 < 10 && map[ship.startRow + 1][ship.startCol] <= 1) {
			if (map[ship.startRow + 1][ship.startCol]) {
				map[++ship.startRow][ship.startCol] = 2;
				return 1;
			}

			map[ship.startRow + 1][ship.startCol] = 3;
			ship.finished = true;
			return 0;
		}
		break;
	default:
		break;
	}

	ship.finished = true;
	return -1;
}

bool computerShot(int** map, int difficulty, ShipDamaging& shipStats) {
	if (difficulty == 1) {
		int count = 0;

		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (map[i][j] <= 1)
					count++;

		int shotPoint = rand() % count;
		count = -1;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (map[i][j] <= 1)
					count++;

				if (shotPoint == count) {

					if (map[i][j]) {
						map[i][j] = 2;
						shipStats.startRow = i;
						shipStats.startCol = j;

						shipStats.finished = false;
						return true;
					}

					map[i][j] = 3;
					return false;
				}
			}
		}
	}

	if (shipStats.finished) {
		fillAdjacent(map, shipStats);
		shipStatsInit(shipStats);
		return computerShot(map, 1, shipStats);
	}

	if (shipStats.endRow == -1 && shipStats.endCol == -1) {
		int direction = findDirect(map, shipStats);

		if (direction == -2)
			return computerShot(map, 2, shipStats);
		if (direction == -1)
			return false;

		shipStats.direct = direction;
		return true;
	}

	if (!shipStats.reversed) {
		int result = attackWithDirection(map, shipStats);
		if (!result)
			shipStats.reversed = true;

		if (result > -1)
			return result;
	}

	int result = attackWithDirectionReversed(map, shipStats);
	if (result > -1)
		return result;
	return computerShot(map, 2, shipStats);
}