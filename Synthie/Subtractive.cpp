/**
 * \file Subtractive.cpp
 *
 * \author Scott Holzknecht
 */

#include "stdafx.h"

#include <cmath>
#include "Subtractive.h"

using namespace std;

CSubtractive::CSubtractive()
{
	m_freq = 500;
	m_wavetype = 0;
	m_duration = 0;
}


CSubtractive::~CSubtractive()
{
}

void CSubtractive::SquareWave()
{
	int num_harmonics = m_sampleRate / (2 * m_freq);
	double sample = 0;
	for (int i = 1; i < num_harmonics; i = i + 2)
	{
		sample = sample + 3200 * (1 / i) * sin(m_phase * (i * m_freq));
	}
	m_frame[0] = m_frame[1] = sample;
}

void CSubtractive::SawtoothWave()
{
	int num_harmonics = m_sampleRate / (2 * m_freq);
	long sample = 0;
	for (int i = 1; i < num_harmonics; i++)
	{
		sample = sample + 3200 * (1 / i) * sin(m_phase * (i * m_freq));
	}
	m_frame[0] = m_frame[1] = sample;
}

void CSubtractive::Start()
{
	m_phase = 0;
}

bool CSubtractive::Generate()
{
	switch (m_wavetype)
	{
	case 0:
		SquareWave();
		break;
	case 1:
		SawtoothWave();
		break;
	default:
		break;
	}
	m_phase += 2 * PI * GetSamplePeriod();
	return true;
}