#include "stdafx.h"
#include "Chorus.h"


const int QSIZE = 200000;
const double M_PI = 3.14159265359;

CChorus::CChorus()
{
}


CChorus::~CChorus()
{
}

void CChorus::Start()
{
}

bool CChorus::Generate(){
	return true;
}

void CChorus::Process(double *frameIn, double *frameOut){
	// Loop over the channels
	for (int c = 0; c<2; c++)
	{
		m_queue[m_wrloc + c] = frameIn[c];

		// Add output of the queue to the current input
		frameOut[c] = m_dry * frameIn[c] + m_wet * m_queue[m_rdloc + c];
	}

	int chorus = 0.006 + sin(0.25 * 2 * M_PI * m_time) * 0.004;
	m_wrloc = (m_wrloc + 2) % QSIZE;
	m_rdloc = (m_rdloc + 2) % QSIZE;
}

void CChorus::SetNote(CNote *note){
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
		else if (name == "delay"){
			value.ChangeType(VT_R8);

		}
	}

}
