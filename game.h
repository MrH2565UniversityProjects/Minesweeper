#pragma once
bool AreCellsAdjacent(int row1,int col1,int row2, int col2);
void GenerateMines(int totalMines, int user_row, int user_col);
void CalculateAdjacentMines();
void DisplayGrid();
void RevealCell(int row, int col);
void ToggleFlag(int row, int col);
void InitializeGird();
void InitializeGame();
void Gameplay(Player player);
int CalculateScore(double duration,int revalvedCellsCount,bool isWin);
void FreeGameGrid();
void WinAnimation();
void LoseAnimation();
void StartGame(bool &IsGridGenerate, time_t &startTime);
bool WinCheck();
void ShowFlagsInformation();