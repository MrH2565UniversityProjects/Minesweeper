#include <fstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "colors.h"
#include "leaderboard.h"
#include "player.cpp"
using namespace std;
void Leaderboard()
{
    Leaderboard("scoreBoard.txt");
}
void Leaderboard(string LeaderboardFileName)
{
    system("cls");
    string bestPlayersHeader = R"(
 _______  _______  _______  _______    _______  ___      _______  __   __  _______  ______    _______
|  _    ||       ||       ||       |  |       ||   |    |   _   ||  | |  ||       ||    _ |  |       |
| |_|   ||    ___||  _____||_     _|  |    _  ||   |    |  |_|  ||  |_|  ||    ___||   | ||  |  _____|
|       ||   |___ | |_____   |   |    |   |_| ||   |    |       ||       ||   |___ |   |_||_ | |_____
|  _   | |    ___||_____  |  |   |    |    ___||   |___ |       ||_     _||    ___||    __  ||_____  |
| |_|   ||   |___  _____| |  |   |    |   |    |       ||   _   |  |   |  |   |___ |   |  | | _____| |
|_______||_______||_______|  |___|    |___|    |_______||__| |__|  |___|  |_______||___|  |_||_______|)";
    fstream dataFile;
    dataFile.open(LeaderboardFileName, ios::in);
    Player players[10];
    int counter = 0;

    while (dataFile >> players[counter].name >> players[counter].score)
    {
        counter++;
    }
    dataFile.close();

    string ranking[10] = {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th"};
    string whitespace = "                 ";
    cout << CYAN << bestPlayersHeader << RESET << endl
         << endl;
    cout << CYAN << whitespace << "╒══════╤════════════════════════════════════════════════════╤═══════╕" << RESET << endl;
    cout << CYAN << whitespace << "│ Rank │ Player                                             │ Score │" << RESET << endl;
    cout << CYAN << whitespace << "╞══════╪════════════════════════════════════════════════════╪═══════╡" << RESET << endl;

    for (int i = 0; i < counter; i++)
    {
        cout << CYAN << whitespace << "│ " << setw(4) << left << ranking[i] << " │ " << setw(50) << left << players[i].name << " │ " << setw(5) << right << players[i].score << " │" << RESET << endl;
    }

    cout << CYAN << whitespace << "╘══════╧════════════════════════════════════════════════════╧═══════╛" << RESET << endl << endl;
    cout << YELLOW << whitespace << "             Press any key to back to main menu..." << RESET << endl;
    char choice = getch();
};