#pragma once
#include "Instrument.h"
#include <vector>
class CEcho :
	public CInstrument
{
public:
	CEcho();
	~CEcho();

	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);

	void Process(double *frameIn, double *frameOut);

private:
	double  m_time;
	double m_dry;
	double m_wet;
	std::vector<short> m_queue;
	int m_wrloc;
	int m_rdloc;

};

