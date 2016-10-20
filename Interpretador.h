#pragma once
#include<vector>
#include<map>
#include<fstream>
#include<sstream>
#include"Memoria.h"

using namespace std;

class Interpretador {
private:
	vector<string> codeOrder;
public:
	void storeObj(string ObjFile, Memoria *memoria);
	vector<string> getCodeOrder() {
		return this->codeOrder;
	}
};