#pragma once

#include <iostream>
#include <string>
#include "Memoria.h"

using namespace std;

class busInt {
private:
	string data;
public:
	busInt();
	void setDataBus(string value);
	string getDataBus() {
		return this->data;
	}
	void clearBus();
	void printBusInt();
};

