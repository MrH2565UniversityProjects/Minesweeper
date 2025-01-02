#include <fstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "colors.h"
#include "leaderboard.h"
#include "player.h"
#include "form.h"
#include "utilities.h"
using namespace std;
void Leaderboard()
{
    Leaderboard("scoreBoard.txt");
}
void Leaderboard(string LeaderboardFileName)
{
    system("cls");
    int x = 9;
    int y = 16;
    string ranking[10] = {"1st", "2nd", "3rd", "4th", "5th","6th","7th","8th","9th","10th"};
    fstream dataFile;
    dataFile.open(LeaderboardFileName, ios::in);
    Player players[10];
    int counter = 0;

    while (dataFile >> players[counter].name >> players[counter].score)
    {
        counter++;
        if (counter == 10)
        {
            break;
        }
    }
    dataFile.close();
    ShowForm();
    SetFooter("Leaderboard");
    Gotoxy(x, y);
    cout << RESET << "╒══════╤═════════════════════════════════════════════════════════════╤═══════╕" << RESET;
    y++;
    Gotoxy(x, y);
    cout << RESET << "│ Rank │ Player                                                      │ Score │" << RESET;
    y++;
    Gotoxy(x, y);
    cout << RESET << "╞══════╪═════════════════════════════════════════════════════════════╪═══════╡" << RESET;
    for (int i = 0; i < counter; i++)
    {
        y++;
        Gotoxy(x, y);
        string color;
        if(i < 3)
        color = BLUE;
        else if(i > 5)
        color = RESET;
        else
        color = CYAN;
        cout << RESET << "│ " << color << setw(4) << left << ranking[i] << RESET << " │ " << color << setw(59) << left << players[i].name <<RESET << " │ "<< color << setw(5) << right << players[i].score << RESET << " │" << endl;
    }
    y++;
    Gotoxy(x, y);
    cout << RESET << "╘══════╧═════════════════════════════════════════════════════════════╧═══════╛" << RESET << endl
         << endl;
    Label EndMessage = {
        "Press any key to back to main menu...",
        YELLOW
    };
    y++;
    ShowLabel(EndMessage,y);
    char choice = getch();
    ClearScreen();
};
