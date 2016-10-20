#include "Decoder.h"

Decoder::Decoder()
{
}

Decoder::~Decoder()
{
}

bool Decoder::decodeElement(instructQueue *iq) {
	this->value = iq->getFirst();

	return true;
}
