#include <iostream>
#include <crtdbg.h>
#include "LinkedList.h"


using namespace std;

int main(int argc, char** argv)
{
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_CrtSetBreakAlloc(156);

	LinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	list.push_back(40);
	list.push_back(50);
	list.push_back(60);
	list.pop_back();
	list.pop_front();
	list.push_front(70);
	list.push_front(80);
	list.push_back(90);
	list.push_back(100);

	LinkedList<int>::iterator iter = list.begin();
	for (iter = list.begin(); iter != list.end(); ++iter)
	{
		if ((*iter) == 30)
		{
			list.push_next(iter, 35);
			list.push_prev(iter, 25);
		}
		else if ((*iter) == 50)
		{
			list.push_next(iter, 55);
			iter = list.pop(iter);
		}
	}

	// 80 70 20 25 30 35 40 55 90 100

	for (iter = list.begin(); iter != list.end(); ++iter)
	{
		cout << *iter << endl;
	}

	return 0;
}