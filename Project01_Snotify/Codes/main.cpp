#include <iostream>
#include "LinkedList.h"


using namespace std;

int main(int argc, char** argv)
{
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
	list.push_front(90);
	list.push_front(100);

	// 100 90 80 70 20 25 30 35 40 50 

	LinkedList<int>::iterator iter = list.begin();
	for (iter = list.begin(); iter != list.end(); ++iter)
	{
		if ((*iter) == 30)
		{
			list.push_next(iter, 35);
			list.push_prev(iter, 25);
		}
	}


	//LinkedList<int>::iterator iter = list.begin();
	for (iter = list.begin(); iter != list.end(); ++iter)
	{
		cout << *iter << endl;
	}

	return 0;
}