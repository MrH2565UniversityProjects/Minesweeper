#pragma once
#include <string>
using namespace std;
struct GameOptions
{
    string playerName;
    int difficulty;
    int customRows = 0;
    int customCols = 0;
    int customMinesCount = 0;
    int status = 1;
};

GameOptions GameOptionsMenu();
GameOptions CustomGameOptionsMenu(GameOptions gameOptions);
void MainMenu(Player player);