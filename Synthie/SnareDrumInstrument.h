#pragma once
#include "Instrument.h"
#include "SweepSineWave.h"
#include "AR.h"
#include <vector>

class CSnareDrumInstrument :
	public CInstrument
{
public:
	CSnareDrumInstrument();
	CSnareDrumInstrument(double bpm);
	virtual ~CSnareDrumInstrument();
public:
	const double NUM_SECS_IN_MINUTE = 60.0;
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_sinewave.SetFreq(f); }
	void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }
	void SetDuration(double d) { m_duration = d; }
	virtual void SetNote(CNote *note);
private:
	CSweepSineWave m_sinewave;
	CAR m_ar;
	double m_duration;
	double m_time;
	int m_wrloc;
	int m_rdloc;
	std::vector<short> m_queue_0;
	std::vector<short> m_queue_1;
};