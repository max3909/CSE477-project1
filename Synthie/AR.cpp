#include "stdafx.h"
#include "AR.h"

#include <fstream>

using std::ofstream;
using std::endl;


CAR::CAR()
{
	m_attack = 0.05;
	m_release = 0.05;
}


CAR::~CAR()
{
}

void CAR::Start(){
	m_time = 0;
	m_attack = 0.05;
	m_release = 0.05;
}

bool CAR::Generate(){
	double m_beatduration = m_duration *(1 / (m_bpm / 60));
	if (m_time <= m_attack){
		m_frame[0] = m_source->Frame(0)*(m_time / m_attack);
		m_frame[1] = m_source->Frame(1)*(m_time / m_attack);
	}
	else if (m_time > m_attack && m_time < m_beatduration - m_release){
		m_frame[0] = m_source->Frame(0);
		m_frame[1] = m_source->Frame(1);
	}
	else if (m_time >= m_beatduration - m_release){
		m_frame[0] = m_source->Frame(0)*((m_beatduration - m_time) / m_release);
		m_frame[1] = m_source->Frame(1)*((m_beatduration - m_time) / m_release);
	}

	m_time += GetSamplePeriod();

	if (m_frame[0] == 0){
		m_frame[0] = 0.001;
	}
	if (m_frame[1] == 0){
		m_frame[1] = 0.001;
	}

	return m_time < (m_beatduration);
}

void CAR::SetSource(CAudioNode *new_source){
	m_source = new_source;
}

