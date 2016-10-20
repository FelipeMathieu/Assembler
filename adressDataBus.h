#pragma once

#include "Memoria.h"

class adressDataBus
{
private:
	string dataBus;
public:
	adressDataBus();
	~adressDataBus();
	bool sendAdress(string adress, Memoria *m);
	string getDataBus() {
		return this->dataBus;
	}
};

