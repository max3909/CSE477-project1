#pragma once
#include "AudioNode.h"
class CAR :
	public CAudioNode
{
public:
	CAR();
	~CAR();

	void Start();

	bool Generate();

	void SetSource(CAudioNode *new_source);

	void SetDuration(double d) {m_duration = d;}

	void SetTime(double t) { m_time = t; }

private:
	double m_attack;
	double m_release;
	double m_duration;
	double m_time;
	CAudioNode *m_source;
};

