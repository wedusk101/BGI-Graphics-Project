//leaderboards.cpp

#include "leaderboard.h"
#include <algorithm>
#include <iostream> // debugging

void saveLeaderBoard(const std::string &fileName, Leaderboard &playerData) // write leaderboard object player data to <filename> from object <playerData>
{
	const uint32_t size = 3 * sizeof(uint32_t); // calculate data packing sizes
	const uint32_t len = playerData.nameLen + 1;
	char *dst = new char[size + len];
	memcpy(dst, (void*)&playerData, size); // serialize the class
	memcpy(dst + size, playerData.playerName, len);
	std::ofstream out;
	out.open(fileName, std::ofstream::binary); // for appending ---->   out.open(fileName, std::ofstream::binary | std::ofstream::app); 
	out.write(dst, size + len); // write out the data
	out.close();
	delete[] dst;
}

void loadLeaderBoard(const std::string &fileName, Leaderboard &playerData) // read leaderboard object player data from <filename> and load it into object <playerData>
{
	FILE *fp = fopen(fileName.c_str(), "r");
	if (fp == nullptr)
	{
		std::cout << "Invalid file!" << std::endl;
		return;
	}
	size_t nBytes = 0;
	while (getc(fp) != EOF)
		nBytes++; // get number of bytes in file
	fclose(fp);
	const uint32_t size = 3 * sizeof(uint32_t);
	const uint32_t pLen = nBytes - size; // length of player name
	char *src = new char[nBytes]; // raw bytes will be read into this buffer
	fp = fopen(fileName.c_str(), "r");
	fgets(src, nBytes, fp); // deserialize file
	fclose(fp);
	memcpy((void*)&playerData, src, size);
	playerData.nameLen = pLen;
	char *name = new char[pLen]; // freeing this pointer will not be possible as there is a shallow copy taking place later
	memcpy(name, src + size, pLen);
	playerData.playerName = name; // restore output path
	delete[] src;
}

bool updateLeaderBoard(const Leaderboard &a, const Leaderboard &b) // rank players - sort the data according to high scores 
{
	return a.topScore > b.topScore; // call std::sort(playerVector.begin(), playerVector.end(), updateLeaderBoard)
}

void displayLeaderBoard(const Leaderboard &playerData)
{
	std::cout << "\n Rank " << playerData.rank << " Top Score " << playerData.topScore << "\n" << std::endl; // display data on console for debugging purposes
}