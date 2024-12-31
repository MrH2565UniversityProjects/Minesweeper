#include <iostream>
using namespace std;
void HideCursor()
{
    cout << "\033[?25l";
    cout.flush();
}

void ShowCursor()
{
    cout << "\033[?25h";
    cout.flush();
}
void ClearScreen()
{
    cout << "\033[2J\033[H";
}

int GetMaxLineLength(string multilineString) {
    stringstream ss(multilineString);
    string line;
    int maxLength = 0;

    while (getline(ss, line)) {
        int lineLength = line.length();
        if (lineLength > maxLength) {
            maxLength = lineLength; 
        }
    }
    return maxLength;
}