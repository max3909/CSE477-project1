#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "AR.h"
#include <vector>
class CWavetable :
	public CInstrument
{
public:
	CWavetable();
	CWavetable(double bpm);
	virtual ~CWavetable();
public:
	const double NUM_SECS_IN_MINUTE = 60.0;
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_sinewave.SetFreq(f); }
	void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }
	void SetDuration(double d) { m_duration = d; }
	bool LoadFile(const char *filename);

	virtual void SetNote(CNote *note);
private:
	CSineWave   m_sinewave;
	CAR m_ar;
	double m_duration;
	double m_time;
	std::vector< std::vector<short> > m_sounds;
	std::vector<short> m_wave;
};

