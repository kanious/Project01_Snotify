#pragma warning( disable : 4305 )

#include <iostream>
#include <crtdbg.h>

#include "LinkedList.h"
#include "Vector.h"
#include "HashMap.h"

#include "cPersonGenerator.h"
#include "cPerson.h"
#include "cMusicGenerator.h"
#include "cSong.h"
#include "cSnotify.h"


using namespace std;

void VectorTest()
{
	vector<float> myVector(1);
	myVector.push_back(1.1);
	myVector.push_back(2.2);
	myVector.push_back(3.3);
	myVector.push_back(4.4);
	myVector.push_back(5.5);

	for (int i = 0; i < 100; ++i)
	{
		myVector.push_back(1);
	}


	//vector<float>::iterator iter = myVector.begin();
	//for (iter = myVector.begin(); iter != myVector.end(); ++iter)
	//	cout << *iter << endl;

	vector<float>::iterator iter = myVector.begin();
	++iter;
	++iter;
	myVector.erase(iter);

	//for (int i = 0; i < myVector.size(); ++i)
	//	cout << myVector[i] << endl;

}
void LinkedListTest()
{
	list<int> myList;
	myList.push_back(10);
	myList.push_back(20);
	myList.push_back(30);
	myList.push_back(40);
	myList.push_back(50);
	myList.push_back(60);
	myList.pop_back();
	myList.pop_front();
	myList.push_front(70);
	myList.push_front(80);
	myList.push_back(90);
	myList.push_back(100);

	list<int>::iterator iter = myList.begin();
	for (iter = myList.begin(); iter != myList.end(); ++iter)
	{
		if ((*iter) == 30)
		{
			myList.push_next(iter, 35);
			myList.push_prev(iter, 25);
		}
		else if ((*iter) == 50)
		{
			myList.push_next(iter, 55);
			iter = myList.erase(iter);
		}
	}

	// 80 70 20 25 30 35 40 55 90 100

	for (iter = myList.begin(); iter != myList.end(); ++iter)
	{
		cout << *iter << endl;
	}
}
void HashMapTest()
{
	//hash_map<string, int> myMap;

	//myMap.insert("test", 1);
	//myMap.insert("test2", 2);
	//myMap.insert("test3", 3);
	//myMap.insert("test4", 4);

	//myMap.remove("test3");
	//hash_map<string, int>::iterator iter = myMap.begin();
	//for (iter = myMap.begin(); iter != myMap.end(); ++iter)
	//{
	//	cout << "key: " << iter.first() << ", value: " << iter.second() << endl;
	//}
}



void insertion_sort(string pArray[], int first, int last, int gap)
{
	int j = 0;
	for (int i = first + gap; i < last; i = i + gap)
	{
		string save = pArray[i];

		for (j = i - gap; ; j = j - gap)
		{
			if (j < first)
				break;

			string current = pArray[j];
			if (current.size() == 0 || save.size() == 0)
				break;

			bool isBreak = false;
			for (int k = 0; k < current.size(); ++k)
			{
				if (save.size() <= k)
				{
					isBreak = true;
					break;
				}

				if (current[k] == save[k])
					continue;

				if (current[k] <= save[k])
					isBreak = true;
				
				break;
			}

			if (isBreak)
				break;

			//if (pArray[j] <= save)
			//	break;

			pArray[j + gap] = pArray[j];
		}

		pArray[j + gap] = save;
	}
}
void shell_sort(string pArray[], unsigned int size)
{
	int gap;

	for (gap = size / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0)
			++gap;

		for (int i = 0; i < gap; i++)
		{
			insertion_sort(pArray, i, size, gap);
		}
	}
}

int main(int argc, char** argv)
{
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_CrtSetBreakAlloc(5994418);

	srand((unsigned int)time(NULL));

	//LinkedListTest();
	//VectorTest();
	//HashMapTest();

	//int i;
	//int n = 10;
	//string list[10] = { "eijfq", "difw", "bkdiw", "aaljfde", "otre", "dd", "pbi", "wofj", "jbio", "ceif" };

	//// 셸 정렬 수행
	//shell_sort(list, n);

	//// 정렬 결과 출력
	//for (i = 0; i < n; i++) {
	//	printf("%s\n", list[i].c_str());
	//}

	//return 0;

	string errorString = "";

	cPersonGenerator* PG = new cPersonGenerator();
	if (!PG->LoadCensusFiles("Data/names/yob1880.txt", "Data/Names_2010Census.csv", "Data/Street_Names.csv", errorString))
	{
		cout << errorString << endl;
		delete PG;
		return 1;
	}
	cMusicGenerator* MG = new cMusicGenerator();
	if (!MG->LoadMusicInformation("Data/hot_stuff_2.csv", errorString))
	{
		cout << errorString << endl;
		delete MG;
		return 1;
	}
	cSnotify* snotify = new cSnotify();

	cSong* newSong = MG->getRandomSong();
	snotify->PlaySong(newSong);
	cout << "Song: " << newSong->audioTag << endl;

	char ch = 0;
	while (ch != 'a') {
		cin >> ch;
	}

	snotify->StopSong(newSong);
	delete newSong;


	//string findFirst = "";
	//string findLast = "";
	//for (int i = 0; i < 500; ++i)
	//{
	//	cPerson* newPerson = PG->generateRandomPerson();
	//	if (i == 10)
	//	{
	//		findFirst = newPerson->first;
	//		findLast = newPerson->last;
	//	}
	//	if (i == 100 || i == 200 || i == 300)
	//	{
	//		newPerson->first = findFirst;
	//		newPerson->last = findLast;
	//	}
	//	snotify->AddUser(newPerson, errorString);
	//	delete newPerson;
	//}

	//cPerson* pPeople = nullptr;
	//unsigned int arraySize = 0;
	//snotify->FindUsersFirstLastNames(findFirst, findLast, pPeople, arraySize);


	//for (unsigned int i = 0; i < arraySize; ++i)
	//{
	//	cout << pPeople[i].first << " " << pPeople[i].last << endl;
	//}

	//delete[] pPeople;



	//delete newPerson;
	//delete newSong;
	//delete newSong2;

	delete PG;
	delete MG;
	delete snotify;

	return 0;
}