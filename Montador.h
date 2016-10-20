#pragma once

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <fstream>
#include <minwinbase.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include "Dicionario.h"
#include "Memoria.h"

using namespace std;

class Montador
{
private:
	map<int, vector<string>> code;
	int controllerCode = 0;
	Dicionario *dicionario;
	map<string, string> mont;
	int controllerMemoriaVariaveis = 0;
	
	vector<string> split(const string &s);
	string filtraPalavra(string p);
	bool isNum(string p);
	inline bool isInteger(const std::string & s);
	string DecToBin(int number);

public:
	Montador(Dicionario *D);
	~Montador();

	void verifyCode(string nmArquivo, Memoria *M);

	map<int, vector<string>> getCodigo() {
		return this->code;
	}

	map<string, string> getMont() {
		return this->mont;
	}
};

