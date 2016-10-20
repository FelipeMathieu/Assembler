#pragma once

#include "instructQueue.h"

class Decoder
{
private:
	string value;
public:
	Decoder();
	~Decoder();
	bool decodeElement(instructQueue *iq);
};

