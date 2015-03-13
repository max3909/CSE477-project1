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
	m_freq = 1000;
}


CSubtractive::~CSubtractive()
{
}

void CSubtractive::SquareWave(double time)
{
	int num_harmonics = m_sampleRate / (2 * m_freq);
	double sample = 0;
	for (int i = 1; i < num_harmonics; i = i + 2)
	{
		sample = sample + 3200 * (1 / i) * sin(time * 2 * PI * (i*m_freq));
	}
	m_frame[0] = m_frame[1] = sample;
}

void CSubtractive::SawtoothWave(double time)
{
	int num_harmonics = m_sampleRate / (2 * m_freq);
	long sample = 0;
	for (int i = 1; i < num_harmonics; i++)
	{
		sample = sample + 3200 * (1 / i) * sin(time * 2 * PI * (i*m_freq));
	}
	m_frame[0] = m_frame[1] = sample;
}