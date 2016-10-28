#pragma once

#include <string>
#include "instructQueue.h"
#include "Memoria.h"
#include "Registers.h"
#include "ULA.h"
#include "busInt.h"

class Decoder
{
private:
	string value;
	string DecToBin(int number);

public:
	Decoder();
	~Decoder();
	void decodeElement(string iq, Memoria *m, busInt *Dbus, Registers *Reg, ULA *ula);
	int bin2dec(const char* binary)
	{
		int len, dec = 0, i, exp;

		len = strlen(binary);
		exp = len - 1;

		for (i = 0; i<len; i++, exp--)
			dec += binary[i] == '1' ? pow(2, exp) : 0;
		return dec;
	}
};