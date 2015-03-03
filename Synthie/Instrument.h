#pragma once
#include "AudioNode.h"
#include "Note.h"
class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	~CInstrument();

	virtual void SetNote(CNote *note) = 0;
};

