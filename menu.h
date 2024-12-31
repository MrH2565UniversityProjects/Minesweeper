#ifndef MENU_H
#define MENU_H
#include <string>
using namespace std;
struct GameOptions
{
    std::string playerName;
    int difficulty;
};

void MainMenu();
GameOptions GameOptionsMenu();

#endif