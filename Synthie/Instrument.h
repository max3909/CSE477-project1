#pragma once
#include "AudioNode.h"
#include "Note.h"
class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	CInstrument(double);
	virtual ~CInstrument();
	virtual void SetNote(CNote *note) = 0;

public:
	double Send(int i) { return sends[i]; }

private:
	double sends[5];
};

