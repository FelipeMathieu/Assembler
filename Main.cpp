#include "Montador.h"
#include "Memoria.h"
#include "Interpretador.h"
#include "instructQueue.h"
#include "adressDataBus.h"
#include "Decoder.h"

void main() {
	Dicionario *D = new Dicionario();
	Memoria *memoria = new Memoria(D);
	Montador *montador = new Montador(D);
	Interpretador *it = new Interpretador();
	instructQueue *iQ = new instructQueue();
	adressDataBus *db = new adressDataBus();
	Decoder *dec = new Decoder();


	montador->verifyCode("Teste.cu", memoria);
	montador->getMont();
	memoria->getMemory();
	it->storeObj("Assembly-Teste.cu", memoria);

	iQ->setQueue(it, db, memoria);
	dec->decodeElement(iQ);

	system("pause");
}