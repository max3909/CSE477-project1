#include "stdafx.h"
#include "NoiseGate.h"

const int QSIZE = 200000;
const double M_PI = 3.14159265359;

CNoiseGate::CNoiseGate()
{
	m_range = 2.25;
	m_threshold = -10;
}


CNoiseGate::~CNoiseGate()
{
}

void CNoiseGate::Start()
{
}

bool CNoiseGate::Generate(){
	return true;
}

void CNoiseGate::Process(double *frameIn, double *frameOut, double time){
	// Loop over the channels
	for (int c = 0; c<2; c++)
	{
		//m_queue[m_wrloc + c] = frameIn[c];
		if (AmpToDec(frameIn[c]) < m_threshold){
			frameOut[c] = m_dry * frameIn[c] + m_wet * (frameIn[c] * m_range);
		}
		// Add output of the queue to the current input
		else{
			frameOut[c] = m_dry* frameIn[c];
		}

	}
}

void CNoiseGate::SetNote(CNote *note){
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
		else if (name == "threshold"){
			value.ChangeType(VT_R8);
			SetThreshold(value.dblVal);
		}
		else if (name == "range") {
			value.ChangeType(VT_R8);
			SetRange(value.dblVal);
		}
		else if (name == "send"){
			value.ChangeType(VT_R8);
			SetSend(value.dblVal);
		}
	}

}