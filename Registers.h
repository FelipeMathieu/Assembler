#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Memoria.h"

using namespace std;


class Registers
{
private:
	map<string, int> registradores;
	map<string, int> flags;
	map<string, string> registradoresLog;
public:
	Registers();
	void setRegisterValue(string Reg, string value, Memoria *m);
	void setRegisterLogValue(string Reg, string value, Memoria *m);
	int getRegisterValue(string Reg);
	string getRegisterLogValue(string Reg);
	void printRegs();
	void printRegsLog();
	void setZeroFlag(int value);
	void setCarryFlag(int value);
	void setOverFlag(int value);
	void setUnderFlag(int value);
	int getFlagValue(string reg);
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
	}
};

