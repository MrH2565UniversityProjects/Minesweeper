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

string GetDefaultFileName(){
    return "scoreBoard.txt"; 
}
void Leaderboard()
{
    Leaderboard(GetDefaultFileName());
}
void bubbleSort(Player players[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}

void ReadPlayersFromFile(string Filename, Player players[], int &counter) {
    fstream dataFile;
    dataFile.open(Filename, ios::in);
    if (!dataFile) {
        cerr << "Error opening file!" << endl;
        return;
    }
    while (dataFile >> players[counter].name >> players[counter].score >> players[counter].isWin) {
        counter++;
        if (counter == 10) {
            break;
        }
    }
    dataFile.close();
}

void WritePlayersToFile(string Filename, Player players[], int counter) {
    fstream dataFile;
    dataFile.open(Filename, ios::out);
    if (!dataFile) {
        cerr << "Error writing to file!" << endl;
        return;
    }
    for (int i = 0; i < counter; i++) {
        dataFile << players[i].name << " " << players[i].score << " " <<players[i].isWin << endl;
    }
    dataFile.close();
}
void Leaderboard(string Filename)
{
    system("cls");
    int x = 9;
    int y = 16;
    string ranking[10] = {"1st", "2nd", "3rd", "4th", "5th","6th","7th","8th","9th","10th"};

    int counter = 0;
    Player players[10];
    ReadPlayersFromFile(Filename,players,counter);
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
        if(players[i].isWin)
        color = GREEN;
        else
        color = RED;
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
void UpdateLeaderboard(string Filename,Player player){
    Player players[11];
    int counter = 0;
    ReadPlayersFromFile(Filename,players,counter);
    players[counter] = player;
    counter++;
    bubbleSort(players, counter);
    if (counter > 10) {
        counter = 10;
    }
    WritePlayersToFile(Filename, players, counter);
}
void UpdateLeaderboard(Player player){
    UpdateLeaderboard(GetDefaultFileName(),player);
}
