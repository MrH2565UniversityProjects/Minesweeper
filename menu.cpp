#include <iostream>
#include "menu.h"
#include "utilities.h"
#include "colors.h"
#include "game.h"
#include "leaderboard.h"
#include "form.h"
#include "form.cpp"
#include <iomanip>
#include <conio.h>
#include <string>
#include <algorithm>
using namespace std;

void MainMenu(Player player)
{
    Display display = {1, 1, 3, 1};
    const int bottonsCount = 3;
    Button buttons[bottonsCount] = {
        {"New Game", 0},
        {"Leaderboard", 1},
        {"Exit", 2}};
    string footer_label = "Main Menu";
    ClearScreen();
    while (display.isRunning)
    {
        MoveCursorToTopLeft();
        ShowForm();
        Label WelcomeMessage = { "Welcome " + player.name,YELLOW};
        ShowLabel(WelcomeMessage,15);
        ShowButtons(buttons, display);
        SetFooter(footer_label);
        display.row = display.start_row;

        char input = getch();
        if (input != '\r')
        {
            NavigateForm(display, input);
        }
        else
        {
            switch (display.user_row_position)
            {
            case 1:
                StartGame(player);
                break;
            case 2:
                Leaderboard();
                break;
            case 3:
                display.isRunning = false;
                break;
            default:
                break;
            }
        }
    }
}
Player SignInMenu()
{
    Player player = {"",0,false};
    Display display = {2, 2, 1, 2, true};
    const int textboxsCount = 3;
    Textbox textbox = {"Enter your name", 0, YELLOW};
    string footer_label = "Press Any Key To Start Game!";
    ClearScreen();
    while (display.isRunning)
    {
        MoveCursorToTopLeft();
        ShowForm();

        ShowTextbox(textbox, display);
        ResetDisplay(display);
        ShowCursor();
            int x = 30;
            int y = 15 + (display.row) * 4;
            Gotoxy(x, y);
            textbox.value = GetInput(51, x, y);
        
        HideCursor();
        string name = textbox.value;
        replace(name.begin(), name.end(), ' ', '_');
        player.name = name;
        break;
    }
    return player;
}
GameOptions GameOptionsMenu()
{
    GameOptions gameOptions;

    Display display = {0, 0, 4, 0, true};
    const int bottonsCount = 4;
    Button buttons[4] = {
        {"Easy", 0, GREEN, GREEN},
        {"Medium", 1, YELLOW, YELLOW},
        {"Hard", 2, RED, RED},
        {"Custom", 3, RESET, RESET}};

    string footer_label = "Game Options";
    ClearScreen();
    while (display.isRunning)
    {
        MoveCursorToTopLeft();
        ShowForm();
        ShowButtons(buttons, display);
        SetFooter(footer_label);
        ResetDisplay(display);
        char input = getch();
        if (input != '\r')
        {
            NavigateForm(display, input);
        }
        else
        {
            gameOptions.difficulty = display.user_row_position;
            if (display.user_row_position == 3)
                return CustomGameOptionsMenu(gameOptions);
            return gameOptions;
        }
    }
}
GameOptions CustomGameOptionsMenu(GameOptions gameOptions)
{
    Display display = {1, 1, 3, 1, true};
    const int textboxsCount = 3;
    Textbox textbox[textboxsCount] = {
        {"Rows count", 0, RESET},
        {"Columns count", 1, RESET},
        {"Mines Cont", 2, RESET}};
    string footer_label = "Press Any Key To Start Game!";
    ClearScreen();
    while (display.isRunning)
    {
        MoveCursorToTopLeft();
        ShowForm();
        ShowTextboxs(textbox, display);
        ResetDisplay(display);
        ShowCursor();
        for (int i = 0; i < textboxsCount; i++)
        {
            int x = 30;
            int y = 15 + (display.row + i) * 4;
            Gotoxy(x, y);
            textbox[i].value = GetInput(51, x, y);
        }
        HideCursor();
        gameOptions.customRows = stoi(textbox[0].value);
        gameOptions.customCols = stoi(textbox[1].value);
        gameOptions.customMinesCount = stoi(textbox[2].value);
        if (gameOptions.customRows > 19 ||
            gameOptions.customCols > 37 ||
            (gameOptions.customMinesCount >= gameOptions.customRows * gameOptions.customCols - 18) ||
            gameOptions.customMinesCount < 1)
        {
            SetFooter("Please enter logical information!");
            char input = getch();
        }
        else
        {
            SetFooter(footer_label);
            return gameOptions;
        }
    }
}