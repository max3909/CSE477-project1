#include "stdafx.h"
#include "OddSines.h"
#include <cmath>


COddSines::COddSines()
{
	for (int i = 0; i<4; i++)
		m_amp[i] = 1;
}


COddSines::~COddSines()
{
}

void COddSines::Start()
{
	m_phase = 0;
}

bool COddSines::Generate()
{
	double sample = 0;
	for (int i = 0; i<4; i++)
	{
		sample += m_amp[i] * sin(m_phase * (i * 2 + 1));
	}

	m_frame[1] = m_frame[0] = sample;
	m_phase += 2 * PI * m_freq * GetSamplePeriod();

	return true;
}