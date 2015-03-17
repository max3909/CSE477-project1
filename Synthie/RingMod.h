#pragma once
#include "Instrument.h"
class CRingMod :
	public CInstrument
{
public:
	CRingMod();
	~CRingMod();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	void SetDry(double d) { m_dry = d; }
	void SetWet(double w) { m_wet = w; }
	void SetSineFreq(double s) { m_sinFreq = s; }

	void Process(double *frameIn, double *frameOut, double time);

private:
	double  m_time;
	double m_dry;
	double m_wet;
	double m_sinFreq;
};

