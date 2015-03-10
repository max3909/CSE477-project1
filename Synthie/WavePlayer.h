#pragma once
#include "AudioNode.h"
class CWavePlayer :
	public CAudioNode
{
public:
	CWavePlayer();
	~CWavePlayer();

public:
	virtual void Start();
	virtual bool Generate();

	void SetSamples(short *s, int n) { m_samples = s; m_numsamples = n; }

private:
	short *m_samples;
	int    m_numsamples;
	int    m_position;

};

