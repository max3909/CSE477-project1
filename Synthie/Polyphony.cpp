/**
 * \file Polyphony.cpp
 *
 * \author Scott Holzknecht
 */

#include "stdafx.h"
#include "Polyphony.h"

using namespace std;

CPolyphony::CPolyphony()
{
}


CPolyphony::~CPolyphony()
{
}

void CPolyphony::Start()
{
	CSubtractive::Start();
}

bool CPolyphony::Generate()
{
	long outframe[2];
	for (double note : m_freqs)
	{
		m_freq = note;
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
		outframe[0] = m_frame[0] / m_freqs.size();
		outframe[1] = m_frame[1] / m_freqs.size();
	}
	
	m_phase += 2 * PI * GetSamplePeriod();
	
	m_frame[0] = RangeBound(outframe[0]);
	m_frame[1] = RangeBound(outframe[1]);

	return true;
}