#include "SoundMaster.h"

SoundMaster::SoundMaster()
{
	FMOD::System_Create(&m_pSystem);

	if (nullptr != m_pSystem)
		m_pSystem->init(32, FMOD_INIT_NORMAL, NULL);

	LoadSong("EmeraldSword", "Audio/02 Emerald Sword.mp3");
	LoadSong("IfYouWantMe", "Audio/02. If You Want Me.mp3");
	LoadSong("30Minutes", "Audio/04 30 Minutes.mp3");
	LoadSong("ThisIsTheMoment", "Audio/14 This Is The Moment.mp3");
	LoadSong("BadGuy", "Audio/Billie Eilish - bad guy.mp3");
}

SoundMaster::~SoundMaster()
{
	SOUND_MAP::iterator iter;
	for (iter = m_mapSounds.begin(); iter != m_mapSounds.end(); ++iter)
	{
		if (nullptr != iter.second().sound)
			iter.second().sound->release();
	}
	m_mapSounds.clear();

	if (nullptr != m_pSystem)
	{
		m_pSystem->close();
		m_pSystem->release();
	}
}

void SoundMaster::LoadSong(std::string tag, std::string path)
{
	if (nullptr == m_pSystem)
		return;

	bool isFound = false;
	SOUND_MAP::iterator iter;
	for (iter = m_mapSounds.begin(); iter != m_mapSounds.end(); ++iter)
	{
		if (iter.first() == tag)
			isFound = true;
	}
	if (isFound)
		return;

	FMOD::Sound* pSound = nullptr;
	m_pSystem->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &pSound);

	if (nullptr == pSound)
		return;

	sSound newSound;
	newSound.sound = pSound;

	m_mapSounds.insert(tag, newSound);
}

void SoundMaster::PlaySong(std::string tag)
{
	FMOD::Sound* pSound = nullptr;
	SOUND_MAP::iterator iter;
	for (iter = m_mapSounds.begin(); iter != m_mapSounds.end(); ++iter)
	{
		if (iter.first() == tag)
		{
			pSound = iter.second().sound;
			break;
		}
	}

	if (nullptr == pSound)
		return;

	FMOD::Channel* pChannel;
	m_pSystem->playSound(pSound, nullptr, false, &pChannel);
	iter.second().channel = pChannel;
}

void SoundMaster::StopSong(std::string tag)
{
	FMOD::Channel* pChannel = nullptr;
	SOUND_MAP::iterator iter;
	for (iter = m_mapSounds.begin(); iter != m_mapSounds.end(); ++iter)
	{
		if (iter.first() == tag)
		{
			pChannel = iter.second().channel;
			break;
		}
	}

	if (nullptr == pChannel)
		return;

	pChannel->stop();
	pChannel = nullptr;
}
