#pragma once
#include "Instrument.h"
#include "AR.h"
#include "OddSines.h"

class COddSinesInstrument :
	public CInstrument
{
public:
	COddSinesInstrument();
	~COddSinesInstrument();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	void SetDuration(double d) { m_ar.SetDuration(d); }
	void SetFreq(double f) { m_sines.SetFreq(f); }
	void SetAmplitude(int i, double d) { m_sines.SetAmplitude(i, d); }

private:
	CAR         m_ar;
	COddSines   m_sines;
	double  m_time;
};

