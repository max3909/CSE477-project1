#include "stdafx.h"
#include "Instrument.h"


CInstrument::CInstrument()
{
	sends[0] = 1;
	sends[1] = 0;
	sends[2] = 0;
	sends[3] = 0;
	sends[4] = 0;
	sends[5] = 0;
}

// Constructor to set the beats per minute
CInstrument::CInstrument(double bpm)
{
	m_bpm = bpm;
	sends[0] = 1;
	sends[1] = 0;
	sends[2] = 0;
	sends[3] = 0;
	sends[4] = 0;
	sends[5] = 0;
}

CInstrument::~CInstrument()
{
}
