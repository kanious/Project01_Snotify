#include "cSong.h"

unsigned int cSong::m_NEXT_Snotify_UniqueSongID = 10000;

cSong::cSong(cSong* pSong)
{
	this->uniqueID = pSong->getUniqueID();
	UpdateInformation(pSong);
}

void cSong::UpdateInformation(cSong* pSong)
{
	this->name = pSong->name;
	this->artist = pSong->artist;
	this->rating = pSong->rating;
	this->numberOfTimesPlayed = pSong->numberOfTimesPlayed;
}

void cSong::SetUniqueID()
{
	uniqueID = m_NEXT_Snotify_UniqueSongID;
	m_NEXT_Snotify_UniqueSongID++;
}