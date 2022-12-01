#ifndef _cMusicGenerator_HG_
#define _cMusicGenerator_HG_

#include "cSong.h"
#include "HashMap.h"
#include "Vector.h"
#include <iostream>
using namespace std;
class cMusicGenerator
{
public:
	cMusicGenerator();
	~cMusicGenerator();

	bool LoadMusicInformation(std::string musicFileName, std::string& errorString);

	cSong* getRandomSong(void);
	
	// Returns 0, NULL, or nullptr if no song is found
	// This must be an EXACT MATCH for what's in the billboard100 file. 
	// So case sensitive, etc. 
	cSong* findSong(std::string songName, std::string artist);


// ¡å¡å¡å MyWork ¡å¡å¡å //
private:
	struct sSongInfo
	{
		std::string name;
		std::string artist;
		std::string audioTag;

		bool operator ==(const sSongInfo& rhs) const { return name == rhs.name && artist == rhs.artist; }
		bool operator !=(const sSongInfo& rhs) const { return name != rhs.name || artist != rhs.artist; }
	};
private:
	vector<sSongInfo> m_vecSongs;
private:
	std::string GetRandomAudio();
public:
	void test()
	{
		for (int i = 0; i < m_vecSongs.size(); ++i)
		{
			cout << m_vecSongs[i].name << ", " << m_vecSongs[i].artist << endl;
		}
	}
// ¡ã¡ã¡ã MyWork ¡ã¡ã¡ã //
};

#endif
	