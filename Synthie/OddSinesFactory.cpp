#include "stdafx.h"
#include "OddSinesFactory.h"


COddSinesFactory::COddSinesFactory()
{
	for (int i = 0; i<4; i++)
		m_amps[i] = 0.1;
}


COddSinesFactory::~COddSinesFactory()
{
}

COddSinesInstrument *COddSinesFactory::CreateInstrument()
{
	COddSinesInstrument *instrument = new COddSinesInstrument();

	for (int i = 0; i<4; i++)
	{
		instrument->SetAmplitude(i, m_amps[i]);
	}

	return instrument;
}

void COddSinesFactory::SetNote(CNote *note)
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

		if (name == "a1")
		{
			value.ChangeType(VT_R8);
			m_amps[0] = value.dblVal;
		}
		else if (name == "a3")
		{
			value.ChangeType(VT_R8);
			m_amps[1] = value.dblVal;
		}
		else if (name == "a5")
		{
			value.ChangeType(VT_R8);
			m_amps[2] = value.dblVal;
		}
		else if (name == "a7")
		{
			value.ChangeType(VT_R8);
			m_amps[3] = value.dblVal;
		}

	}

}
