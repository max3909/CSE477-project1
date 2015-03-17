#include "stdafx.h"
#include "WavePlayer.h"


CWavePlayer::CWavePlayer()
{
	m_samples = NULL;
	m_numsamples = 0;
}


CWavePlayer::~CWavePlayer()
{
}

void CWavePlayer::Start()
{
	m_position = 0;
	m_time = 0;
}

bool CWavePlayer::Generate()
{
	if (m_position < m_numsamples && m_time < m_duration)
	{
		m_frame[0] = m_samples[m_position++] / 32768.0;
		m_frame[1] = m_samples[m_position++] / 32768.0;

		m_time += GetSamplePeriod();
		return true;
	}
	else
	{
		m_frame[1] = m_frame[0] = 0;
		return false;
	}
}
