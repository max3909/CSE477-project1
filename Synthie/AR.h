#pragma once
#include "AudioNode.h"
class CAR :
	public CAudioNode
{
public:
	CAR();
	~CAR();
private:
	double m_time;
	double m_attack;
	double m_release;
	CAudioNode* m_source;
public:
	double m_duration;
	void SetSource(CAudioNode* const &source) { m_source = source; }
	void SetDuration(double d) { m_duration = d; }
	void SetAttack(double a) { m_attack = a; }
	void SetRelease(double r) { m_release = r; }
	virtual void Start();
	virtual bool Generate();
};

