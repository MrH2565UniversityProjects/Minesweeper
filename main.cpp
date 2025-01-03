#include <fstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "colors.h"
#include "utilities.cpp"
#include "leaderboard.cpp"
#include "game.cpp"
#include "menu.cpp"
using namespace std;
bool isRunning = true;
void Run();
bool HandleAction(int button);
int main()
{
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    ClearScreen();
    HideCursor();
    Player player = SignInMenu();
    MainMenu(player);
    return 0;
}

