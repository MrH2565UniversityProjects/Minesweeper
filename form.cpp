#include <iostream>
#include <iomanip>
#include <conio.h>
#include "form.h"
#include "utilities.h"
#include "colors.h"
void ShowButton(Button &_button, Display &_display)
{
    int x = 8;
    int y = 14 + _display.row * 4;
    Gotoxy(x, y);
    if (_display.row == _display.user_row_position)
    {
        cout << _button.hover_color << "╒══╕ ╒═══════════════════════════════════════════════════════════════════════╕" << RESET, Gotoxy(x, y + 1);
        cout << _button.hover_color << "│██│ │  " << setw(65) << left << _button.label << "    │" << RESET, Gotoxy(x, y + 2);
        cout << _button.hover_color << "╘══╛ ╘═══════════════════════════════════════════════════════════════════════╛" << RESET;
    }
    else
    {
        cout << _button.color << "╒══╕ ╒═══════════════════════════════════════════════════════════════════════╕" << RESET, Gotoxy(x, y + 1);
        cout << _button.color << "│░░│ │  " << setw(65) << left << _button.label << "    │" << RESET, Gotoxy(x, y + 2);
        cout << _button.color << "╘══╛ ╘═══════════════════════════════════════════════════════════════════════╛" << RESET;
    }
    _display.row++;
}
void SetFooter(string label)
{
    int y = 35;
    int x = (87 - label.length()) / 2 + 3;
    Gotoxy(x, y);
    cout << label;
};
void NavigateForm(Display &display, char input)
{
    switch (input)
    {
    case 'w':
        display.user_row_position--;
        if(display.user_row_position < display.start_row)
            display.user_row_position = display.start_row+display.row_count-1;
        break;
    case 's':
    display.user_row_position++;
        if(display.user_row_position >= display.start_row+display.row_count)
            display.user_row_position = display.start_row;
        break;
    default:
        display.user_row_position = display.user_row_position;
        break;
    }
}
void ShowTextbox(Textbox& _textbox,Display& _display){
    int x = 8;
    int y = 14 + _display.row * 4;
    Gotoxy(x, y);
        cout << _textbox.color << "╒════════════════════════════════════════════════════════════════════════════╕" << RESET, Gotoxy(x, y + 1);
        cout << _textbox.color << "│    " << setw(15) << left << _textbox.label << ": " << setw(51) << left << "" << "    │" << RESET, Gotoxy(x, y + 2);
        cout << _textbox.color << "╘════════════════════════════════════════════════════════════════════════════╛" << RESET;
    
    _display.row++;
}
void ShowButtons(Button _buttons[], Display &_display)
{
    for (int i = 0; i < _display.row_count; i++)
    {
        ShowButton(_buttons[i], _display);
    }
}
void ShowTextboxs(Textbox _textboxs[], Display &_display)
{
    for (int i = 0; i < _display.row_count; i++)
    {
        ShowTextbox(_textboxs[i], _display);
    }
}
void ShowForm(){
    cout << blank_form;
}

void ResetDisplay(Display &display){
     display.row = display.start_row;
}