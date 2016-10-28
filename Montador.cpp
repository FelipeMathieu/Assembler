#include "Montador.h"

Montador::Montador(Dicionario *D)
{
	this->dicionario = D;
}

Montador::~Montador()
{
}

void Montador::verifyCode(string nmArquivo, Memoria *M) {

	ifstream compilar(nmArquivo);
	ofstream monta;
	string auxString;
	vector<string> auxVector, auxSetVar;
	map<string, string> auxMapInformacoes, auxMapRegistradores, auxMapFlags;
	int aux = 0;
	int i = 0, j = 0, k = 0, auxController = 0;
	string erro = "";
	string auxMont_count = "", auxMont = "";
	string memoryAdress = "";

	if (nmArquivo.substr(nmArquivo.find_last_of(".") + 1) == "cu") {

		if (compilar.is_open()) {

			while (this->controllerCode < 5) {

				switch (this->controllerCode)
				{
					//Le todo o arquivo e armazena linha por linha
				case 0:
					while (getline(compilar, auxString)) {
						this->code[aux] = this->split(auxString);

						for (i; i < this->code[aux].size(); i++) {
							this->code[aux].at(i) = this->filtraPalavra(this->code[aux].at(i));
						}
						i = 0;
						aux += 1;
					}
					i = 0;
					auxString = "";
					aux = 0;
					this->controllerCode += 1;
					compilar.close();
					erro = "";
					break;

					//Salva em uma variavel mont as instru��es
				case 1:
					for (j; j < this->code.size(); j++) {
						if (this->code[0].at(0) != "INICIO" && this->code[0].at(0) != "VAR") {
							erro = "Declaracao de codigo errado!";
						}
						else {
							if (this->code[j].at(0) != "INICIO" && this->code[j].at(0) != "VAR" && this->code[j].at(0) != "FIM") {
								for (k; k < this->code[j].size(); k++) {
									auxString = this->code[j].at(k);
									auxMapInformacoes = this->dicionario->getInstrucoes();
									auxMapRegistradores = this->dicionario->getRegistradores();
									auxMapFlags = this->dicionario->getFlags();

									if (auxMapInformacoes.find(auxString) != auxMapInformacoes.end()) {
										this->mont[auxString] = auxMapInformacoes.find(auxString)->second;
									}
									else if (auxMapRegistradores.find(auxString) != auxMapRegistradores.end()) {
										this->mont[auxString] = auxMapRegistradores.find(auxString)->second;
									}
									else if (auxMapFlags.find(auxString) != auxMapFlags.end()) {
										this->mont[auxString] = auxMapFlags.find(auxString)->second;
									}
									else {
										this->mont[auxString] = "";
									}
									auxString = "";
								}
								k = 0;
							}
							else {
								auxString = this->code[j].at(0);
								auxMapInformacoes = this->dicionario->getInstrucoes();
								this->mont[auxString] = auxMapInformacoes.find(auxString)->second;
							}
						}
					}
					if (erro == "") {
						auxString = "";
						j = 0;
						k = 0;
						this->controllerCode += 1;
						erro = "";
						break;
					}
					else {
						cout << erro << endl;
						this->controllerCode = 10;
						break;
					}

					//Codifica as instru��es
				case 2:
					compilar.open(nmArquivo);
					if (compilar.is_open()) {
						while (getline(compilar, auxString)) {

							auxVector = split(auxString);

							for (j; j < auxVector.size(); j++) {
								auxVector.at(j) = this->filtraPalavra(auxVector.at(j));
							}
							j = 0;
							if (find(auxVector.begin(), auxVector.end(), "INICIO") != auxVector.end()) {
								break;
							}
							else {
								for (j; j < auxVector.size(); j++) {
									if (auxVector.at(j) != "VAR") {
										auxSetVar.push_back(auxVector.at(j));
									}
									else {
										break;
									}
								}
								if (auxSetVar.size() > 2 || auxVector.at(0) == "VAR") {
									if (auxVector.at(0) == "VAR") {
										erro = "";
									}
									else if (auxSetVar.size() > 2) {
										erro = "Informe corretamente as variaveis \n";
										break;
									}
								}
								else {
									if (!this->isInteger(auxSetVar.at(0)) && this->isNum(auxSetVar.at(1))) {
										if (this->mont.find(auxSetVar.at(0)) != this->mont.end()) {
											this->mont[auxSetVar.at(1)] = this->DecToBin(stoi(auxSetVar.at(1), nullptr, 10));
											M->allocaMemoria(this->DecToBin(stoi(auxSetVar.at(1), nullptr, 10)));
											this->mont[auxSetVar.at(0)] = M->getMemoryAdress(this->DecToBin(stoi(auxSetVar.at(1), nullptr, 10)));
											if (!M->setP(auxSetVar.at(0), this->DecToBin(stoi(auxSetVar.at(1), nullptr, 10)))) {
												erro = "Erro ao allocar memoria. Erro com ponteiro ";
											}
										}
									}
									else {
										erro = "Informe corretamente as variaveis e/ou use apenas numeros inteiros \n";
										break;
									}
								}

								j = 0;
							}
							auxSetVar.clear();
							auxString = "";
						}
					}
					if (erro != "") {
						cout << erro << endl;
						this->controllerCode = 10;
						compilar.close();
					}
					else {
						this->controllerCode += 1;
						compilar.close();
						j = 0;
						erro = "";
					}
					break;

					//Varifica se � variavel e assume seus valores
				case 3:
					i = 0;

					if (this->mont.find("INICIO") != this->mont.end() && this->mont.find("FIM") != this->mont.end()) {
						if (this->mont.find("VAR") != this->mont.end()) {
							auxController = 1;

							for (auto& x : this->mont) {

								if (this->isInteger(x.first)) {
									x.second = this->DecToBin(stoi(x.first, nullptr, 10));
								}
								else {
									if (x.second == "") {
										erro = "Declarar corretamente variaveis. Simbolos nao existentes \n";
										break;
									}
								}
							}
						}
						else {
							auxController = 2;

							for (auto& x : this->mont) {

								if (this->isInteger(x.first)) {
									x.second = this->DecToBin(stoi(x.first, nullptr, 10));
								}
								else {
									if (x.second == "") {
										erro = "Declarar corretamente variaveis. Simbolos nao existentes \n";
										break;
									}
								}
							}
						}
					}
					else {
						erro = "Declare o inicio e o fim do codigo \n";
					}


					if (erro != "") {
						cout << erro;
						this->controllerCode = 10;
					}
					else {
						this->controllerCode += 1;
						erro = "";
					}

					break;

					//Escreve o arquivo fonte.
				case 4:
					monta.open("Assembly-" + nmArquivo);
					compilar.open(nmArquivo);
					auxVector.clear();
					auxController = 0;
					j = 0;
					memoryAdress = "";

					if (monta.is_open() && compilar.is_open()) {
						while (getline(compilar, auxString)) {

							auxVector = this->split(auxString);
							i = 0;

							for (i; i < auxVector.size(); i++) {
								auxVector.at(i) = this->filtraPalavra(auxVector.at(i));
							}

							if (find(auxVector.begin(), auxVector.end(), "INICIO") != auxVector.end()) {
								auxController = 2;
							}

							i = 0;

							if (auxController == 2) {
								for (i; i < auxVector.size(); i++) {
									j = auxVector.size() - 1;
									if (i != j) {
										monta << this->mont.find(auxVector.at(i))->second;
										auxMont.append(this->mont.find(auxVector.at(i))->second);
									}
									else {
										if ((auxVector.at(i) == "INICIO" || auxVector.at(i) == "FIM") && i > 0) {
											memoryAdress = M->getMemoryAdress(this->mont[auxVector.at(i)]);
											if (auxMont.size() + memoryAdress.size() == 16) {
												monta << memoryAdress;
												memoryAdress = "";
											}
											else if (auxMont.size() + memoryAdress.size() < 16) {
												for (int l = 0; l < 16 - (auxMont.size() + memoryAdress.size()); l++) {
													auxMont_count.append("0");
												}
												auxMont_count = auxMont_count.append(memoryAdress);

												monta << auxMont_count;
											}
										}
										else {
											if (auxMont.size() + this->mont.find(auxVector.at(i))->second.size() == 16) {
												monta << this->mont.find(auxVector.at(i))->second;
											}
											else if (auxMont.size() + this->mont.find(auxVector.at(i))->second.size() < 16) {
												for (int l = 0; l < 16 - (auxMont.size() + this->mont.find(auxVector.at(i))->second.size()); l++) {
													auxMont_count.append("0");
												}
												auxMont_count = auxMont_count.append(this->mont.find(auxVector.at(i))->second);
												monta << auxMont_count;
											}
										}
									}
								}
								auxMont_count = "";
								auxMont = "";
								monta << endl;
							}
							/*else if (auxController == 1) {
							monta << this->mont.find(auxVector.at(0))->second << endl;
							}*/
						}
					}
					else {
						erro = "Erro ao salvar arquivo";
					}

					if (erro != "") {
						cout << erro << endl;
						this->controllerCode = 10;
						monta.close();
						compilar.close();
					}
					else {
						this->controllerCode += 1;
						monta.close();
						compilar.close();
						erro = "";
					}
					break;

				default:
					break;
				}
			}
		}
	}
	else {
		cout << "Por favor utilize apenas arquivos .cu" << endl;
	}
}


vector<string> Montador::split(const string &s)
{
	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;

	// invariant: we have processed characters [original value of i, i) 
	while (i != s.size())
	{
		// ignore leading blanks
		// invariant: characters in range [original i, current i) are all spaces
		while (i != s.size() && isspace(s[i]))
			++i;

		// find end of next word
		string_size j = i;
		// invariant: none of the characters in range [original j, current j)is a space
		while (j != s.size() && !isspace(s[j]))
			j++;
		// if we found some nonwhitespace characters 
		if (i != j) {
			// copy from s starting at i and taking j - i chars
			ret.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}

string Montador::filtraPalavra(string p)
{
	char chars[] = ",;.:";

	for (unsigned int i = 0; i < strlen(chars); ++i)
	{
		// you need include <algorithm> to use general algorithms like std::remove()
		p.erase(remove(p.begin(), p.end(), chars[i]), p.end());
	}

	// transform(p.begin(), p.end(), p.begin(), tolower);

	return p;
}

bool Montador::isNum(string p)
{
	char chars[] = ",;.: ";
	bool v = true;

	for (unsigned int i = 0; i < strlen(chars); ++i)
	{
		// you need include <algorithm> to use general algorithms like std::remove()
		if (find(p.begin(), p.end(), chars[i]) != p.end()) {
			v = false;
			break;
		}
	}

	// transform(p.begin(), p.end(), p.begin(), tolower);

	return v;
}

inline bool Montador::isInteger(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

string Montador::DecToBin(int number)
{
	if (number == 0) return "0";
	if (number == 1) return "1";

	if (number % 2 == 0)
		return DecToBin(number / 2) + "0";
	else
		return DecToBin(number / 2) + "1";
}
