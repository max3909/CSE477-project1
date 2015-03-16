/**
 * \file Reson.cpp
 *
 * \author Scott Holzknecht
 */

#include "stdafx.h"
#include "Reson.h"

#define QUEUESIZE 100000

CReson::CReson()
{
	m_wrloc = 0;
	m_rdloc = 0;
}

CReson::~CReson()
{
}

void CReson::Start()
{
	CSubtractive::Start();

	m_queue_0.clear();
	m_queue_1.clear();

	m_queue_0.resize(QUEUESIZE);
	m_queue_1.resize(QUEUESIZE);
	m_wrloc = 0;
	m_rdloc = 0;
}

bool CReson::Generate()
{
	CSubtractive::Generate();

	double const GAIN = 10;
	double R = 1 - 0.01 / 2;
	double costheta = (2 * R * cos(2 * PI * 0.02)) / (1 + pow(R, 2));
	double sintheta = sqrt(1 - pow(costheta, 2));
	double A = (1 - pow(R, 2)) * sintheta;
	A = A * GAIN;

	m_wrloc = (m_wrloc + 1) % QUEUESIZE;

	int outframe[2];
	outframe[0] = A * m_frame[0] + (2 * R * costheta) * m_queue_0[m_wrloc - 1] - R * R * m_queue_0[m_wrloc - 2];
	outframe[1] = A * m_frame[1] + (2 * R * costheta) * m_queue_1[m_wrloc - 1] - R * R * m_queue_1[m_wrloc - 2];

	m_frame[0] = RangeBound(m_frame[0]);

	m_queue_0[m_wrloc] = m_frame[0];
	m_queue_1[m_wrloc] = m_frame[1];
	return true;
}
