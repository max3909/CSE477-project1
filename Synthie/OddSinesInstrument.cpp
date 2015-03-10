#include "stdafx.h"
#include "OddSinesInstrument.h"
#include "Notes.h"


COddSinesInstrument::COddSinesInstrument()
{
}


COddSinesInstrument::~COddSinesInstrument()
{
}

void COddSinesInstrument::Start()
{
	m_ar.SetSampleRate(GetSampleRate());
	m_ar.Start();
	m_time = 0;
	m_sines.SetSampleRate(GetSampleRate());
	m_sines.Start();
	m_ar.SetSource(&m_sines);
}


void COddSinesInstrument::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i<len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			SetDuration(value.dblVal);
		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
		else if (name == "attack")
		{
			value.ChangeType(VT_R8);
			m_ar.SetAttack(value.dblVal);
		}
		else if (name == "release")
		{
			value.ChangeType(VT_R8);
			m_ar.SetRelease(value.dblVal);
		}
	}

}


bool COddSinesInstrument::Generate()
{
	m_sines.Generate();
	bool valid = m_ar.Generate();

	m_frame[0] = m_ar.Frame(0);
	m_frame[1] = m_ar.Frame(1);

	m_time += GetSamplePeriod();
	return valid;
}