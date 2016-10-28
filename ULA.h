#pragma once

#include <string>
#include "Memoria.h"
#include "Registers.h"

using namespace std;

class ULA
{
private:
	string temporaryReg1;
	string temporaryReg2;
public:
	ULA();
	~ULA();

	void setTempReg1(string element);
	void setTempReg2(string element);
	void add(string reg, Memoria *m, Registers *r);
	void sub(string reg, Memoria *m, Registers *r);
	void mul(string reg, Memoria *m, Registers *r);
	void div(string reg, Memoria *m, Registers *r);
	void not(string reg, Memoria *m, Registers *r);
	void or(string reg, Memoria *m, Registers *r);
	void and(string reg, Memoria *m, Registers *r);
	string DecToBin(int number)
	{
		if (number == 0) return "0";
		if (number == 1) return "1";

		if (number % 2 == 0)
			return DecToBin(number / 2) + "0";
		else
			return DecToBin(number / 2) + "1";
	};
	int bin2dec(const char* binary)
	{
		int len, dec = 0, i, exp;

		len = strlen(binary);
		exp = len - 1;

		for (i = 0; i<len; i++, exp--)
			dec += binary[i] == '1' ? pow(2, exp) : 0;
		return dec;
	};
};

