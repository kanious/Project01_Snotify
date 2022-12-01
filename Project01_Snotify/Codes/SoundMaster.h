#ifndef _SOUNDMASTER_H_
#define _SOUNDMASTER_H_

#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_errors.h"

#include "HashMap.h"

class SoundMaster
{
private:
	struct sSound
	{
		FMOD::Sound* sound;
		FMOD::Channel* channel;
	};

public:
	FMOD::System* m_pSystem;

	typedef hash_map<std::string, sSound> SOUND_MAP;
	SOUND_MAP m_mapSounds;

public:
	SoundMaster();
	~SoundMaster();

public:
	void LoadSong(std::string tag, std::string path);
	void PlaySong(std::string tag);
	void StopSong(std::string tag);
};

#endif //_SOUNDMASTER_H_