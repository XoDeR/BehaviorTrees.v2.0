#include "Util.h"
#include <iostream> // for using stringstream
#include <sstream>

float getRandomFloat(float a, float b) 
{
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

bool getRandomBoolean()
{
	int randomValue = rand() % 2;
	return randomValue == 1 ? true : false;
}

vector<int> getListFromCommaSeparatedString(string str)
{
	vector<int> vect;
	std::stringstream ss(str);
	int i;

	while (ss >> i)
	{
		vect.push_back(i);

		if (ss.peek() == ',')
			ss.ignore();
	}
	return vect;
}

vector<string> getListOfStringsFromCommaSeparatedString(string str)
{
	vector<string> vect;
	std::stringstream ss(str);
	string i;

	while (ss >> i)
	{
		vect.push_back(i);

		if (ss.peek() == ',')
			ss.ignore();
	}
	return vect;
}

string getFilenameFromPath(string path)
{
	unsigned int found = path.find_last_of("/\\");
	return path.substr(found+1);
}

bool getBit(uint32_t n, int index)
{
	return ((n & (1 << index)) > 0);
}

void setBit(uint32_t& n, int index, bool isSet)
{
	if (isSet == true)
	{
		n =  (n | (1 << index));
	}
	else
	{
		int mask = ~(1 << index);
		n =  n & mask;
	}
}