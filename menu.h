#pragma once
#include <string>
using namespace std;
struct GameOptions
{
    std::string playerName;
    int difficulty;
    int customRows = 0;
    int customCols = 0;
    int customMinesCount = 0;
};

void MainMenu();
GameOptions GameOptionsMenu();
GameOptions CustomGameOptionsMenu(GameOptions gameOptions);
