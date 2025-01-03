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

GameOptions GameOptionsMenu();
GameOptions CustomGameOptionsMenu(GameOptions gameOptions);
void MainMenu(Player player);