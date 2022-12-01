#ifndef _HASHFUNC_H_
#define _HASHFUNC_H_

#include <string>

template<typename T> static unsigned long CalculateHash(const T& key);
template<> static unsigned long CalculateHash(const std::string& key)
{
	const char* cKey = key.c_str();
	unsigned long hashedValue = 0;
	int index = 0;
	int shift = 0;

	while (cKey[index] != '\0')
	{
		if (shift == 32)
			shift = 0;
		hashedValue += ((int)cKey[index++]) << shift;
		shift += 8;
	}
	return hashedValue;
}
template<> static unsigned long CalculateHash(const float& key)
{
	return (unsigned long)key;
}
template<> static unsigned long CalculateHash(const int& key)
{
	return (unsigned long)key;
}
template<> static unsigned long CalculateHash(const unsigned int& key)
{
	return (unsigned long)key;
}

#endif //_HASHFUNC_H_
