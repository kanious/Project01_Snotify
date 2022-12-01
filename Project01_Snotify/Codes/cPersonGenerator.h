#ifndef _cPersonGenerator_HG_
#define _cPersonGenerator_HG_

#include <string>
#include "cPerson.h"
#include "Vector.h"

class cPersonGenerator
{
public:
	cPersonGenerator();
	~cPersonGenerator();

	// This takes three files:
	// - One of the "Popular Baby Names" found here: https://www.ssa.gov/oact/babynames/limits.html
	//   (example: "yob2001.txt" which are babies born in the year 2001
	// - The "Names_2010Census.csv" file, from:
	//   "Frequently Occurring Surnames from the 2010 Census" from here:
	//   https://www.census.gov/topics/population/genealogy/data/2010_surnames.html
	// - The "Street_Names.csv" file, from:
	//   "Street Names (San Francisco)" from here: 
	//   https://catalog.data.gov/dataset/street-names-37fec/resource/d655cc82-c98f-450a-b9bb-63521c870503
	// Returns:
	// - true of successful
	// - false if there's any issue (can't find file, or whatever)
	//   If false, then the "errorString" (passed by reference) should be loaded with some sort of 
	//   description of what went wrong (file didn't open, parse issue, Skynet became self aware, etc.)
	//   Use your discretion (and creativity) for this. 
	bool LoadCensusFiles(
		std::string babyNameFile,
		std::string surnameFile,
		std::string streetNameFile,
		std::string& errorString);

	unsigned int getNumberOfNamesLoaded(void);
	unsigned int getNumberOfSurnamesLoaded(void);
	unsigned int getNumberOfStreetsLoaded(void);

	// Randomly generates a person from the data
	// Returns 0, NULL, or nullptr if it can't do this. 
	cPerson* generateRandomPerson(void);


// ���� MyWork ���� //
private:
	struct sFirstName
	{
		std::string name = "";
		std::string gender = "";
	};
	struct sSurname
	{
		std::string surname = "";
	};
	struct sStreetInfo
	{
		std::string streetName = "";
		std::string streetType = "";
		std::string streetDirection = "";
	};
private:
	vector<sFirstName> m_vecMaleNames;
	vector<sFirstName> m_vecFemaleNames;
	vector<sSurname> m_vecSurnames;
	vector<sStreetInfo> m_vecStreets;
	bool readFirstNameFile(std::string filePath, std::string& errorString);
	bool readSurnameFile(std::string filePath, std::string& errorString);
	bool readStreetFile(std::string filePath, std::string& errorString);
	void SetFirstMiddleMaleName(cPerson*& person);
	void SetFirstMiddleFemaleName(cPerson*& person);
	void GetRandomExtraInformation(cPerson*& person);
// ���� MyWork ���� //
};


#endif 
