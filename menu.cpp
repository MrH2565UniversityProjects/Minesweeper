#include <iostream>
#include "menu.h"
using namespace std;

struct Button
{
    string label;
    int id;
    string color = RESET;
};
void DisplayButton(string label, bool isSelected, int whitespaceCount, string color = RESET, string selected_color = YELLOW)
{
    string whitespace = "";
    for (int i = 0; i < whitespaceCount; i++)
    {
        whitespace += " ";
    }
    if (isSelected)
    {
        cout << selected_color << whitespace << "╒════════════════════╕" << RESET << endl;
        cout << selected_color << whitespace << "│   " << setw(17) << left << label << "│  ■" << RESET << endl;
        cout << selected_color << whitespace << "╘════════════════════╛" << RESET << endl;
    }
    else
    {
        cout << color << whitespace << "╒════════════════════╕" << RESET << endl;
        cout << color << whitespace << "│   " << setw(17) << left << label << "│" << RESET << endl;
        cout << color << whitespace << "╘════════════════════╛" << RESET << endl;
    }
}
void DisplayHeader(string &header)
{
    cout << CYAN << header << RESET << endl
         << endl;
}
void DisplayMenu(string& header, Button* buttons, int buttonsCount, int selectedButton, bool useSelectedButtonColor = true, string SelectedButtonColor = YELLOW)
{
    DisplayHeader(header);
    for (int i = 0; i < buttonsCount; ++i)
    {
        string selectedButtonColor;
        if (useSelectedButtonColor)
        {
            selectedButtonColor = SelectedButtonColor;
        }
        else
        {
            selectedButtonColor = buttons[i].color;
        }
        int whitespace = GetMaxLineLength(header)/2-11;
        DisplayButton(buttons[i].label, buttons[i].id == selectedButton,whitespace, buttons[i].color, selectedButtonColor);
    }
}
int NavigateMenu(int currentSelection, int buttonsCount, char input)
{
    switch (input)
    {
    case 'w':
        return (currentSelection - 1 + buttonsCount) % buttonsCount;
    case 's':
        return (currentSelection + 1) % buttonsCount;
    default:
        return currentSelection;
    }
}
void MainMenu()
{
    string header = R"(
    __  __ _____ _   _ ______  _______          ________ ______ _____  ______ _____    _ 
   |  \/  |_   _| \ | |  ____|/ ____\ \        / /  ____|  ____|  __ \|  ____|  __ \  | |
   | \  / | | | |  \| | |__  | (___  \ \  /\  / /| |__  | |__  | |__) | |__  | |__) | | |
   | |\/| | | | | . ` |  __|  \___ \  \ \/  \/ / |  __| |  __| |  ___/|  __| |  _  /  | |
   | |  | |_| |_| |\  | |____ ____) |  \  /\  /  | |____| |____| |    | |____| | \ \  |_|
   |_|  |_|_____|_| \_|______|_____/    \/  \/   |______|______|_|    |______|_|  \_\ (_))";

    Button Buttons[3] = {
        {"New Game", 0},
        {"Leaderboard", 1},
        {"Exit", 2}};
    int selectedButton = 0;
    int buttonsCount = sizeof(Buttons) / sizeof(Buttons[0]);
    bool isRunning = true;

    while (isRunning)
    {
        ClearScreen();
        DisplayMenu(header, Buttons, buttonsCount, selectedButton, true, YELLOW);

        char input = getch();
        if (input == '\r')
        {
            switch (selectedButton)
            {
            case 0:
                StartGame();
                break;
            case 1:
                Leaderboard();
                break;
            case 2:
                isRunning = false;
                break;
            default:
                break;
            }
        }
        else
        {
            selectedButton = NavigateMenu(selectedButton, buttonsCount, input);
        }
    }
}
GameOptions GameOptionsMenu()
{
    string header = R"(
      _____                         ____        _   _                 
     / ____|                       / __ \      | | (_)                
    | |  __  __ _ _ __ ___   ___  | |  | |_ __ | |_ _  ___  _ __  ___ 
    | | |_ |/ _` | '_ ` _ \ / _ \ | |  | | '_ \| __| |/ _ \| '_ \/ __|
    | |__| | (_| | | | | | |  __/ | |__| | |_) | |_| | (_) | | | \__ \
     \_____|\__,_|_| |_| |_|\___|  \____/| .__/ \__|_|\___/|_| |_|___/
                                         | |                          
                                         |_|                          
)";
    GameOptions gameOptions;
    Button Buttons[4] = {
        {"Easy", 0, GREEN},
        {"Medium", 1, YELLOW},
        {"Hard", 2, RED},
        {"Legendary", 3, MAGENTA}};
    int selectedButton = 0;
    int buttonsCount = sizeof(Buttons) / sizeof(Buttons[0]);
    bool isRunning = true;
    ClearScreen();
    cout << endl;
    cout << CYAN << "======================================================================" << endl;
    cout << CYAN << "    ■   " << RESET << "Enter Your name (whitespace is not allowed): " << YELLOW;
    cin >> gameOptions.playerName;
    cout << RESET;
    while (isRunning)
    {
        ClearScreen();
        DisplayMenu(header, Buttons, buttonsCount, selectedButton, false);

        char input = getch();
        if (input == '\r')
        {
            gameOptions.difficulty = selectedButton;
            return gameOptions;
        }
        else
        {
            selectedButton = NavigateMenu(selectedButton, buttonsCount, input);
        }
    }
    return gameOptions;
}