#include "cSnotify.h"
#include <string>
#include <sstream>
#include <iostream>
#include "SoundMaster.h"


using namespace std;

void shell_sort_title(cSong*& pArray, unsigned int& size);
void shell_sort_artist(cSong*& pArray, unsigned int& size);
void shell_sort_userID(cPerson*& pArray, unsigned int& size);
void shell_sort_lastname(cPerson*& pArray, unsigned int& size);
void shell_sort_firstname(cPerson*& pArray, unsigned int& size);

cSnotify::cSnotify()
{
	m_mapUsers.clear();
	m_mapSongs.clear();
	m_pSoundMaster = new SoundMaster;
}

cSnotify::~cSnotify()
{
	hash_map<unsigned int, cPerson*>::iterator iterUser;
	for (iterUser = m_mapUsers.begin(); iterUser != m_mapUsers.end(); ++iterUser)
		delete iterUser.second();
	m_mapUsers.clear();

	hash_map<unsigned int, cSong*>::iterator iterSong;
	for (iterSong = m_mapSongs.begin(); iterSong != m_mapSongs.end(); ++iterSong)
		delete iterSong.second();
	m_mapSongs.clear();

	delete m_pSoundMaster;
}

bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString)
{
	errorString = "";
	cPerson* newPerson = new cPerson(pPerson);

	unsigned int userID = newPerson->getSnotifyUniqueUserID();
	bool success = m_mapUsers.insert(userID, newPerson);
	if (!success)
	{
		delete newPerson;
		errorString = "This user is already added.";
		return false;
	}
	return true;
}
bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{
	errorString = "";
	unsigned int userID = pPerson->getSnotifyUniqueUserID();
	unsigned int SINnumber = pPerson->SIN;

	cPerson* findPerson = nullptr;
	bool success = m_mapUsers.find(userID, findPerson);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the user [ID:" << userID << "].";
		errorString = ss.str();
		return false;
	}
	if (SINnumber != findPerson->SIN)
	{
		errorString = "SIN number is not matched.";
		return false;
	}

	findPerson->UpdateInformation(pPerson);
	return true;
}
bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	errorString = "";

	cPerson* findPerson = nullptr;
	bool success = m_mapUsers.find(SnotifyUserID, findPerson);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the user [ID:" << SnotifyUserID << "].";
		errorString = ss.str();
		return false;
	}
	delete findPerson;
	m_mapUsers.remove(SnotifyUserID);

	return true;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{
	errorString = "";
	cSong* newSong = new cSong(pSong);

	unsigned int songID = newSong->getUniqueID();
	bool success = m_mapSongs.insert(songID, newSong);
	if (!success)
	{
		delete newSong;
		errorString = "This song is already added.";
		return false;
	}

	return true;
}
bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	errorString = "";
	unsigned int songID = pSong->getUniqueID();

	cSong* findSong = nullptr;
	bool success = m_mapSongs.find(songID, findSong);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the song [ID:" << songID << "].";
		errorString = ss.str();
		return false;
	}

	findSong->UpdateInformation(pSong);
	return true;
}
bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{
	errorString = "";

	cSong* findSong = nullptr;
	bool success = m_mapSongs.find(UniqueSongID, findSong);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the song [ID:" << UniqueSongID << "].";
		errorString = ss.str();
		return false;
	}
	delete findSong;
	m_mapSongs.remove(UniqueSongID);

	hash_map<unsigned int, cPerson*>::iterator iterUser;
	for (iterUser = m_mapUsers.begin(); iterUser != m_mapUsers.end(); ++iterUser)
		iterUser.second()->RemoveSong(UniqueSongID);

	return true;
}

bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString)
{
	errorString = "";

	cPerson* findPerson = nullptr;
	bool success = m_mapUsers.find(snotifyUserID, findPerson);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the user [ID:" << snotifyUserID << "].";
		errorString = ss.str();
		return false;
	}

	cSong* newSong = new cSong(pNewSong);
	findPerson->AddSong(newSong);

	return true;
}
bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString)
{
	errorString = "";

	cPerson* findPerson = nullptr;
	bool success = m_mapUsers.find(snotifyUserID, findPerson);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the user [ID:" << snotifyUserID << "].";
		errorString = ss.str();
		return false;
	}

	success = findPerson->RemoveSong(SnotifySongID);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the song [ID:" << SnotifySongID << "] in library.";
		errorString = ss.str();
		return false;
	}

	return true;
}

bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating)
{
	cPerson* findPerson = nullptr;
	bool success = m_mapUsers.find(SnotifyUserID, findPerson);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the user [ID:" << SnotifyUserID << "].";
		cout << ss.str() << endl;
		return false;
	}

	success = findPerson->UpdateRateOnSong(songUniqueID, newRating);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the song [ID:" << songUniqueID << "] in library.";
		cout << ss.str() << endl;
		return false;
	}

	return false;
}

cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString)
{
	errorString = "";

	cPerson* findPerson = nullptr;
	bool success = m_mapUsers.find(SnotifyUserID, findPerson);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the user [ID:" << SnotifyUserID << "].";
		cout << ss.str() << endl;
		return nullptr;
	}

	cSong* getSong = nullptr;
	success = findPerson->GetSong(songUniqueID, getSong);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the song [ID:" << songUniqueID << "] in library.";
		cout << ss.str() << endl;
		return nullptr;
	}

	if (nullptr == getSong)
		return nullptr;

	cSong* cloneSong = new cSong(getSong);

	return cloneSong;
}
bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating)
{
	cPerson* findPerson = nullptr;
	bool success = m_mapUsers.find(snotifyUserID, findPerson);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the user [ID:" << snotifyUserID << "].";
		cout << ss.str() << endl;
		return false;
	}

	success = findPerson->GetRating(songUniqueID, songRating);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the song [ID:" << songUniqueID << "] in library.";
		cout << ss.str() << endl;
		return false;
	}

	return true;
}
bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays)
{
	cPerson* findPerson = nullptr;
	bool success = m_mapUsers.find(snotifyUserID, findPerson);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the user [ID:" << snotifyUserID << "].";
		cout << ss.str() << endl;
		return false;
	}

	success = findPerson->GetNumberOfPlays(songUniqueID, numberOfPlays);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the song [ID:" << songUniqueID << "] in library.";
		cout << ss.str() << endl;
		return false;
	}

	return true;
}

cPerson* cSnotify::FindUserBySIN(unsigned int SIN)
{
	hash_map<unsigned int, cPerson*>::iterator iter;
	for (iter = m_mapUsers.begin(); iter != m_mapUsers.end(); ++iter)
	{
		if (iter.second()->SIN == SIN)
			return new cPerson(iter.second());
	}
	return nullptr;
}
cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID)
{
	cPerson* findPerson = nullptr;
	m_mapUsers.find(SnotifyID, findPerson);

	if (nullptr != findPerson)
		return new cPerson(findPerson);

	return nullptr;
}
cSong* cSnotify::FindSong(std::string title, std::string artist)
{
	hash_map<unsigned int, cSong*>::iterator iter;
	for (iter = m_mapSongs.begin(); iter != m_mapSongs.end(); ++iter)
	{
		if (iter.second()->name == title && iter.second()->artist == artist)
			return new cSong(iter.second());
	}
	return nullptr;
}
cSong* cSnotify::FindSong(unsigned int uniqueID)
{
	cSong* findSong = nullptr;
	m_mapSongs.find(uniqueID, findSong);

	if (nullptr != findSong)
		return new cSong(findSong);

	return nullptr;
}

bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	cPerson* findPerson = nullptr;
	bool success = m_mapUsers.find(snotifyUserID, findPerson);
	if (!success)
	{
		stringstream ss;
		ss << "Cannot find the user [ID:" << snotifyUserID << "].";
		cout << ss.str() << endl;
		return false;
	}

	vector<cSong*>* pvecLibrary = findPerson->GetLibrary();
	if (nullptr == pvecLibrary)
	{
		stringstream ss;
		ss << "Failed to get the library information of the user [ID:" << snotifyUserID << "].";
		cout << ss.str() << endl;
		return false;
	}

	sizeOfLibary = pvecLibrary->size();
	pLibraryArray = new cSong[sizeOfLibary]();
	for (unsigned int i = 0; i < sizeOfLibary; ++i)
	{
		pLibraryArray[i] = cSong((*pvecLibrary)[i]);
	}
	return true;
}
bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	bool success = GetUsersSongLibrary(snotifyUserID, pLibraryArray, sizeOfLibary);
	if (!success)
		return false;

	shell_sort_title(pLibraryArray, sizeOfLibary);

	return true;
}
bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	bool success = GetUsersSongLibrary(snotifyUserID, pLibraryArray, sizeOfLibary);
	if (!success)
		return false;

	shell_sort_artist(pLibraryArray, sizeOfLibary);

	return true;
}
bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	sizeOfUserArray = m_mapUsers.size();
	pAllTheUsers = new cPerson[sizeOfUserArray]();

	int index = 0;
	hash_map<unsigned int, cPerson*>::iterator iter;
	for (iter = m_mapUsers.begin(); iter != m_mapUsers.end(); ++iter)
	{
		pAllTheUsers[index] = cPerson(iter.second());
		++index;
	}

	return true;
}
bool cSnotify::GetUsersByID(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	bool success = GetUsers(pAllTheUsers, sizeOfUserArray);
	if (!success)
		return false;

	shell_sort_userID(pAllTheUsers, sizeOfUserArray);

	return true;
}

bool cSnotify::FindUsersFirstName(std::string firstName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	vector<cPerson*> vecFind;

	hash_map<unsigned int, cPerson*>::iterator iter;
	for (iter = m_mapUsers.begin(); iter != m_mapUsers.end(); ++iter)
	{
		if (iter.second()->first == firstName)
			vecFind.push_back(iter.second());
	}

	sizeOfUserArray = vecFind.size();
	pAllTheUsers = new cPerson[sizeOfUserArray]();
	for (unsigned int i = 0; i < sizeOfUserArray; ++i)
	{
		pAllTheUsers[i] = cPerson(vecFind[i]);
	}

	shell_sort_lastname(pAllTheUsers, sizeOfUserArray);

	return true;
}
bool cSnotify::FindUsersLastName(std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	vector<cPerson*> vecFind;

	int index = 0;
	hash_map<unsigned int, cPerson*>::iterator iter;
	for (iter = m_mapUsers.begin(); iter != m_mapUsers.end(); ++iter)
	{
		if (iter.second()->last == lastName)
		{
			vecFind.push_back(iter.second());
			cout << index << endl;
		}
		index++;
	}

	sizeOfUserArray = vecFind.size();
	pAllTheUsers = new cPerson[sizeOfUserArray]();
	for (unsigned int i = 0; i < sizeOfUserArray; ++i)
	{
		pAllTheUsers[i] = cPerson(vecFind[i]);
	}

	shell_sort_firstname(pAllTheUsers, sizeOfUserArray);

	return true;
}
bool cSnotify::FindUsersFirstLastNames(std::string firstName, std::string lastName, cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	vector<cPerson*> vecFind;

	int index = 0;
	hash_map<unsigned int, cPerson*>::iterator iter;
	for (iter = m_mapUsers.begin(); iter != m_mapUsers.end(); ++iter)
	{
		if (iter.second()->first == firstName && iter.second()->last == lastName)
		{
			vecFind.push_back(iter.second());
			cout << index << endl;
		}
		index++;
	}

	sizeOfUserArray = vecFind.size();
	pAllTheUsers = new cPerson[sizeOfUserArray]();
	for (unsigned int i = 0; i < sizeOfUserArray; ++i)
	{
		pAllTheUsers[i] = cPerson(vecFind[i]);
	}

	return true;
}


void insertion_sort_title(cSong*& pArray, int first, int last, int gap)
{
	int j = 0;
	for (int i = first + gap; i < last; i = i + gap)
	{
		cSong save = pArray[i];
		string nameSave = save.name;

		for (j = i - gap; ; j = j - gap)
		{
			if (j < first)
				break;

			cSong current = pArray[j];
			string nameCurrent = current.name;

			if (nameCurrent.size() == 0 || nameSave.size() == 0)
				break;

			bool isBreak = false;
			for (int k = 0; k < nameCurrent.size(); ++k)
			{
				if (nameSave.size() <= k)
				{
					isBreak = true;
					break;
				}

				if (nameCurrent[k] == nameSave[k])
					continue;

				if (nameCurrent[k] <= nameSave[k])
					isBreak = true;

				break;
			}

			if (isBreak)
				break;

			pArray[j + gap] = pArray[j];
		}

		pArray[j + gap] = save;
	}
}
void shell_sort_title(cSong*& pArray, unsigned int& size)
{
	int gap;

	for (gap = size / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0)
			++gap;

		for (int i = 0; i < gap; i++)
		{
			insertion_sort_title(pArray, i, size, gap);
		}
	}
}

void insertion_sort_artist(cSong*& pArray, int first, int last, int gap)
{
	int j = 0;
	for (int i = first + gap; i < last; i = i + gap)
	{
		cSong save = pArray[i];
		string artistSave = save.artist;

		for (j = i - gap; ; j = j - gap)
		{
			if (j < first)
				break;

			cSong current = pArray[j];
			string artistCurrent = current.artist;

			if (artistCurrent.size() == 0 || artistSave.size() == 0)
				break;

			bool isBreak = false;
			for (int k = 0; k < artistCurrent.size(); ++k)
			{
				if (artistSave.size() <= k)
				{
					isBreak = true;
					break;
				}

				if (artistCurrent[k] == artistSave[k])
					continue;

				if (artistCurrent[k] <= artistSave[k])
					isBreak = true;

				break;
			}

			if (isBreak)
				break;

			pArray[j + gap] = pArray[j];
		}

		pArray[j + gap] = save;
	}
}
void shell_sort_artist(cSong*& pArray, unsigned int& size)
{
	int gap;

	for (gap = size / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0)
			++gap;

		for (int i = 0; i < gap; i++)
		{
			insertion_sort_artist(pArray, i, size, gap);
		}
	}
}

void insertion_sort_userID(cPerson*& pArray, int first, int last, int gap)
{
	int j = 0;
	for (int i = first + gap; i < last; i = i + gap)
	{
		cPerson save = pArray[i];

		for (j = i - gap; ; j = j - gap)
		{
			if (j < first)
				break;

			if (pArray[j].getSnotifyUniqueUserID() <= save.getSnotifyUniqueUserID())
				break;

			pArray[j + gap] = pArray[j];
		}

		pArray[j + gap] = save;
	}
}
void shell_sort_userID(cPerson*& pArray, unsigned int& size)
{
	int gap;

	for (gap = size / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0)
			++gap;

		for (int i = 0; i < gap; i++)
		{
			insertion_sort_userID(pArray, i, size, gap);
		}
	}
}

void insertion_sort_lastname(cPerson*& pArray, int first, int last, int gap)
{
	int j = 0;
	for (int i = first + gap; i < last; i = i + gap)
	{
		cPerson save = pArray[i];
		string stringSave = save.last;

		for (j = i - gap; ; j = j - gap)
		{
			if (j < first)
				break;

			cPerson current = pArray[j];
			string stringCurrent = current.last;

			if (stringCurrent.size() == 0 || stringSave.size() == 0)
				break;

			bool isBreak = false;
			for (int k = 0; k < stringCurrent.size(); ++k)
			{
				if (stringSave.size() <= k)
				{
					isBreak = true;
					break;
				}

				if (stringCurrent[k] == stringSave[k])
					continue;

				if (stringCurrent[k] <= stringSave[k])
					isBreak = true;

				break;
			}

			if (isBreak)
				break;

			pArray[j + gap] = pArray[j];
		}

		pArray[j + gap] = save;
	}
}
void shell_sort_lastname(cPerson*& pArray, unsigned int& size)
{
	int gap;

	for (gap = size / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0)
			++gap;

		for (int i = 0; i < gap; i++)
		{
			insertion_sort_lastname(pArray, i, size, gap);
		}
	}
}

void insertion_sort_firstname(cPerson*& pArray, int first, int last, int gap)
{
	int j = 0;
	for (int i = first + gap; i < last; i = i + gap)
	{
		cPerson save = pArray[i];
		string stringSave = save.first;

		for (j = i - gap; ; j = j - gap)
		{
			if (j < first)
				break;

			cPerson current = pArray[j];
			string stringCurrent = current.first;

			if (stringCurrent.size() == 0 || stringSave.size() == 0)
				break;

			bool isBreak = false;
			for (int k = 0; k < stringCurrent.size(); ++k)
			{
				if (stringSave.size() <= k)
				{
					isBreak = true;
					break;
				}

				if (stringCurrent[k] == stringSave[k])
					continue;

				if (stringCurrent[k] <= stringSave[k])
					isBreak = true;

				break;
			}

			if (isBreak)
				break;

			pArray[j + gap] = pArray[j];
		}

		pArray[j + gap] = save;
	}
}
void shell_sort_firstname(cPerson*& pArray, unsigned int& size)
{
	int gap;

	for (gap = size / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0)
			++gap;

		for (int i = 0; i < gap; i++)
		{
			insertion_sort_firstname(pArray, i, size, gap);
		}
	}
}


void cSnotify::PlaySong(cSong* pSong)
{
	if (nullptr == m_pSoundMaster || nullptr == pSong)
		return;

	m_pSoundMaster->PlaySong(pSong->audioTag);
}

void cSnotify::StopSong(cSong* pSong)
{
	if (nullptr == m_pSoundMaster || nullptr == pSong)
		return;

	m_pSoundMaster->StopSong(pSong->audioTag);
}
