#pragma once

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <time.h>
#include "Dicionario.h"

using namespace std;

class Memoria
{
private:
	vector<pair<string, pair<string, string>>> memory;
	map<string, string> stackMemory;
	string DecToBin(int number);
	string stringToHex(const std::string& input);

public:
	Memoria(Dicionario *D);
	~Memoria();

	vector<pair<string, pair<string, string>>> getMemory() {
		return this->memory;
	};

	bool allocaMemoria(string value);
	string getMemoryAdress(string value);
	bool setP(string value, string toP);
	bool findInstruction(string element);
	string getValue(string adress);
};

