#pragma once
#include <string>
using namespace std;
const string blank_form = R"(
    ╔═════════════════════════════════════════════════════════════════════════════════════╗
    ╠═════════════════════════════════════════════════════════════════════════════════════╣
    ║    ___ ___  ____  ____     ___  _____ __    __    ___    ___  ____    ___  ____     ║
    ║   ║   T   Tl    j║    \   /  _]/ ___/║  T__T  T  /  _]  /  _]║    \  /  _]║    \    ║
    ║   ║ _   _ ║ ║  T ║  _  Y /  [_(   \_ ║  ║  ║  ║ /  [_  /  [_ ║  o  )/  [_ ║  D  )   ║
    ║   ║  \_/  ║ ║  ║ ║  ║  ║Y    _]\__  T║  ║  ║  |Y    _]Y    _]║   _/Y    _]║    /    ║
    ║   ║   ║   ║ ║  ║ ║  ║  |║   [_ /  \ |l  `  '  !║   [_ ║   [_ ║  ║  ║   [_ ║    \    ║
    ║   ║   ║   ║ j  l ║  ║  |║     T\    ║ \      / ║     T║     T║  ║  ║     T║  .  Y   ║
    ║   l___j___j|____jl__j__jl_____j \___j  \_/\_/  l_____jl_____jl__j  l_____jl__j\_j   ║
    ║                                                                                     ║
    ╠═════════════════════════════════════════════════════════════════════════════════════╣
    ╠═════════════════════════════════════════════════════════════════════════════════════╣
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ║                                                                                     ║
    ╠═════════════════════════════════════════════════════════════════════════════════════╣
    ║                                                                                     ║
    ╚═════════════════════════════════════════════════════════════════════════════════════╝)";
    
struct Display{
    int row = 0;
    int start_row = 0;
    int row_count = 5;
    int user_row_position = 0;
    bool isRunning = true;
};
struct Button{
string label;
int row;
string color = RESET;
string hover_color = YELLOW;
};
struct Textbox{
    string label;
    int row;
    string color = RESET;
    bool IsNumberOnly = false;
    string value = "";
};
struct Label{
    string text;
    string color = RESET;   
};
void NavigateForm(Display &display , char input);
void SetFooter(string label);
void ShowButton(Button &_button,Display& _display);
void ShowTextbox(Textbox &_textbox,Display& _display);
void ShowButtons(Button _buttons[],Display& _display);
void ShowTextboxs(Textbox _textboxs[], Display &_display);
void GetTextboxInputs(Textbox &_textbox, Display &_display);;
void ResetDisplay(Display &display);
void ShowLabel(Label &_label,int y);
void ShowForm();