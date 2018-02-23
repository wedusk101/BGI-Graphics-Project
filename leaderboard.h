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

	Leaderboard() : rank(1), name("player"), topScore(0) {} // default constructor
};


void saveLeaderBoard(const std::string &, Leaderboard &); // write leaderboard data to file - serialize object data 
void loadLeaderBoard(const std::string &, Leaderboard &); // read leaderboard data from file - deserialize object data
// rank players - sort the data according to high scores - updateLeaderBoard()
// display leaderboard data - displayLeaderBoard()

#endif