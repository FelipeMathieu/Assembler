#include "adressDataBus.h"

adressDataBus::adressDataBus()
{
}

adressDataBus::~adressDataBus()
{
}

bool adressDataBus::sendAdress(string adress, Memoria *m) {
	this->dataBus = m->getValue(adress);
	if (this->dataBus != "ERRO") {
		return true;
	}
	else {
		return false;
	}
}
