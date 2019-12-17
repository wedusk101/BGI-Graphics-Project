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
	int topScore;
	uint32_t nameLen;
	char *playerName; 


	Leaderboard() : rank(INT_MAX), playerName(""), topScore(INT_MIN)
	{
		nameLen = strlen(playerName);
	}

	Leaderboard(char *name) : rank(INT_MAX), playerName(name), topScore(INT_MIN)
	{
		nameLen = strlen(playerName);
	}
};


void saveLeaderBoard(const std::string &, Leaderboard &); // write leaderboard data to file - serialize object data 
void loadLeaderBoard(const std::string &, Leaderboard &); // read leaderboard data from file - deserialize object data

bool updateLeaderBoard(const Leaderboard &, const Leaderboard &); // rank players - sort the data according to high scores 

void displayLeaderBoard(const Leaderboard &); // display leaderboard data 

#endif