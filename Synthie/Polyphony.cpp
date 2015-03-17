/**
 * \file Polyphony.cpp
 *
 * \author Scott Holzknecht
 */

#include "stdafx.h"
#include "Polyphony.h"
#include "Notes.h"
#include <string>

using namespace std;

CPolyphony::CPolyphony()
{
}


CPolyphony::~CPolyphony()
{
}

void CPolyphony::Start()
{
	CSubtractive::Start();
}

bool CPolyphony::Generate()
{
	long outframe[2];
	for (double note : m_freqs)
	{
		m_freq = note;
		switch (m_wavetype)
		{
		case 0:
			SquareWave();
			break;
		case 1:
			SawtoothWave();
			break;
		case 2:
			TriangleWave();
			break;
		default:
			break;
		}
		outframe[0] = m_frame[0] / m_freqs.size();
		outframe[1] = m_frame[1] / m_freqs.size();
	}
	
	m_phase += 2 * PI * GetSamplePeriod();
	
	m_frame[0] = RangeBound(outframe[0]);
	m_frame[1] = RangeBound(outframe[1]);

	return !(m_phase / (2 * PI) >= m_duration);
}

inline vector<wstring> SplitString(wstring s, wstring d)
{
	vector<wstring> r;
	size_t pos = 0;
	while ((pos = s.find(d)) != wstring::npos)
	{
		r.push_back(s.substr(0, pos));
		s.erase(0, pos + d.length());
	}
	return r;
}

void CPolyphony::SetNote(CNote *note)
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
		else if (name == "notes")
		{
			vector<wstring> list = SplitString(value.bstrVal, L",");
			for (wstring ele : list)
			{
				AddFreq(NoteToFrequency(ele.c_str()));
			}
		}
		else if (name == "wave")
		{
			value.ChangeType(VT_INT);
			m_wavetype = value.intVal;
		}
	}
}