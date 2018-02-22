//leaderboard.h
#pragma once

#ifndef LEADERBOARD__H_
#define LEADERBOARD__H_

#include <string>
#include <fstream>
//#include <vector>
//#include <algorithm>
//#include "graphics.h"

struct Leaderboard
{
	int rank;
	std::string name;
	int topScore;
};

// read leaderboard data from file - loadLeaderBoard()
// write leaderboard data to file - saveLeaderBoard()
// rank players - sort the data according to high scores - updateLeaderBoard()
// display leaderboard data - displayLeaderBoard()

#endif