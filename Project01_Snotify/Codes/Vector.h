#ifndef _VECTOR_H_
#define _VECTOR_H_

template <typename T>
class vector
{
public:
	class iterator
	{
	private:
		T* arr = nullptr;
		int index = 0;
		iterator(int idx, T* dataArr) { index = idx; arr = dataArr; }
	public:
		T& operator *() { return arr[index]; };
		bool operator ==(const iterator& iter) const { return index == iter.index; }
		bool operator !=(const iterator& iter) const { return index != iter.index; }
		iterator& operator ++() { index++; return *this; }
		iterator& operator ++(int val) { iterator temp(index, arr); index++; return temp; }
		iterator& operator --() { index--; return *this; }
		iterator& operator --(int val) { iterator temp(index, arr); index--; return temp; }
		friend class vector;
	};

private:
	static const int DEFAULT_SIZE = 32;
	T* arr;
	int dataCount;
	int dataCapacity;

public:
	vector(int size = DEFAULT_SIZE)
	{
		arr = new T[size];
		dataCount = 0;
		dataCapacity = size;
	}
	vector(const vector& rhs)
	{
		arr = new T[rhs.dataCapacity];
		dataCount = rhs.dataCount;
		dataCapacity = rhs.dataCapacity;
		for (int i = 0; i < dataCount; ++i)
			arr[i] = rhs.arr[i];
	}
	~vector()
	{
		delete[] arr;
	}
	int size() const { return dataCount; }
	bool empty() const { return dataCount == 0; }
	int capacity() const { return dataCapacity; }
	iterator begin() { return iterator(0, arr); }
	iterator end() { return iterator(dataCount, arr); }
	vector& operator=(const vector& rhs)
	{
		if (this != &rhs)
		{
			if (dataCapacity != rhs.dataCapacity)
			{
				delete[] arr;
				dataCapacity = rhs.dataCapacity;
				arr = new T[dataCapacity];
			}
			dataCount = rhs.dataCount;
			for (int i = 0; i < dataCount; ++i)
				arr[i] = rhs.arr[i];
		}
		return *this;
	}
	T& operator[](int idx)
	{
		return arr[idx];
	}
	int ceiling(float num)
	{
		int iNum = (int)num;
		if (num == (float)iNum)
			return iNum;
		return iNum + 1;
	}
	void push_back(const T& data)
	{
		if (dataCount >= dataCapacity)
			resize(ceiling(dataCapacity * 1.5f));

		arr[dataCount++] = data;
	}
	void pop_back()
	{
		dataCount = dataCount > 0 ? dataCount - 1 : 0;
	}
	iterator erase(iterator& where)
	{
		if (0 == dataCount)
			return where;

		int eraseIndex = where.index;
		memcpy(arr + eraseIndex, arr + eraseIndex + 1, sizeof(T) * (dataCapacity - eraseIndex - 1));
		--dataCount;
		return --where;
	}
	void erase(unsigned int idx)
	{
		if (0 == dataCount)
			return;

		memcpy(arr + idx, arr + idx + 1, sizeof(T) * (dataCapacity - idx - 1));
		--dataCount;
		return;
	}
	void resize(int size, T val = T())
	{
		T* newArr = new T[size];
		dataCount = dataCount >= size ? size : dataCount;
		dataCapacity = size;
		//std::memset(newArr, 0, sizeof(T) * dataCapacity);
		//std::memcpy(newArr, arr, sizeof(T) * dataCount);
		for (int i = 0; i < dataCount; ++i)
			newArr[i] = arr[i];
		delete[] arr;
		arr = newArr;
	}
	void reserve(int size)
	{
		if (size <= dataCapacity)
			return;

		T* newArr = new T[size];
		//std::memset(newArr, 0, sizeof(T) * size);
		//std::memcpy(newArr, arr, sizeof(T) * dataCount);
		for (int i = 0; i < dataCount; ++i)
			newArr[i] = arr[i];
		delete[] arr;
		arr = newArr;
		dataCapacity = size;
	}
	void clear()
	{
		dataCount = 0;
	}
};

#endif //_VECTOR_H_