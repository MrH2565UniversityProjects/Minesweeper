#pragma once
void HideCursor();
void ShowCursor();
void ClearScreen();
void Gotoxy(int x, int y);
void MoveCursorToTopLeft();
int GetMaxLineLength(string multilineString);