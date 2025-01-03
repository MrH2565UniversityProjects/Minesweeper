#pragma once
#include <string>
#include "player.h"
using namespace std;
void Leaderboard();
string GetDefaultFileName();
void Leaderboard(string Filename);
Player* LoadPlayers(string Filename);
void WritePlayersToFile(string Filename, Player players[], int counter);
void ReadPlayersFromFile(string Filename, Player players[], int &counter);
void UpdateLeaderboard(Player player);
void UpdateLeaderboard(string Filename,Player player);