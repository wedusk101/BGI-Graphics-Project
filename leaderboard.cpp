//leaderboards.cpp

#include "leaderboard.h"

void loadLeaderBoard(const std::string &fileName, Leaderboard &playerData) // read leaderboard object player data from <filename> and load it into object <playerData>
{
	std::ifstream in;
	in.open(fileName, std::ifstream::binary);
	in.read(reinterpret_cast<char*>(&playerData), sizeof(Leaderboard));
	in.close();
}

void saveLeaderBoard(const std::string &fileName, Leaderboard &playerData) // write leaderboard object player data to <filename> from object <playerData>
{
	std::ofstream out;
	out.open(fileName, std::ofstream::binary);
	out.write(reinterpret_cast<char*>(&playerData), sizeof(Leaderboard));
	out.close();
}

// updateLeaderBoard()

// displayLeaderBoard()