#include <iostream>
#include <Windows.h>
#include "StartMenu.h"
#include "GameProcess.h"
#include "ComputerAI.h"
#include "TopList.h"

int main() {
	welcomeMessage();
	srand(time(NULL));
	int game, mode;
	const char fn[] = "top.dat";

	Account temp;
	Account* accountsList{};
	do {
		do {
			std::cout << "\t1. New game" << std::endl
				<< "\t2. Top score list" << std::endl
				<< "\t0. Exit" << std::endl;

			std::cout << "Choose a mode: ";
			std::cin >> mode;
			if (mode > 2 || mode < 0)
				std::cout << "Enter a correct value. " << std::endl;
	
			switch (mode) {
			case 1:
				break;
			case 2:
				listTops(fn, accountsList);
				break;
			case 0:
				return 0;
			default:
				break;
			}
		} while (mode != 1);

		ShipDamaging damage1{}, damage2{};
		int winner;
		int** firstPlayerMap = genMap(), ** secondPlayerMap = genMap();
		bool firstPlayerShotSuccess = false, secondPlayerShotSuccess = rand() % 2;
		bool realPlayer = playerOrComputer(), shipsByPlayer = false;
		int diff = setDifficulty();
		int playerPoints = 0;

		if (realPlayer) {
			shipsByPlayer = shipsPlacedByPlayer();
			temp = createAccount();
		}

		if (shipsByPlayer)
			playerPositions(firstPlayerMap);
		else
			computerPositions(firstPlayerMap);
		computerPositions(secondPlayerMap);

		gameStartMessage();
		system("PAUSE");

		do {
			if (!secondPlayerShotSuccess) {
				system("CLS");
				if (realPlayer)
					std::cout << "Score: " << temp.score << std::endl;					

				std::cout << "First player shoots! " << std::endl;
				printMap(firstPlayerMap, secondPlayerMap, !realPlayer);
				firstPlayerShotSuccess = (realPlayer ? playerShot(secondPlayerMap) : computerShot(secondPlayerMap, diff, damage1));

				Sleep(250);
				if (firstPlayerShotSuccess)
					temp.score += rand() % 51 + (diff == 2 ? 75 : 50);
			}

			if (!firstPlayerShotSuccess) {
				system("CLS");
				if (realPlayer)
					std::cout << "Score: " << temp.score << std::endl;

				std::cout << "Second player shoots! " << std::endl;
				printMap(firstPlayerMap, secondPlayerMap, !realPlayer);
				secondPlayerShotSuccess = computerShot(firstPlayerMap, diff, damage2);

				Sleep(250);

				if (secondPlayerShotSuccess)
					temp.score -= rand() % (diff == 1 ? 51 : 26);

				if (temp.score < 0)
					temp.score = 0;
			}
		} while (!(winner = checkWinner(firstPlayerMap, secondPlayerMap)));

		if (realPlayer)
			std::cout << "Score: " << temp.score << std::endl;

		system("CLS");
		printMap(firstPlayerMap, secondPlayerMap, !realPlayer);

		if (winner == 1) {
			std::cout << "First player won! " << std::endl;

			if (realPlayer) {
				std::cout << "Your score is " << temp.score << std::endl;
				int count = loadFromFile(fn, accountsList);

				bool added = false;

				for (int i = 0; i < count; i++) {
					if (!strcmp(accountsList[i].name, temp.name)) {
						if (accountsList[i].score < temp.score)
							accountsList[i] = temp;

						added = true;
						break;
					}
				}

				if (!added)
					accountsList[count++] = temp;

				saveToFile(fn, accountsList, count);
			}
		}
		else
			std::cout << "Second player won!" << std::endl;

		do {
			std::cout << "Do you want to continue (1/0)? ";
			std::cin >> game;

			if (game > 1 || game < 0)
				std::cout << "Enter a correct number: " << std::endl;
		} while (game > 1 || game < 0);

		system("CLS");
	} while (game);

	return 0;
}