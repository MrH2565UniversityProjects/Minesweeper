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
        cout << BG_RESET << RESET;
        MoveCursorToTopLeft();
        ShowForm();
        Label WelcomeMessage = {"Welcome " + player.name, YELLOW};
        ShowLabel(WelcomeMessage, 15);
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
                Gameplay(player);
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
    Player player = {"", 0, false};
    Display display = {4, 4, 1, 4, true};
    Textbox textbox = {"Enter your name", 5, YELLOW};
    string footer_label = "Press Any Key To Start Game!";
    ClearScreen();
    while (display.isRunning)
    {
        MoveCursorToTopLeft();
        ShowForm();
        int x = 8;
        int y = 14;
        Gotoxy(x,y);
        cout << CYAN << "╔════════════════════════════════════════════════════════════════════════════╗";
        for(int i=0;i<13;i++){
        y++;
        Gotoxy(x,y);
        cout << "║                                                                            ║";
        }
                y++;
        Gotoxy(x,y);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝" << RESET;
        y=17;
        string lines[6] = {
            {"Welcome to Minesweeper!"},
            {"Face the ultimate challenge: uncover tiles, avoid mines, and"},
            {"trust your instincts. Every number is a clue"},
            {" every move a risk. Strategy and focus are key!"},
            {" Created as a simple yet exciting programming project by:"},
            {"Mahdi Hoseinpoor - 2025"}
        };

        PrintC((lines[0]),y);
        y++;
        PrintC(lines[1],y);
        PrintC(lines[2],y);
        PrintC(lines[3],y);
        y++;
        PrintC(lines[4],y);
        y++;
        PrintC(lines[5],y);
        ShowTextbox(textbox, display);
        ResetDisplay(display);
        ShowCursor();
        GetTextboxInput(textbox, display);
        HideCursor();
        string name = textbox.value;
        replace(name.begin(), name.end(), ' ', '_');
        if (name == "")
            name = "_blank";
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
    Button buttons[5] = {
        {"Easy", 0, GREEN, GREEN},
        {"Medium", 1, YELLOW, YELLOW},
        {"Hard", 2, RED, RED},
        {"Custom", 3, BLUE, BLUE}};

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
        if(input == 27){
            gameOptions.status = 0;
            return gameOptions;
        }
        else if (input != '\r')
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
        {"Rows count", 0, CYAN, true, {"Rows must Be a number Between 3 and 17", RED}},
        {"Columns count", 1, CYAN, true, {"Columns must Be a number Between 3 and 37", RED}},
        {"Mines Cont", 2, CYAN, true, {"Mines must be positive number and lower than all cells mines 18", RED}}};
    string footer_label = "Press Any Key To Start Game!";
    ClearScreen();
    while (display.isRunning)
    {
        MoveCursorToTopLeft();
        ResetDisplay(display);
        ShowForm();
        ShowTextboxs(textbox, display);
        ResetDisplay(display);
        ShowCursor();
        bool closeMenu = false;
         while (!closeMenu)
        {
            GetTextboxInput(textbox[0], display);
            if(textbox[0].value == ""){
                closeMenu = true;
                break;
            }
            gameOptions.customRows = stoi(textbox[0].value);
            if (gameOptions.customRows > 17 || gameOptions.customRows < 3)
            {
                ResetTextboxInput(textbox[0], display);
            }else break;
        }

         while (!closeMenu)
        {
            GetTextboxInput(textbox[1], display);
            gameOptions.customCols = stoi(textbox[1].value);
            if (gameOptions.customCols > 37 || gameOptions.customCols < 3)
            {
                ResetTextboxInput(textbox[1], display);
            }else break;
        };
        int countdownToReset = 1;
        while (!closeMenu)
        {
            if(countdownToReset < 0)
                break;
            GetTextboxInput(textbox[2], display);
            gameOptions.customMinesCount = stoi(textbox[2].value);
            if ((gameOptions.customMinesCount >= gameOptions.customRows * gameOptions.customCols - 18) ||
                gameOptions.customMinesCount < 1)
            {
                ResetTextboxInput(textbox[2], display);
                countdownToReset--;

            }else break;
        }

        HideCursor();
        if(countdownToReset < 0)
            continue;
        if(closeMenu)
            gameOptions.status = 0;
        return gameOptions;
    }
}