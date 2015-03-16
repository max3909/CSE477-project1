#pragma once
#include "Instrument.h"
#include <vector>
#include <fstream>

using std::ofstream;
using std::endl;
class CFlange :
	public CInstrument
{
public:
	CFlange();
	~CFlange();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);


	void SetDry(double d) { m_dry = d; }
	void SetWet(double w) { m_wet = w; }
	void SetDelay(double dl) { m_delay = dl; }
	

	void Process(double *frameIn, double *frameOut, double time);

private:
	double  m_time;
	double m_dry;
	double m_wet;
	double m_delay;
	
	std::vector<double> m_queue;
	int m_wrloc;
	int m_rdloc;
	ofstream log;
};

