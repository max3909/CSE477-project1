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
	void setSend(int i, double send) { sends[i] = send; }

	double GetSend() { return m_send; }
	void SetSend(double s) { m_send = s; }

private:
	double sends[5];
	double m_send;
};

