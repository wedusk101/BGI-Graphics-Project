//leaderboard.h
#pragma once

#ifndef LEADERBOARD__H_
#define LEADERBOARD__H_

#include <string>
#include <fstream>
#include <climits>
#include "graphics.h"

struct Leaderboard
{
	int rank;
	// std::string name; // object serialization fails for strings as of now
	int topScore;

	Leaderboard() : rank(INT_MAX), /*name("player"),*/ topScore(INT_MIN) {} // default constructor
};


void saveLeaderBoard(const std::string &, Leaderboard &); // write leaderboard data to file - serialize object data 
void loadLeaderBoard(const std::string &, Leaderboard &); // read leaderboard data from file - deserialize object data

bool updateLeaderBoard(const Leaderboard &, const Leaderboard &); // rank players - sort the data according to high scores 

void displayLeaderBoard(const Leaderboard &); // display leaderboard data 

#endif