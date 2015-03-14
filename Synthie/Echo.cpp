#include "stdafx.h"
#include "Echo.h"

const int QSIZE = 200000;

CEcho::CEcho()
{
	m_queue.resize(QSIZE);
}


CEcho::~CEcho()
{
}

void CEcho::Start()
{
}

bool CEcho::Generate(){
	return true;
}

void CEcho::Process(double *frameIn, double *frameOut){
	//m_dry = 0.25;
	//m_wet = 0.5;
	// Loop over the channels
	for (int c = 0; c<2; c++)
	{
		m_queue[m_wrloc + c] = frameIn[c];

		// Add output of the queue to the current input
		frameOut[c] = m_dry * frameIn[c] + m_wet * m_queue[m_rdloc + c];
	}

	
	m_wrloc = (m_wrloc + 2) % QSIZE;
	m_rdloc = (m_rdloc + 2) % QSIZE;
}

void CEcho::SetNote(CNote *note){
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

