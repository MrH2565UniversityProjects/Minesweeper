#include <fstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include "game.h"
#include "colors.h"
#include "menu.h"
#include "utilities.h"
using namespace std;
struct Cell
{
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int adjacentMines;
};
struct GameProperties
{
    int rows;
    int cols;
    int TotalMineCount;
    Cell grid[20][20];
};
GameProperties properties;
GameOptions options;
bool AreCellsAdjacent(int row1, int col1, int row2, int col2)
{
    for (int delta_row = -1; delta_row <= 1; delta_row++)
    {
        for (int delta_col = -1; delta_col <= 1; delta_col++)
        {
            int new_row = row1 + delta_row, new_col = col1 + delta_col;
            if (new_row == row2 && new_col == col2)
            {
                return true;
            }
        }
    }
    return false;
}
void GenerateMines(int totalMines, int user_row, int user_col)
{
    srand(time(0));
    for (int i = 0; i < totalMines;)
    {
        int row = rand() % properties.rows;
        int col = rand() % properties.cols;

        if (!properties.grid[row][col].isMine && !(AreCellsAdjacent(user_row, user_col, row, col)))
        {
            properties.grid[row][col].isMine = true;
            i++;
        }
    }
}
void CalculateAdjacentMines()
{
    for (int row = 0; row < properties.rows; row++)
    {
        for (int col = 0; col < properties.cols; col++)
        {
            if (properties.grid[row][col].isMine)
                continue;

            int count = 0;
            for (int delta_row = -1; delta_row <= 1; delta_row++)
            {
                for (int delta_col = -1; delta_col <= 1; delta_col++)
                {
                    int new_row = row + delta_row, new_col = col + delta_col;
                    if (new_row >= 0 && new_row < properties.rows && new_col >= 0 && new_col < properties.cols && properties.grid[new_row][new_col].isMine)
                    {
                        count++;
                    }
                }
            }
            properties.grid[row][col].adjacentMines = count;
        }
    }
}
int userRow = 0;
int userCol = 0;
void DisplayGrid()
{
    MoveCursorToTopLeft();
    for (int r = 0; r < properties.rows; r++)
    {
        for (int c = 0; c < properties.cols; c++)
        {
            cout << "│ ";
            if (r == userRow && c == userCol)
            {
                cout << BG_GRAY;
            }
            if (properties.grid[r][c].isRevealed)
            {
                if (properties.grid[r][c].isMine)
                    cout << "*";
                else
                {
                    string colors[6] = {RESET, CYAN, BLUE, RED, ULTERARED, MAGENTA};
                    int adj_mine = properties.grid[r][c].adjacentMines;
                    if (adj_mine < 6)
                    {
                        cout << colors[adj_mine] << adj_mine;
                    }
                    else
                    {
                        cout << MAGENTA << adj_mine;
                    }
                }
            }
            else if (properties.grid[r][c].isFlagged)
            {
                cout << YELLOW << "F";
            }
            else
            {
                cout << RESET << "?";
            }
            cout << BG_RESET << RESET << " │";
        }
        cout << endl;
    }
}
void RevealCell(int row, int col)
{
    if (row < 0 || row >= properties.rows || col < 0 || col >= properties.cols || properties.grid[row][col].isRevealed)
        return;

    properties.grid[row][col].isRevealed = true;
    if (properties.grid[row][col].adjacentMines == 0 && !properties.grid[row][col].isMine)
    {
        for (int dr = -1; dr <= 1; dr++)
        {
            for (int delta_col = -1; delta_col <= 1; delta_col++)
            {
                RevealCell(row + dr, col + delta_col);
            }
        }
    }
}

void ToggleFlag(int row, int col)
{
    if (row >= 0 && row < properties.rows && col >= 0 && col < properties.cols && !properties.grid[row][col].isRevealed)
    {
        properties.grid[row][col].isFlagged = !properties.grid[row][col].isFlagged;
    }
}
void InitializeGird()
{
    for (int i = 0; i < properties.rows; i++)
    {
        for (int j = 0; j < properties.cols; j++)
        {
            properties.grid[i][j].adjacentMines = 0;
            properties.grid[i][j].isFlagged = false;
            properties.grid[i][j].isRevealed = false;
            properties.grid[i][j].isMine = false;
        }
    }
}
void InitializeGame(GameOptions options)
{
    ClearScreen();
    switch (options.difficulty)
    {
    case 0:
        properties.cols = 8;
        properties.rows = 5;
        properties.TotalMineCount = 5;
        break;
    case 1:
        properties.cols = 8;
        properties.rows = 10;
        properties.TotalMineCount = 40;
        break;
    case 2:
        properties.cols = 12;
        properties.rows = 12;
        properties.TotalMineCount = 60;
        break;
    case 3:
        properties.cols = options.customCols;
        properties.rows = options.customRows;
        properties.TotalMineCount = options.customMinesCount;
    }
    InitializeGird();
}
void StartGame()
{
    options = GameOptionsMenu();
    InitializeGame(options);

    bool IsGridGenerate = false;
    while (true)
    {
        DisplayGrid();
        cout << "Use WASD to move, F to flag, and R to reveal." << endl;
        char action = getch();
        if (action == 'w')
        {
            userRow--;
            if (userRow < 0)
                userRow = properties.rows - 1;
        }
        if (action == 's')
        {
            userRow++;
            if (userRow > properties.rows - 1)
                userRow = 0;
        }
        if (action == 'a')
        {
            userCol--;
            if (userCol < 0)
                userCol = properties.cols - 1;
        }
        if (action == 'd')
        {
            userCol++;
            if (userCol > properties.cols - 1)
                userCol = 0;
        }
        if (action == 'r')
        {
            if (!IsGridGenerate)
            {
                GenerateMines(properties.TotalMineCount, userRow, userCol);
                CalculateAdjacentMines();
                IsGridGenerate = true;
                RevealCell(userRow, userCol);
                continue;
            }
            if (properties.grid[userRow][userCol].isMine)
            {
                cout << "You hit a mine! Game Over!" << endl;
                break;
            }
            RevealCell(userRow, userCol);
        }
        else if (action == 'f')
        {
            ToggleFlag(userRow, userCol);
        }
        bool won = true;
        for (int r = 0; r < properties.rows; r++)
        {
            for (int c = 0; c < properties.cols; c++)
            {
                if (!properties.grid[r][c].isMine && !properties.grid[r][c].isRevealed)
                {
                    won = false;
                }
            }
        }
        if (won)
        {
            cout << "Congratulations! You won!" << endl;
            break;
        }
    }
    char c = getch();
    ClearScreen();
};
