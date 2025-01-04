#include <fstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <ctime>
#include "game.h"
#include "colors.h"
#include "menu.h"
#include "utilities.h"
#include "form.h"
#include "player.h"
#include "leaderboard.h"
using namespace std;
struct Cell
{
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int adjacentMines;
};
int start_x = 10;
int start_y = 16;
struct GameProperties
{
    int rows;
    int cols;
    int UsageFlags;
    int TotalMineCount;
    bool GameEnd =false;
    Cell **grid;
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
    srand(static_cast<unsigned int>(time(nullptr)));
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
                    if (new_row >= 0 && new_row < properties.rows &&
                        new_col >= 0 && new_col < properties.cols &&
                        properties.grid[new_row][new_col].isMine)
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
void DisplayGround()
{
    int x = 9;
    int y = 14;
    int rows = 19;
    int cols = 39;
    Gotoxy(x, y);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            cout << BG_RESET << DARK_BLUE << "# ";
        }
        y++;
        Gotoxy(x, y);
    }
    cout << RESET;
}
void DisplayGrid()
{
    int x = start_x;
    int y = start_y;
    Gotoxy(x, y);
    for (int r = 0; r < properties.rows; r++)
    {
        for (int c = 0; c < properties.cols; c++)
        {
            if (r == userRow && c == userCol)
            {
                cout << BG_GRAY;
            }
            if (properties.grid[r][c].isMine && properties.GameEnd)
                cout << RED << "*" << RESET;
            else if (properties.grid[r][c].isRevealed)
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
            cout << BG_RESET << RESET;
            if (c != properties.cols - 1)
                cout << " ";
        }
        y++;
        Gotoxy(x, y);
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
        if (properties.grid[row][col].isFlagged)
        {
            properties.grid[row][col].isFlagged = false;
            properties.UsageFlags++;
        }
        else if (!properties.grid[row][col].isFlagged && properties.UsageFlags > 0)
        {
            properties.grid[row][col].isFlagged = true;
            properties.UsageFlags--;
        }
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
        properties.cols = 11;
        properties.rows = 5;
        properties.TotalMineCount = properties.cols * properties.rows * 0.1;
        break;
    case 1:
        properties.cols = 24;
        properties.rows = 11;
        properties.TotalMineCount = properties.cols * properties.rows * 0.2;
        break;
    case 2:
        properties.cols = 37;
        properties.rows = 17;
        properties.TotalMineCount = properties.cols * properties.rows * 0.5;
        break;
    case 3:
        properties.cols = options.customCols;
        properties.rows = options.customRows;
        properties.TotalMineCount = options.customMinesCount;
    }
    properties.grid = new Cell *[properties.rows];
    for (int i = 0; i < properties.rows; i++)
    {
        properties.grid[i] = new Cell[properties.cols];
    }
    properties.GameEnd = false;
    start_x = (87 - (properties.cols * 2 - 1)) / 2 + 3;
    start_y = 14 + (19 - properties.rows) / 2;
    if (start_x % 2 == 0)
        start_x++;
    properties.UsageFlags = properties.TotalMineCount;
    InitializeGird();
    ShowForm();
    DisplayGround();
}
void FreeGameGrid()
{
    for (int i = 0; i < properties.rows; i++)
    {
        delete[] properties.grid[i];
    }
    delete[] properties.grid;
}
void ShowGameOver(string fg_color, string bg_color)
{
    int x = 18;
    int y = 20;
    Gotoxy(x, y);
    cout << fg_color << bg_color << "   _____                         ____                 _ ";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"(  / ____|                       / __ \               | |)";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __| |";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__| |)";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |  |_|)";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"(  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|  (_))";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"(                                                        )";
}
void ShowCongratulations(string fg_color, string bg_color)
{

    int x = 22;
    int y = 19;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( ╔═══════════════════════════════════════════════╗ )";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( ║   __  __               _       ___       __   ║ )";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( ║   \ \/ /___  __  __   | |     / (_)___  / /   ║ )";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( ║    \  / __ \/ / / /   | | /| / / / __ \/ /    ║ )";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( ║    / / /_/ / /_/ /    | |/ |/ / / / / /_/     ║ )";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( ║   /_/\____/\__,_/     |__/|__/_/_/ /_(_)      ║ )";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( ║                                               ║ )";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( ║  ══════════════════════════════════════════   ║ )";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( ╚═══════════════════════════════════════════════╝ )";
}
void StartGame(Player player)
{

    options = GameOptionsMenu();
    if (options.status == 0)
        return;
    InitializeGame(options);
    int revalvedCellsCount = 0;
    time_t startTime, endTime;
    startTime = time(NULL);
    bool IsGridGenerate = false;
    bool isWin = true;
    while (!properties.GameEnd)
    {
        DisplayGrid();
        // SetFooter("Use WASD to move, F to flag, and R to reveal");
        Label gameinformation;
        gameinformation.text = "Flags: " + IntToString(properties.UsageFlags);
        gameinformation.color = GREEN;
        if (properties.UsageFlags < properties.TotalMineCount / 3)
            gameinformation.color = RED;
        else if (properties.UsageFlags < 2 * properties.TotalMineCount / 3)
            gameinformation.color = YELLOW;
        ShowLabel(gameinformation, 33);
        SetFooter("Use WASD to move, F to flag, R to reveal, V to win!");
        char action = getch();
        if (isupper(action))
        {
            action = tolower(action);
        }
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
                startTime = time(NULL);
                RevealCell(userRow, userCol);
                continue;
            }
            if (properties.grid[userRow][userCol].isMine)
            {
                properties.GameEnd = true;
                break;
            }
            RevealCell(userRow, userCol);
            revalvedCellsCount++;
        }
        else if (action == 'f')
        {
            ToggleFlag(userRow, userCol);
        }
        isWin = true;
        for (int r = 0; r < properties.rows; r++)
        {
            for (int c = 0; c < properties.cols; c++)
            {
                if (!properties.grid[r][c].isMine && !properties.grid[r][c].isRevealed)
                {
                    isWin = false;
                }
            }
        }
        if (action == 'v')
        {
            isWin = true;
        }
        if (isWin)
        {
            properties.GameEnd = true;
            break;
        }
    }
    DisplayGrid();
    Sleep(500);
    if (properties.GameEnd)
    {
        if (isWin)
        {
            for (int i = 0; i < 12; i++)
            {

                ShowCongratulations(BG_GREEN, RESET);
                Sleep(150);
                ShowCongratulations(BG_RESET, GREEN);
                Sleep(150);
            }
            Sleep(1000);
        }
        else
        {
            properties.GameEnd = true;
            for (int i = 0; i < 12; i++)
            {

                ShowGameOver(BG_RED, RESET);
                Sleep(150);
                ShowGameOver(BG_RESET, RED);
                Sleep(150);
            }
            Sleep(1000);
        }
    }
    FreeGameGrid();
    endTime = time(NULL);
    double duration = difftime(endTime, startTime);
    int score = CalculateScore(duration, revalvedCellsCount, isWin);
    player.score = score;
    player.isWin = isWin;
    if (score > 0)
    {
        UpdateLeaderboard(player);
    }
    char c = getch();
    ClearScreen();
};
int CalculateScore(double duration, int revalvedCellsCount, bool isWin)
{
    if (isWin)
    {
        int _const = 100000;
        return ((properties.TotalMineCount * 1.0) / (properties.rows * properties.cols) + 1) * ((_const * 1.0) / (duration + 1));
    }
    int _const = 37 * 19;
    return (_const * ((revalvedCellsCount * 1.0) / (properties.rows * properties.cols)));
}
