#include "stdafx.h"
#include "RingMod.h"

const double M_PI = 3.14159265359;

CRingMod::CRingMod()
{
	m_sinFreq = 1;
}


CRingMod::~CRingMod()
{
}

void CRingMod::Start()
{
}

bool CRingMod::Generate(){
	return true;
}

void CRingMod::Process(double *frameIn, double *frameOut, double time){
	double sinewave = sin(m_sinFreq * 2 * M_PI * time);
	// Loop over the channels
	for (int c = 0; c<2; c++)
	{
		//m_queue[m_wrloc + c] = frameIn[c];

		// Add output of the queue to the current input
		frameOut[c] = m_dry* frameIn[c] + m_wet * ((sinewave * frameIn[c]));
	}

	/*int flange = 0.006 + sin(0.25 * 2 * M_PI * m_time) * 0.004;
	int delaylength = int((flange*GetSampleRate() + 0.5) * 2);
	m_wrloc = (m_wrloc + 2) % QSIZE;
	m_rdloc = (m_wrloc + QSIZE - delaylength) % QSIZE;*/
}

void CRingMod::SetNote(CNote *note){
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "wet"){
			value.ChangeType(VT_R8);
			SetWet(value.dblVal);
		}
		else if (name == "dry"){
			value.ChangeType(VT_R8);
			SetDry(value.dblVal);
		}
		else if (name == "frequency"){
			value.ChangeType(VT_R8);
			SetSineFreq(value.dblVal);
		}
		else if (name == "send"){
			value.ChangeType(VT_R8);
			SetSend(value.dblVal);
		}
	}

}
