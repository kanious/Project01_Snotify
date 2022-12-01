#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

template <typename T>
class list
{
private:
	//template <typename T>
	class listNode
	{
	public:
		T data;
		int index = 0;
		listNode* prev = nullptr;
		listNode* next = nullptr;
	};

public:
	class iterator
	{
	private:
		listNode* current;
		iterator(listNode* iter) { current = iter; }
	public:
		T& operator *() { return current->data; };
		bool operator ==(const iterator& iter) const { return current == iter.current; }
		bool operator !=(const iterator& iter) const { return current != iter.current; }
		iterator& operator ++() { current = current->next; return *this; }
		iterator& operator ++(int val) { iterator temp(current); current = current->next; return temp; }
		iterator& operator --() { current = current->prev; return *this; }
		iterator& operator --(int val) { iterator temp(current); current = current->prev; return temp; }
		friend class list;
	};

private:
	int dataCount;
	listNode* head;
	listNode* tail;

public:
	list()
	{
		dataCount = 0;
		head = new listNode();
		tail = new listNode();
		head->next = tail;
		tail->prev = head;
	}
	~list()
	{
		listNode* node = head;
		listNode* nextNode = head->next;

		while (node != nullptr)
		{
			nextNode = node->next;
			delete node;
			node = nextNode;
		}
		dataCount = 0;
	}
	int size() const { return dataCount; }
	bool empty() const { return dataCount == 0; }
	iterator begin() { return iterator(head->next); }
	iterator end() { return iterator(tail); }
	void push_back(const T& data)
	{
		listNode* prevNode = tail->prev;
		listNode* newNode = new listNode();
		newNode->data = data;
		prevNode->next = newNode;
		newNode->prev = prevNode;
		newNode->next = tail;
		tail->prev = newNode;
		++dataCount;
	}
	void push_front(const T& data)
	{
		listNode* nextNode = head->next;
		listNode* newNode = new listNode();
		newNode->data = data;
		head->next = newNode;
		newNode->prev = head;
		newNode->next = nextNode;
		nextNode->prev = newNode;
		++dataCount;
	}
	void push_prev(const iterator& iter, const T& data)
	{
		listNode* currentNode = iter.current;
		listNode* prevNode = currentNode->prev;
		listNode* newNode = new listNode();
		newNode->data = data;
		prevNode->next = newNode;
		newNode->prev = prevNode;
		newNode->next = currentNode;
		currentNode->prev = newNode;
		++dataCount;
	}
	void push_next(const iterator& iter, const T& data)
	{
		listNode* currentNode = iter.current;
		listNode* nextNode = currentNode->next;
		listNode* newNode = new listNode();
		newNode->data = data;
		currentNode->next = newNode;
		newNode->prev = currentNode;
		newNode->next = nextNode;
		nextNode->prev = newNode;
		++dataCount;
	}
	void pop_back()
	{
		if (0 == dataCount)
			return;

		listNode* lastNode = tail->prev;
		listNode* prevNode = lastNode->prev;
		prevNode->next = tail;
		tail->prev = prevNode;
		delete lastNode;
		--dataCount;
	}
	void pop_front()
	{
		if (0 == dataCount)
			return;

		listNode* firstNode = head->next;
		listNode* nextNode = firstNode->next;
		head->next = nextNode;
		nextNode->prev = head;
		delete firstNode;
		--dataCount;
	}
	iterator erase(iterator& iter)
	{
		if (0 == dataCount)
			return iter;

		listNode* prevNode = iter.current->prev;
		listNode* nextNode = iter.current->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		delete iter.current;
		--dataCount;

		return iterator(prevNode);
	}
	void clear()
	{
		listNode* node = head->next;
		listNode* nextNode;

		while (dataCount != 0)
		{
			nextNode = node->next;
			delete node;
			node = nextNode;
			--dataCount;
		}

		head->next = tail;
		tail->prev = head;
	}
};

#endif //_LINKEDLIST_H_