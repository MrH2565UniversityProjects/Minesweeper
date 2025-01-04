#pragma once
#include <string>

using namespace std;
void HideCursor();
void ShowCursor();
void ClearScreen();
void Gotoxy(int x, int y);
void MoveCursorToTopLeft();
void PrintC(string text, int &y);
void PrintC(string text, int &y,int length);
int GetMaxLineLength(string multilineString);
string GetNumberInput(int maxLength, int cursorX, int cursorY);
string GetInput(int maxLength, int cursorX, int cursorY);
string IntToString(int number);