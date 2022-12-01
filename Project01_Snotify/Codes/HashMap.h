#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "HashFunc.h"

const int TABLE_SIZE = 200000;
template <typename Tkey, typename Tvalue>
class hash_map
{
private:
	template <typename Tkey, typename Tvalue>
	class hashNode
	{
	public:
		Tkey key;
		Tvalue value;
		hashNode* prev;
		hashNode* next;
		hashNode* keyNext;
		hashNode()
			: prev(nullptr), next(nullptr), keyNext(nullptr)
		{ }
		hashNode(const Tkey& k, const Tvalue& v)
			: key(k), value(v), prev(nullptr), next(nullptr), keyNext(nullptr)
		{ }
	};

public:
	class iterator
	{
	private:
		hashNode<Tkey, Tvalue>* current;
	public:
		iterator() { current = nullptr; }
		iterator(hashNode<Tkey, Tvalue>* iter) { current = iter; }
		Tkey& first() { return current->key; }
		Tvalue& second() { return current->value; }
		bool operator ==(const iterator& iter) const { return current == iter.current; }
		bool operator !=(const iterator& iter) const { return current != iter.current; }
		iterator& operator++() { current = current->next; return *this; }
		iterator& operator++(int val) { iterator temp(current); current = current->next; return temp; }
		iterator& operator--() { current = current->prev; return *this; }
		iterator& operator--(int val) { iterator temp(current); current = current->prev; return temp; }

		friend class hash_map;
	};

private:
	hashNode<Tkey, Tvalue>** table;
	hashNode<Tkey, Tvalue>* head;
	hashNode<Tkey, Tvalue>* tail;
	int dataCount = 0;

public:
	hash_map()
	{
		table = new hashNode<Tkey, Tvalue>*[TABLE_SIZE]();
		head = new hashNode<Tkey, Tvalue>();
		tail = new hashNode<Tkey, Tvalue>();
		head->next = tail;
		tail->prev = head;
	}
	~hash_map()
	{
		hashNode<Tkey, Tvalue>* node = head;
		hashNode<Tkey, Tvalue>* nextNode = head->next;
		while (node != nullptr)
		{
			nextNode = node->next;
			delete node;
			node = nextNode;
		}
		delete[] table;
	}
	int size() const { return dataCount; }
	bool empty() const { return dataCount == 0; }
	iterator begin() { return iterator(head->next); }
	iterator end() { return iterator(tail); }
	unsigned long hashFunc(const Tkey& key)
	{
		unsigned long hashIndex = CalculateHash<Tkey>(key);
		hashIndex %= TABLE_SIZE;

		return hashIndex;
	}
	bool find(const Tkey& key, Tvalue& value)
	{
		unsigned long hashValue = hashFunc(key);
		hashNode<Tkey, Tvalue>* current = table[hashValue];

		while (current != nullptr)
		{
			if (current->key == key)
			{
				value = current->value;
				return true;
			}
			current = current->next;
		}
		return false;
	}
	bool insert(const Tkey& key, const Tvalue& value)
	{
		unsigned long hashValue = hashFunc(key);
		hashNode<Tkey, Tvalue>* prev = nullptr;
		hashNode<Tkey, Tvalue>* current = table[hashValue];

		while (current != nullptr && current->key != key)
		{
			prev = current;
			current = current->keyNext;
		}

		if (current == nullptr)
		{
			current = new hashNode<Tkey, Tvalue>(key, value);
			if (prev == nullptr)
				table[hashValue] = current;
			else
				prev->keyNext = current;
			dataCount++;

			hashNode<Tkey, Tvalue>* prevNode = tail->prev;
			prevNode->next = current;
			current->prev = prevNode;
			current->next = tail;
			tail->prev = current;
		}
		else
		{
			return false;
			//current->value = value;
		}

		return true;
	}
	bool remove(const Tkey& key)
	{
		unsigned long hashValue = hashFunc(key);
		hashNode<Tkey, Tvalue>* prev = nullptr;
		hashNode<Tkey, Tvalue>* current = table[hashValue];

		while (current != nullptr && current->key != key)
		{
			prev = current;
			current = current->keyNext;
		}

		if (current == nullptr)
			return false;
		else
		{
			if (prev == nullptr)
				table[hashValue] = current->keyNext;
			else
				prev->keyNext = current->keyNext;

			hashNode<Tkey, Tvalue>* prevNode = current->prev;
			hashNode<Tkey, Tvalue>* nextNode = current->next;
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
			delete current;
			dataCount--;
		}
		return true;
	}
	void clear()
	{
		hashNode<Tkey, Tvalue>* node = head->next;
		hashNode<Tkey, Tvalue>* nextNode;

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

#endif //_HASHMAP_H_