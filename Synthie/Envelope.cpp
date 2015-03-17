/**
 * \file Envelope.cpp
 *
 * \author Scott Holzknecht
 */

#include "stdafx.h"
#include "Envelope.h"

#define PEAK 1.2

CEnvelope::CEnvelope()
{
	m_attackend = 0;
	m_delayend = 0;
	m_releasestart = 0;
	m_duration = 0;
}


CEnvelope::~CEnvelope()
{
}

void CEnvelope::Start()
{
	CSubtractive::Start();
}

bool CEnvelope::Generate()
{
	CSubtractive::Generate();

	double time = m_phase / (2 * PI);

	if (time >= m_releasestart)
	{
		m_frame[0] *= (time - m_releasestart) / (m_duration - m_releasestart);
		m_frame[1] *= (time - m_releasestart) / (m_duration - m_releasestart);
	}
	else if (time > m_attackend && time < m_delayend)
	{
		m_frame[0] *= PEAK * (time - m_attackend) / (m_delayend - m_attackend);
		m_frame[1] *= PEAK * (time - m_attackend) / (m_delayend - m_attackend);
	}
	else if (time < m_attackend)
	{
		m_frame[0] *= PEAK * (time) / (m_attackend);
		m_frame[1] *= PEAK * (time) / (m_attackend);
	}

	return true;
}