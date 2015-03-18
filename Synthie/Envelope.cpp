/**
* \file Envelope.cpp
*
* \author Scott Holzknecht
*/

#include "stdafx.h"
#include "Envelope.h"
#include "Notes.h"

#define PEAK 1.2

CEnvelope::CEnvelope()
{
	m_attackend = 0;
	m_delayend = 0.001;
	m_releaselen = 0.05;
}


CEnvelope::~CEnvelope()
{
}

void CEnvelope::Start()
{
	CSubtractive::Start();
}

bool CEnvelope::Generate()
{
	CSubtractive::Generate();

	double time = m_phase / (2 * PI);
	double value;

	if (time >= (m_duration - m_releaselen))
	{
		value = (-(time - (m_duration - m_releaselen)) / (m_releaselen)) + 1;
		m_frame[0] *= value;
		m_frame[1] *= value;
	}
	else if (time > m_attackend && time < m_delayend)
	{
		value = PEAK * ((-(time - m_attackend) / (m_delayend - m_attackend)) + 1);
		m_frame[0] *= value;
		m_frame[1] *= value;
	}
	else if (time < m_attackend)
	{
		value = PEAK * (time) / (m_attackend);
		m_frame[0] *= value;
		m_frame[1] *= value;
	}

	return !(time >= m_duration);
}

void CEnvelope::SetNote(CNote *note)
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
		else if (name == "wave")
		{
			value.ChangeType(VT_INT);
			m_wavetype = value.intVal;
		}
		else if (name == "attack")
		{
			value.ChangeType(VT_R8);
			m_attackend = value.dblVal;
		}
		else if (name == "delay")
		{
			value.ChangeType(VT_R8);
			m_delayend = value.dblVal;
		}
		else if (name == "release")
		{
			value.ChangeType(VT_R8);
			m_releaselen = value.dblVal;
		}
	}

	m_delayend += m_attackend;

}