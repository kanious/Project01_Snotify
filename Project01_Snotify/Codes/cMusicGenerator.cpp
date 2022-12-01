#include "cMusicGenerator.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Functions.h"
using namespace std;

cMusicGenerator::cMusicGenerator()
{

}

cMusicGenerator::~cMusicGenerator()
{
	m_vecSongs.clear();
}

bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
	ifstream namesFile(musicFileName);
	if (!namesFile.is_open())
	{
		errorString = "Failed to open the music information data file.";
		return false;
	}

	int totalNum = 0;
	string nextLine;
	unsigned int tokenCount = 0;
	hash_map<string, sSongInfo> mapSongs;
	hash_map<string, sSongInfo> mapSongs_artistVer;
	int lineNum = 0;

	getline(namesFile, nextLine); //first line
	while (getline(namesFile, nextLine))
	{
		stringstream sLine(nextLine);
		string token;
		sSongInfo song;
		getline(sLine, token, ',');
		getline(sLine, token, ',');
		getline(sLine, token, ',');
		tokenCount = 3;
		while (getline(sLine, token, ','))
		{
			switch (tokenCount)
			{
			case 3:
				song.name = token;
				break;
			case 4:
				song.artist = token;
				break;
			}
			tokenCount++;

			if (tokenCount > 4)
				break;
		}
		if (!mapSongs.insert(song.name, song))
			mapSongs_artistVer.insert(song.artist, song);

		lineNum++;
		if (lineNum > 2000)
			break;
	}

	hash_map<string, sSongInfo>::iterator iter = mapSongs.begin();
	for (iter = mapSongs.begin(); iter != mapSongs.end(); ++iter)
	{
		iter.second().audioTag = GetRandomAudio();
		m_vecSongs.push_back(iter.second());
	}
	mapSongs.clear();

	for (iter = mapSongs_artistVer.begin(); iter != mapSongs_artistVer.end(); ++iter)
	{
		iter.second().audioTag = GetRandomAudio();
		m_vecSongs.push_back(iter.second());
	}
	mapSongs_artistVer.clear();

	return true;
}

cSong* cMusicGenerator::getRandomSong(void)
{
	int randNum = GetRandNum_Big(0, m_vecSongs.size() - 1);
	sSongInfo info = m_vecSongs[randNum];

	cSong* pSong = new cSong();
	pSong->name = info.name;
	pSong->artist = info.artist;
	pSong->audioTag = info.audioTag;

	return pSong;
}

cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
	for (int i = 0; i < m_vecSongs.size(); ++i)
	{
		sSongInfo info = m_vecSongs[i];
		if (info.name == songName && info.artist == artist)
		{
			cSong* pSong = new cSong();
			pSong->name = info.name;
			pSong->artist = info.artist;
			pSong->audioTag = info.audioTag;

			return pSong;
		}
	}
	
	return nullptr;
}

string cMusicGenerator::GetRandomAudio()
{
	string audio = "";
	int randNum = GetRandNum(0, 4);

	switch (randNum)
	{
	case 0: audio = "EmeraldSword"; break;
	case 1: audio = "IfYouWantMe"; break;
	case 2: audio = "30Minutes"; break;
	case 3: audio = "ThisIsTheMoment"; break;
	case 4: audio = "BadGuy"; break;
	}
	return audio;
}
