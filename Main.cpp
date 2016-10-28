#include "Montador.h"
#include "Memoria.h"
#include "Interpretador.h"
#include "instructQueue.h"
#include "adressDataBus.h"
#include "Decoder.h"
#include "busInt.h"
#include "Registers.h"
#include "ULA.h"

void main() {
	Dicionario *D = new Dicionario();
	Memoria *memoria = new Memoria(D);
	Montador *montador = new Montador(D);
	Interpretador *it = new Interpretador();
	instructQueue *iQ = new instructQueue();
	adressDataBus *db = new adressDataBus();
	Decoder *dec = new Decoder();
	busInt *busI = new busInt();
	Registers *Reg = new Registers ();
	ULA *ula = new ULA();

	montador->verifyCode("Teste.cu", memoria);
	it->storeObj("Assembly-Teste.cu", memoria);

	iQ->setQueue(it, db, memoria);

	system("cls");


	while (it->getCodeOrder().size() - 1 >= iQ->getControllerQueue() ||  !iQ->isEmpty()) {
		if (iQ->isEmpty()) {
			iQ->setQueue(it, db, memoria);
		}

		dec->decodeElement(iQ->getFirst(), memoria, busI, Reg, ula, it, db, iQ);
	}


	system("pause");
}