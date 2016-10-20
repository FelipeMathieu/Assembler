#pragma once
#include<vector>
#include<map>

using namespace std;

class Dicionario{
private:

	map<string, string> instrucoes;
	map<string, string> registradores;
	map<string, string> flags;
	map<string, string> variveis;

public:
	Dicionario();

	map<string, string> getInstrucoes() {
		return this->instrucoes;
	}

	map<string, string> getRegistradores() {
		return this->registradores;
	}

	map<string, string> getFlags() {
		return this->flags;
	}
};
