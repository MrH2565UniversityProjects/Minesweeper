#pragma once
#include <string>
#include "player.h"
using namespace std;
void Leaderboard();
void Leaderboard(string LeaderboardFileName);
Player* LoadPlayers(string LeaderboardFileName);