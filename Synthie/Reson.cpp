/**
 * \file Reson.cpp
 *
 * \author Scott Holzknecht
 */

#include "stdafx.h"
#include "Reson.h"
#include "Notes.h"

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
	outframe[0] = A * m_frame[0] + (2 * R * costheta) * m_queue_0[(m_wrloc + QUEUESIZE - 1) % QUEUESIZE] - R * R * m_queue_0[(m_wrloc + QUEUESIZE - 2) % QUEUESIZE];
	outframe[1] = A * m_frame[1] + (2 * R * costheta) * m_queue_1[(m_wrloc + QUEUESIZE - 1) % QUEUESIZE] - R * R * m_queue_1[(m_wrloc + QUEUESIZE - 2) % QUEUESIZE];

	m_frame[0] = RangeBound(outframe[0]);
	m_frame[1] = RangeBound(outframe[1]);

	m_queue_0[m_wrloc] = m_frame[0];
	m_queue_1[m_wrloc] = m_frame[1];
	return !(m_phase / (2 * PI) >= m_duration);
}

void CReson::SetNote(CNote *note)
{
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			m_duration = value.dblVal;
		}
		else if (name == "note")
		{
			m_freq = (NoteToFrequency(value.bstrVal));
		}
	}
}