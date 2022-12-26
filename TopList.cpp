#include "TopList.h"

int loadFromFile(const char* fn, Account*& accountsList) {
    int accountsCount = fsize(fn) / sizeof(Account);
    accountsList = new Account[accountsCount + 1];

    FILE* file;
    fopen_s(&file, fn, "rb");

    if (file != nullptr) {
        fread_s(accountsList, sizeof(Account) * accountsCount, sizeof(Account), accountsCount, file);
        fclose(file);
    }

    return accountsCount;
}

void saveToFile(const char* fn, Account* accountsList, int count) {
    FILE* file;
    fopen_s(&file, fn, "wb");

    if (file != nullptr) {
        fwrite(accountsList, sizeof(Account), count, file);
        fclose(file);
    }
}

void listTops(const char* fn, Account* accs) {
    int count = loadFromFile(fn, accs);
    if (!count) {
        std::cout << "No players in the top. " << std::endl << std::endl;
        return;
    }

    bool swapped = true;
    while (swapped) {
        swapped = false;

        for (int i = 0; i < count - 1; i++)
            if (accs[i].score < accs[i + 1].score) {
                std::swap(accs[i], accs[i + 1]);
                swapped = true;
            }
    }

    for (int i = 0; i < count; i++)
        std::cout << "\t\t" << i + 1 << ". " << accs[i].name << " - " << accs[i].score << std::endl;
    std::cout << std::endl;
}

int fsize(const char* fn) {
    int len = 0;
    FILE* file;
    fopen_s(&file, fn, "r");

    if (file != nullptr) {
        fseek(file, 0, SEEK_END);
        len = ftell(file);
        fclose(file);
    }
    return len;
}

Account createAccount() {
    Account acc;

    std::cin.get();
    std::cout << "Enter your name: ";
    std::cin.getline(acc.name, 256);

    return acc;
}