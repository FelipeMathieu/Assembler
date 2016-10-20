#include "Memoria.h"

Memoria::Memoria(Dicionario *D)
{
	this->memory = *new vector<pair<string, pair<string, string>>>(100);
	int i = 0;

	while(i < 32) {
		if (i < 20) {
			for (auto &x : D->getInstrucoes()) {
				this->memory.at(i).first = this->DecToBin(i);
				this->memory.at(i).second.first = x.second;
				i++;
			}
		}
		if (i >= 20 && i < 28) {
			for (auto &x : D->getRegistradores()) {
				this->memory.at(i).first = this->DecToBin(i);
				this->memory.at(i).second.first = x.second;
				i++;
			}
		}
		if (i >= 28) {
			for (auto &x : D->getFlags()) {
				this->memory.at(i).first = this->DecToBin(i);
				this->memory.at(i).second.first = x.second;
				i++;
			}
		}
	}

	for (int j = 35; j < this->memory.size(); j++) {
		this->memory.at(j).first = this->DecToBin(j);
	}
}

Memoria::~Memoria()
{
}

bool Memoria::allocaMemoria(string value) {
	int auxMem = 0, j = 0;
	bool sec = false;
	string auxBin = "";

	srand(time(NULL));

	while (!sec && j < 100) {
		auxMem = rand() % 100;
		if (this->memory.at(auxMem).second.first == "" && auxMem >= 35) {
			this->memory.at(auxMem).second.first = value;
			sec = true;
		}
		else {
			j += 1;
			sec = false;
		}
	}

	if (j >= 100) {
		cout << endl << "Erro de memoria. Memoria insuficiente!" << endl;
		sec = false;
	}

	return sec;
}

string Memoria::DecToBin(int number)
{
	if (number == 0) return "0";
	if (number == 1) return "1";

	if (number % 2 == 0)
		return DecToBin(number / 2) + "0";
	else
		return DecToBin(number / 2) + "1";
}

string Memoria::getMemoryAdress(string value) {
	int j = 0;

	for (int i = 0; i < this->memory.size(); i++) {
		if (this->memory.at(i).second.first == value) {
			j = i;
			break;
		}
	}

	return this->memory.at(j).first;
}

bool Memoria::setP(string value, string toP){
	string i = "";
	if (this->allocaMemoria(this->stringToHex(value))) {
		i = this->getMemoryAdress(toP);
		for (int j = 35; j < this->memory.size(); j++) {
			if (this->memory.at(j).first == this->getMemoryAdress(this->stringToHex(value))) {
				this->memory.at(j).second.second = i;
				return true;
				break;
			}
		}
	}
	else {
		cout << endl << "Erro ao criar ponteiro" << endl;
		return false;
 	}
}

string Memoria::stringToHex(const std::string& input)
{
	static const char* const lut = "0123456789ABCDEF";
	size_t len = input.length();

	std::string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}
	return output;
}

bool Memoria::findInstruction(string element) {
	for (int i = 0; i < 35; i++) {
		if (this->memory.at(i).second.first == element) {
			return true;
			break;
		}
	}
	return false;
}

string Memoria::getValue(string adress) {
	for (int i = 0; i < this->memory.size(); i++) {
		if (this->memory.at(i).first == adress) {
			return this->memory.at(i).second.first;
			break;
		}
	}
	return "ERRO";
}