#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "WaveInstrument.h"
#include "WavePlayer.h"
#include "AR.h"
#include <vector>
#include <string>
class CDrumWaveTable :
	public CInstrument
{
public:
	CDrumWaveTable();
	CDrumWaveTable(double bpm);
	virtual ~CDrumWaveTable();
public:
	const double NUM_SECS_IN_MINUTE = 60.0;
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_sinewave.SetFreq(f); }
	void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }
	void SetDuration(double d) { m_duration = d; }
	bool LoadFile(const char *filename);
	CWaveInstrument *CreateInstrument();
	virtual void SetNote(CNote *note);
private:
	CSineWave   m_sinewave;
	CAR m_ar;
	CWavePlayer m_wavePlayer;
	double m_duration;
	double m_time;
	int m_notevalue;
	int    m_numsamples;
	short *m_samples;
	std::vector< std::vector<short> > m_sounds;
	std::vector< std::string > m_sound_names;
	std::vector<short> m_wave;
	int		m_pitch;

};