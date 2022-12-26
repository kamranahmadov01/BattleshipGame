#include "StartMenu.h"

void welcomeMessage() {
	std::cout << "Welcome to Battleship game! Hope you'll enjoy this game. " << std::endl << std::endl;
}

int setDifficulty() {
	int difficulty;
	std::cout << "Now you have to choose the difficulty from given below. " << std::endl;

	do {
		std::cout << "\t1. Easy" << std::endl
			<< "\t2. Hard" << std::endl;
		std::cout << "Select difficulty: ";
		std::cin >> difficulty;

		if (difficulty < 1 || difficulty > 2)
			std::cout << "Error. Try to select the difficulty again. " << std::endl;
	} while (difficulty < 1 || difficulty > 2);

	return difficulty;
}

bool setVisibility() {
	int result;

	std::cout << "Do you want to see enemy's ships (for debugging, 1/0)? ";
	std::cin >> result;

	return (bool)result;
}

bool playerOrComputer() {
	int result;

	do {
		std::cout << "\t1. Player vs Computer" << std::endl
			<< "\t2. Computer vs Computer" << std::endl;

		std::cout << "Choose a mode: ";
		std::cin >> result;
	} while (result > 2 || result < 1);

	return result == 1;
}

bool shipsPlacedByPlayer() {
	int result;
	
	do {
		std::cout << "Do you want to place all ships yourself (1/0)? ";
		std::cin >> result;

		if (result > 1 || result < 0)
			std::cout << "Error. Enter a correct value. " << std::endl;
	} while (result > 1 || result < 0) ;

	return (bool)result;
}

void gameStartMessage() {
	std::cout << "The game starts right now. Good luck! " << std::endl;
}