#pragma once
#include <iostream>
#include <string>
#include "GameProcess.h"

struct Account {
	char name[256]{};
	int score = 0;
};

int loadFromFile(const char* fn, Account*& accountsList);
void saveToFile(const char* fn, Account* accountsList, int count);
int fsize(const char* fn);
Account createAccount();
void listTops(const char* fn, Account* accs);