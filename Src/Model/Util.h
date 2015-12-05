#pragma once
#include "BtCommon.h"
#include <cstdint>

float getRandomFloat(float a, float b);
bool getRandomBoolean();
vector<int> getListFromCommaSeparatedString(string str);
vector<string> getListOfStringsFromCommaSeparatedString(string str);
string getFilenameFromPath(string path);
bool getBit(uint32_t n, int index);
void setBit(uint32_t& n, int index, bool isSet);
