#include "cPersonGenerator.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>

#include "Functions.h"
using namespace std;

cPersonGenerator::cPersonGenerator()
{
}
cPersonGenerator::~cPersonGenerator()
{
	m_vecFemaleNames.clear();
	m_vecMaleNames.clear();
	m_vecSurnames.clear();
	m_vecStreets.clear();
}

bool cPersonGenerator::LoadCensusFiles(
	std::string babyNameFile,
	std::string surnameFile,
	std::string streetNameFile,
	std::string& errorString)
{
	// TODO: Put YOUR amazing code here!
	return readFirstNameFile(babyNameFile, errorString)
		&& readSurnameFile(surnameFile, errorString)
		&& readStreetFile(streetNameFile, errorString);
}

unsigned int cPersonGenerator::getNumberOfNamesLoaded(void)
{
	return m_vecFemaleNames.size() + m_vecMaleNames.size();
}
unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void)
{
	return m_vecSurnames.size();
}
unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void)
{
	return m_vecStreets.size();
}

cPerson* cPersonGenerator::generateRandomPerson(void)
{
	cPerson* pPerson = new cPerson();

	// GENDER
	// MALE: 40%, FEMALE: 40%, NON_BINARY: 10%, RATHER_NOT_SAY_UNKNOWN: 10%
	int randNum = GetRandNum(0, 99);
	if (randNum < 40) //0~39
		pPerson->gender = cPerson::eGenderType::MALE;
	else if (randNum >= 40 && randNum < 80) //40~79
		pPerson->gender = cPerson::eGenderType::FEMALE;
	else if (randNum >= 80 && randNum < 90) //80~89
		pPerson->gender = cPerson::eGenderType::NON_BINARY;
	else //90~99
		pPerson->gender = cPerson::eGenderType::RATHER_NOT_SAY_UNKNOWN;

	// AGE
	// 1 ~ 100
	pPerson->age = GetRandNum(1, 100);

	// NAME
	switch (pPerson->gender)
	{
	case cPerson::eGenderType::MALE:
		SetFirstMiddleMaleName(pPerson);
		break;
	case cPerson::eGenderType::FEMALE:
		SetFirstMiddleFemaleName(pPerson);
		break;
	case cPerson::eGenderType::NON_BINARY:
	case cPerson::eGenderType::RATHER_NOT_SAY_UNKNOWN:
		randNum = GetRandNum(0, 1);
		if (0 == randNum)
			SetFirstMiddleMaleName(pPerson);
		else
			SetFirstMiddleFemaleName(pPerson);
		break;
	}
	randNum = GetRandNum_Big(0, m_vecSurnames.size() - 1);
	pPerson->last = m_vecSurnames[randNum].surname;

	// ADDRESS
	randNum = GetRandNum_Big(0, m_vecStreets.size() - 1);
	pPerson->streetName = m_vecStreets[randNum].streetName;
	pPerson->streetType = m_vecStreets[randNum].streetType;
	pPerson->streetDirection = m_vecStreets[randNum].streetDirection;
	
	pPerson->streetNumber = randNum;
	GetRandomExtraInformation(pPerson);

	return pPerson;
}

bool cPersonGenerator::readFirstNameFile(string filePath, string& errorString)
{
	ifstream namesFile(filePath);
	if (!namesFile.is_open())
	{
		errorString = "Failed to open the first name data file.";
		return false;
	}

	int totalNum = 0;
	string nextLine;
	unsigned int tokenCount = 0;
	getline(namesFile, nextLine); //first line
	while (getline(namesFile, nextLine))
	{
		stringstream sLine(nextLine);
		string token;
		sFirstName name;
		tokenCount = 0;
		while (getline(sLine, token, ','))
		{
			switch (tokenCount)
			{
			case 0:
				name.name = token;
				break;
			case 1:
				name.gender = token;
				break;
			}
			tokenCount++;

			if (tokenCount > 1)
				break;
		}

		if (name.gender == "F")
			m_vecFemaleNames.push_back(name);
		else
			m_vecMaleNames.push_back(name);
	}

	return true;
}
bool cPersonGenerator::readSurnameFile(string filePath, string& errorString)
{
	ifstream namesFile(filePath);
	if (!namesFile.is_open())
	{
		errorString = "Failed to open the surname data file.";
		return false;
	}

	int totalnum = 0;
	string nextLine;
	unsigned int tokenCount = 0;
	getline(namesFile, nextLine); //first line
	int lineNum = 0;
	while (getline(namesFile, nextLine))
	{
		stringstream sLine(nextLine);
		string token;
		sSurname name;

		getline(sLine, token, ',');
		name.surname = token;

		m_vecSurnames.push_back(name);

		lineNum++;
		if (lineNum > 2000)
			break;
	}

	return true;
}
bool cPersonGenerator::readStreetFile(string filePath, string& errorString)
{
	ifstream namesFile(filePath);
	if (!namesFile.is_open())
	{
		errorString = "Failed to open the street data file.";
		return false;
	}

	int totalnum = 0;
	string nextLine;
	unsigned int tokenCount = 0;
	getline(namesFile, nextLine); //first line
	while (getline(namesFile, nextLine))
	{
		stringstream sLine(nextLine);
		string token;
		sStreetInfo street;
		getline(sLine, token, ',');
		tokenCount = 1;
		while (getline(sLine, token, ','))
		{
			switch (tokenCount)
			{
			case 1:
				street.streetName = token;
				break;
			case 2:
				street.streetType = token;
				break;
			case 3:
				street.streetDirection = token;
				break;
			}
			tokenCount++;

			if (tokenCount > 3)
				break;
		}
		m_vecStreets.push_back(street);
	}

	return true;
}

void cPersonGenerator::SetFirstMiddleMaleName(cPerson*& person)
{
	int firstNum = GetRandNum_Big(0, m_vecMaleNames.size() - 1);
	person->first = m_vecMaleNames[firstNum].name;

	int middleNum = firstNum;
	while (firstNum == middleNum)
		middleNum = GetRandNum_Big(0, m_vecMaleNames.size() - 1);
	person->middle = m_vecMaleNames[middleNum].name;
}
void cPersonGenerator::SetFirstMiddleFemaleName(cPerson*& person)
{
	int firstNum = GetRandNum_Big(0, m_vecFemaleNames.size() - 1);
	person->first = m_vecFemaleNames[firstNum].name;

	int middleNum = firstNum;
	while (firstNum == middleNum)
		middleNum = GetRandNum_Big(0, m_vecFemaleNames.size() - 1);
	person->middle = m_vecFemaleNames[middleNum].name;
}
void cPersonGenerator::GetRandomExtraInformation(cPerson*& person)
{
	int randNum = GetRandNum(0, 9);
	string postalCode = "";

	switch (randNum)
	{
	case 0:
		person->province = "Ontario";
		person->city = "Toronto";
		postalCode = "M5V3L9";
		break;
	case 1:
		person->province = "Quebec";
		person->city = "Quebec City";
		postalCode = "G1R2S0";
		break;
	case 2:
		person->province = "Nova Scotia";
		person->city = "Halifax";
		postalCode = "B3J3S9";
		break;
	case 3:
		person->province = "New Brunswick";
		person->city = "Fredericton";
		postalCode = "E3B3X5";
		break;
	case 4:
		person->province = "Manitoba";
		person->city = "Winnipeg";
		postalCode = "R3C0L5";
		break;
	case 5:
		person->province = "British Columbia";
		person->city = "Victoria";
		postalCode = "V8W1B8";
		break;
	case 6:
		person->province = "Prince Edward Island";
		person->city = "Charlottetown";
		postalCode = "C1A4K1";
		break;
	case 7:
		person->province = "Saskatchewan";
		person->city = "Regina";
		postalCode = "S4P4W7";
		break;
	case 8:
		person->province = "Alberta";
		person->city = "Edmonton";
		postalCode = "T6C4L8";
		break;
	case 9:
		person->province = "Newfoundland and Labrador";
		person->city = "St. John's";
		postalCode = "A1A1B3";
		break;
	}

	for (int i = 0; i < postalCode.length(); ++i)
		person->postalCode[i] = postalCode[i];

	person->SIN = GetRandNum_Big(100000000, 999999999);
}

// Here's a simple way to load the comma delimited files:
bool readCSVFile(void)
{
	// Open the file
	std::ifstream namesFile("Names_2010Census.csv");
	if (!namesFile.is_open())
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	// name,rank,count,prop100k,cum_prop100k,pctwhite,pctblack,pctapi,pctaian,pct2prace,pcthispanic
	// SMITH,1,2442977,828.19,828.19,70.9,23.11,0.5,0.89,2.19,2.4
	//
	// - rank is how popular the last name is, like 1st, 2nd, etc.
	// - count is how many people have that last name, so 2,442,977 people have last name "Smith"
	// - prop100k is the ratio per 100,000 people. Smith is 828.19, 
	//            meaning that there's a 828.19 out of 100,000 chance (0.82819% chance)
	//            that someone is named "Smith"

	std::string theLine;

	unsigned int lineCount = 0;
	while (std::getline(namesFile, theLine))
	{
		lineCount++;
		std::stringstream ssLine(theLine);

		std::string token;
		unsigned int tokenCount = 0;
		while (std::getline(ssLine, token, ','))
		{
			if (tokenCount == 0)
			{
				std::cout << token << std::endl;
			}
			// Ignore the other parts of the line
			tokenCount++;
		}
	}

	std::cout << "Lines read = " << lineCount << std::endl;

	return true;
}