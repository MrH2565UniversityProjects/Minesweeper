#include <iostream>
#include <windows.h>
#include <conio.h>
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

void Gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    COORD pos;             
    pos.X = x;  
    pos.Y = y;                                 
    SetConsoleCursorPosition(hConsole, pos);    
}
int GetMaxLineLength(string multilineString) {
/*  stringstream ss(multilineString);
    string line;
    int maxLength = 0;

    while (getline(ss, line)) {
        int lineLength = line.length();
        if (lineLength > maxLength) {
            maxLength = lineLength; 
        }
    } 
    return maxLength; */
    return 50;
}
bool IsDigit(char ch){
    return ('0' <= ch) && ('9' >= ch);
}
string GetNumberInput(int maxLength, int cursorX, int cursorY)
{
    string input;
    char ch;

    while (true)
    {
        ch = getch();
        if(!(IsDigit(ch) || ch == '\r' || ch == '\b' || ch == 27)) continue;

        if (ch == '\r')
        {
            break; 
        }
        else if (ch == '\b') 
        {
            if (!input.empty())
            {
                input.pop_back();
                Gotoxy(cursorX + input.length(), cursorY); 
                cout << " \b";
            }
        }
        else if(ch == 27){
            return "";
        }
        else if (input.length() < maxLength)
        {
            input.push_back(ch);
            cout << ch; 
        }
    }

    return input; 
}
string GetInput(int maxLength, int cursorX, int cursorY)
{
    string input;
    char ch;

    while (true)
    {
        ch = getch();

        if (ch == '\r')
        {
            break; 
        }
        else if (ch == '\b') 
        {
            if (!input.empty())
            {
                input.pop_back();
                Gotoxy(cursorX + input.length(), cursorY); 
                cout << " \b";
            }
        }
        else if(ch == 27){
            return "";
        }
        else if (input.length() < maxLength)
        {
            input.push_back(ch);
            cout << ch; 
        }
    }

    return input; 
}

string IntToString(int number) {
    string result = "";   
    if (number == 0) {
        result = "0";
    } else {
        while (number > 0) {
            result = static_cast<char>('0' + (number % 10)) + result;
            number /= 10; 
        }
    }
    return result;
}