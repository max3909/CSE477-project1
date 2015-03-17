#include "stdafx.h"
#include "WavePlayer.h"


CWavePlayer::CWavePlayer()
{
	m_samples = NULL;
	m_numsamples = 0;
	m_attack = 0.05;
	m_release = 0.05;
}


CWavePlayer::~CWavePlayer()
{
}

void CWavePlayer::Start()
{
	m_position = 0;
	m_time = 0;
	if (m_pitchfactor == NULL || m_pitchfactor < 0)
		m_pitchfactor = 0;
}

void CWavePlayer::UpdatePos()
{
	m_position = m_position + m_pitchfactor + 1;
}

bool CWavePlayer::Generate()
{

	// Read the component's sample and make it our resulting frame.
	if (m_time <  m_attack)
	{
		m_frame[0] = (m_samples[m_position++] / 32768.0) * m_time / m_attack;
		m_frame[1] = (m_samples[m_position] / 32768.0) * m_time / m_attack;
		UpdatePos();
		m_time += GetSamplePeriod();
		return true;
	}
	else if (m_time > m_duration - m_release && m_time < m_duration)
	{
		m_frame[0] = (m_samples[m_position++] / 32768.0) * (m_duration - m_time) / m_release;
		m_frame[1] = (m_samples[m_position] / 32768.0) * (m_duration - m_time) / m_release;
		UpdatePos();
		m_time += GetSamplePeriod();
		return true;
	}
	else
	{

		if (m_position < m_numsamples && m_time < m_duration)
		{
			m_frame[0] = m_samples[m_position++] / 32768.0;
			m_frame[1] = m_samples[m_position] / 32768.0;
			UpdatePos();

			m_time += GetSamplePeriod();
			return true;
		}
		else
		{
			m_frame[1] = m_frame[0] = 0;
			return false;
		}
	}
}
