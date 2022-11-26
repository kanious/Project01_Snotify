#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>

template <typename T>
class LinkedList
{
private:
	template <typename T>
	class LinkedListNode
	{
	public:
		T data;
		int index = 0;
		LinkedListNode<T>* prev = nullptr;
		LinkedListNode<T>* next = nullptr;
	};

public:
	class iterator
	{
	private:
		LinkedListNode<T>* current;
		iterator(LinkedListNode<T>* iter) { current = iter; }
	public:
		T& operator *() { return current->data; };
		bool operator ==(const iterator& iter) const { return current == iter.current; }
		bool operator !=(const iterator& iter) const { return current != iter.current; }
		iterator& operator ++() { current = current->next; return *this; }
		iterator& operator --() { current = current->prev; return *this; }
		friend class LinkedList;
	};

private:
	int dataCount;
	LinkedListNode<T>* head;
	LinkedListNode<T>* tail;

public:
	LinkedList()
	{
		dataCount = 0;
		head = new LinkedListNode<T>();
		tail = new LinkedListNode<T>();
		head->next = tail;
		tail->prev = head;
	}
	~LinkedList()
	{
		LinkedListNode<T>* node = head;
		LinkedListNode<T>* nextNode = head->next;

		while (node != nullptr)
		{
			nextNode = node->next;
			delete node;
			node = nextNode;
		}
		dataCount = 0;
	}
	void push_back(const T& data)
	{
		LinkedListNode<T>* prevNode = tail->prev;
		LinkedListNode<T>* newNode = new LinkedListNode<T>();
		newNode->data = data;
		prevNode->next = newNode;
		newNode->prev = prevNode;
		newNode->next = tail;
		tail->prev = newNode;
		++dataCount;
	}
	void push_front(const T& data)
	{
		LinkedListNode<T>* nextNode = head->next;
		LinkedListNode<T>* newNode = new LinkedListNode<T>();
		newNode->data = data;
		head->next = newNode;
		newNode->prev = head;
		newNode->next = nextNode;
		nextNode->prev = newNode;
		++dataCount;
	}
	void push_prev(const iterator& iter, const T& data)
	{
		LinkedListNode<T>* currentNode = iter.current;
		LinkedListNode<T>* prevNode = currentNode->prev;
		LinkedListNode<T>* newNode = new LinkedListNode<T>();
		newNode->data = data;
		prevNode->next = newNode;
		newNode->prev = prevNode;
		newNode->next = currentNode;
		currentNode->prev = newNode;
		++dataCount;
	}
	void push_next(const iterator& iter, const T& data)
	{
		LinkedListNode<T>* currentNode = iter.current;
		LinkedListNode<T>* nextNode = currentNode->next;
		LinkedListNode<T>* newNode = new LinkedListNode<T>();
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

		LinkedListNode<T>* lastNode = tail->prev;
		LinkedListNode<T>* prevNode = lastNode->prev;
		prevNode->next = tail;
		tail->prev = prevNode;
		delete lastNode;
		--dataCount;
	}
	void pop_front()
	{
		if (0 == dataCount)
			return;

		LinkedListNode<T>* firstNode = head->next;
		LinkedListNode<T>* nextNode = firstNode->next;
		head->next = nextNode;
		nextNode->prev = head;
		delete firstNode;
		--dataCount;
	}
	iterator pop(iterator& iter)
	{
		if (0 == dataCount)
			return iter;

		LinkedListNode<T>* prevNode = iter.current->prev;
		LinkedListNode<T>* nextNode = iter.current->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		delete iter.current;
		--dataCount;

		return iterator(prevNode);
	}
	void clear()
	{
		LinkedListNode<T>* node = head->next;
		LinkedListNode<T>* nextNode;

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
	int size() const { return dataCount; }
	bool empty() const { return dataCount == 0; }
	iterator begin() { return iterator(head->next); }
	iterator end() { return iterator(tail); }
};

#endif //_LINKEDLIST_H_