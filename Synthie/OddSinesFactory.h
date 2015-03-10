#pragma once
#include "OddSinesInstrument.h"
class COddSinesFactory
{
public:
	COddSinesFactory();
	~COddSinesFactory();

	COddSinesInstrument *CreateInstrument();

	void SetNote(CNote *note);

private:
	double m_amps[4];
};

