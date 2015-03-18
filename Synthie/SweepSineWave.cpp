#include "stdafx.h"
#include "SweepSineWave.h"


CSweepSineWave::CSweepSineWave()
{
	m_phase = 0;
	m_amp = 0.1;
	m_freq = 200;
	m_freq_scale = 150;
}


CSweepSineWave::~CSweepSineWave()
{
}

void CSweepSineWave::Start()
{
	m_phase = 0;
	m_freq = 200;
}

bool CSweepSineWave::Generate()
{
	m_frame[0] = m_amp * sin(m_phase * 2 * PI);
	m_frame[1] = m_frame[0];

	m_phase += m_freq * GetSamplePeriod();
	m_freq -= m_freq_scale * GetSamplePeriod();

	return true;
}