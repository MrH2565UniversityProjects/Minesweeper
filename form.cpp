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
    Label _label = {label, RESET};
    ShowLabel(_label, 35);
};
void NavigateForm(Display &display, char input)
{
    if (isupper(input))
    {
        input = tolower(input);
    }

    switch (input)
    {
    case 'w':
        display.user_row_position--;
        if (display.user_row_position < display.start_row)
            display.user_row_position = display.start_row + display.row_count - 1;
        break;
    case 's':
        display.user_row_position++;
        if (display.user_row_position >= display.start_row + display.row_count)
            display.user_row_position = display.start_row;
        break;
    default:
        display.user_row_position = display.user_row_position;
        break;
    }
}
void ShowTextbox(Textbox &_textbox, Display &_display)
{
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
void ShowForm()
{
    cout << RESET << blank_form;
}

void ResetDisplay(Display &display)
{
    display.row = display.start_row;
}
void ShowLabel(Label &_label, int y)
{
    int x = (87 - _label.text.length()) / 2 + 3;
    Gotoxy(x, y);
    cout << _label.color << _label.text << RESET;
}
void GetTextboxInput(Textbox &_textbox, Display &_display)
{
    int x = 30;
    int y = 15 + _display.row * 4;
    Gotoxy(x, y);
    if (_textbox.IsNumberOnly)
    {
        _textbox.value = GetNumberInput(51, x, y);
    }
    else
    {
        _textbox.value = GetInput(51, x, y);
    }
    _display.row++;
}
void ResetTextboxInput(Textbox &_textbox, Display &_display)
{
    _display.row--;
    int x = 30;
    int y = 15 + _display.row * 4;
    Gotoxy(x, y);
    for(int i = 0; i < _textbox.value.length(); i++)
    {
        cout << ' ';
    }
    ShowLabel(_textbox.ValidationMessage,y+2);
}