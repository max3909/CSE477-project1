#pragma once
#include "Instrument.h"
#include <vector>
#include <cmath>

using std::log10;

class CNoiseGate :
	public CInstrument
{
public:
	CNoiseGate();
	~CNoiseGate();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	void SetDry(double d) { m_dry = d; }
	void SetWet(double w) { m_wet = w; }
	void SetDelay(double dl) { m_delay = dl; }
	void SetThreshold(double t) { m_threshold = t; }
	void SetRange(double r) { m_range = r; }

	void Process(double *frameIn, double *frameOut, double time);
	double AmpToDec(double amp) { return 10 * log10(pow(amp, 2)); }
	double DecToAmp(double dec) { return sqrt(pow(10, (dec / 10))); }

private:
	double  m_time;
	double m_dry;
	double m_wet;
	double m_delay;
	double m_threshold;
	double m_range;
};

