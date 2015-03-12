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
	m_freq = 22000;
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
		sample = sample + (1 / i) * sin(time * 2 * 3.1415 * (i*m_freq));
	}
	m_frame[0] = m_frame[1] = sample;
}