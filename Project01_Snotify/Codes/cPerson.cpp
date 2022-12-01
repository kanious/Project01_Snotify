#include "cPerson.h"
#include "cSong.h"
#include <iostream>

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

cPerson::cPerson()
{
	// In here, set the default information
	this->gender = cPerson::RATHER_NOT_SAY_UNKNOWN;
	this->streetNumber = 0;
	this->age = -1;
	this->SIN = 0;

	// Generate unique Snotify ID
	this->m_Snotify_UniqueUserID = cPerson::m_NEXT_Snotify_UniqueUSerID;
	// Increment for next created user by a small random amount 
	const unsigned int MAX_ID_INCREEMNT = 11;
	
	//cPerson::m_NEXT_Snotify_UniqueUSerID += (rand() % MAX_ID_INCREEMNT);
	cPerson::m_NEXT_Snotify_UniqueUSerID++;
}

// The 1st Snotify user will have ID: 10,000,000
// static 
unsigned int cPerson::m_NEXT_Snotify_UniqueUSerID = 10000000;


cPerson::~cPerson()
{
	for (int i = 0; i < m_vecLibrary.size(); ++i)
		delete m_vecLibrary[i];
	m_vecLibrary.clear();
}

std::string cPerson::getGenderAsString(void)
{
	switch (this->gender)
	{
	case cPerson::MALE:
		return "MALE";
		break;
	case cPerson::FEMALE:
		return "FEMALE";
		break;
	case cPerson::NON_BINARY:
		return "NON_BINARY";
		break;
	case cPerson::RATHER_NOT_SAY_UNKNOWN:
		return "RATHER_NOT_SAY_UNKNOWN";
		break;
//	default:
//		break;
	}

	// This should never happen
//	return "RATHER_NOT_SAY_UNKNOWN";
	return "OMG! CALL THE DEV TEAM!! SOMEONE SCREWED UP!!!";
}

unsigned int cPerson::getSnotifyUniqueUserID(void)
{
	return m_Snotify_UniqueUserID;
}

cPerson::cPerson(cPerson* pPerson)
{
	this->m_Snotify_UniqueUserID = pPerson->getSnotifyUniqueUserID();
	this->SIN = pPerson->SIN;
	UpdateInformation(pPerson);
}

void cPerson::UpdateInformation(cPerson* pPerson)
{
	this->first = pPerson->first;
	this->middle = pPerson->middle;
	this->last = pPerson->last;
	this->gender = pPerson->gender;
	this->age = pPerson->age;
	this->streetNumber = pPerson->streetNumber;
	this->streetName = pPerson->streetName;
	this->streetType = pPerson->streetType;
	this->streetDirection = pPerson->streetDirection;
	this->city = pPerson->city;
	this->province = pPerson->province;
	for (int i = 0; i < 6; ++i)
		this->postalCode[i] = pPerson->postalCode[i];
	this->m_vecLibrary.clear();
	for (int i = 0; i < pPerson->m_vecLibrary.size(); ++i)
		this->m_vecLibrary.push_back(new cSong(pPerson->m_vecLibrary[i]));
}

void cPerson::AddSong(cSong* song)
{
	m_vecLibrary.push_back(song);
}

bool cPerson::RemoveSong(unsigned int songID)
{
	bool isRemoved = false;
	vector<cSong*>::iterator iter = m_vecLibrary.begin();
	for (iter = m_vecLibrary.begin(); iter != m_vecLibrary.end(); ++iter)
	{
		if ((*iter)->getUniqueID() == songID)
		{
			iter = m_vecLibrary.erase(iter);
			isRemoved = true;
		}
	}

	return isRemoved;
}

bool cPerson::UpdateRateOnSong(unsigned int songID, unsigned int newRating)
{
	bool isUpdated = false;
	for (int i = 0; i < m_vecLibrary.size(); ++i)
	{
		if (m_vecLibrary[i]->getUniqueID() == songID)
		{
			m_vecLibrary[i]->rating = newRating;
			isUpdated = true;
		}
	}

	return isUpdated;
}

bool cPerson::GetSong(unsigned int songID, cSong*& song)
{
	bool isFound = false;
	for (int i = 0; i < m_vecLibrary.size(); ++i)
	{
		if (m_vecLibrary[i]->getUniqueID() == songID)
		{
			++m_vecLibrary[i]->numberOfTimesPlayed;
			song = m_vecLibrary[i];
			isFound = true;
		}
	}

	return isFound;
}

bool cPerson::GetRating(unsigned int songID, unsigned int& rating)
{
	for (int i = 0; i < m_vecLibrary.size(); ++i)
	{
		if (m_vecLibrary[i]->getUniqueID() == songID)
		{
			rating = m_vecLibrary[i]->rating;
			return true;
		}
	}

	return false;
}

bool cPerson::GetNumberOfPlays(unsigned int songID, unsigned int& numberOfPlays)
{
	for (int i = 0; i < m_vecLibrary.size(); ++i)
	{
		if (m_vecLibrary[i]->getUniqueID() == songID)
		{
			numberOfPlays = m_vecLibrary[i]->numberOfTimesPlayed;
			return true;
		}
	}

	return false;
}