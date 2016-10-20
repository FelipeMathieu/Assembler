#include"Interpretador.h"

void Interpretador::storeObj(string ObjFile, Memoria *memoria) {
	fstream myFile;
	string str, auxStr;
	vector<string> instrucoes;

	myFile.open(ObjFile);

	if (myFile) {
		while (getline(myFile, str)) {
			if (!memoria->findInstruction(str)) {
				this->codeOrder.push_back(str);
				memoria->allocaMemoria(str);
			}
		}
	}
}