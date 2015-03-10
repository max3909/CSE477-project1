#pragma once
#include "Instrument.h"
#include "WavePlayer.h"
class CWaveInstrument :
	public CInstrument
{
public:
	CWaveInstrument();
	~CWaveInstrument();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	CWavePlayer *GetPlayer() { return &m_wavePlayer; }

private:
	CWavePlayer m_wavePlayer;
};

