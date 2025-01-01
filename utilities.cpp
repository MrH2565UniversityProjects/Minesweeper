#include <iostream>
#include <windows.h>
#include "utilities.h"
using namespace std;
void HideCursor()
{
    cout << "\033[?25l";
    cout.flush();
}
void MoveCursorToTopLeft()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hConsole, coord);
}
void ShowCursor()
{
    cout << "\033[?25h";
    cout.flush();
}
void ClearScreen()
{
    system("cls");
}

void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    COORD pos;             
    pos.X = x;  
    pos.Y = y;                                 
    SetConsoleCursorPosition(hConsole, pos);    
}
int GetMaxLineLength(string multilineString) {
/*     stringstream ss(multilineString);
    string line;
    int maxLength = 0;

    while (getline(ss, line)) {
        int lineLength = line.length();
        if (lineLength > maxLength) {
            maxLength = lineLength; 
        }
    } 
    return maxLength;*/
    return 50;  
}