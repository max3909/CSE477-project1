#include "stdafx.h"
#include "SnareDrumInstrument.h"
#include "Notes.h"

#define QUEUESIZE 100000

CSnareDrumInstrument::CSnareDrumInstrument()
{
	m_duration = 0.1;
	m_rdloc = 0;
	m_wrloc = 0;
}

// Constructor to set the beats per minute
CSnareDrumInstrument::CSnareDrumInstrument(double bpm)
{
	m_duration = 0.1;
	m_bpm = bpm;
	m_rdloc = 0;
	m_wrloc = 0;
}

CSnareDrumInstrument::~CSnareDrumInstrument()
{
}

void CSnareDrumInstrument::Start()
{
	/*	m_sinewave.SetSampleRate(GetSampleRate());
	m_sinewave.Start();
	m_time = 0; */
	m_ar.SetSource(&m_sinewave);
	m_ar.SetSampleRate(GetSampleRate());
	m_ar.Start();
	m_queue_0.clear();
	m_queue_1.clear();

	m_queue_0.resize(QUEUESIZE);
	m_queue_1.resize(QUEUESIZE);
	m_rdloc = 0;
	m_wrloc = 0;
}


bool CSnareDrumInstrument::Generate()
{
	// Tell the component to generate an audio sample
	m_sinewave.Generate();

	double f = -.12 + ((double)rand() / RAND_MAX) * (.24);

	// Read the component's sample and make it our resulting frame.
	m_frame[0] = m_sinewave.Frame(0) + f;
	m_frame[1] = m_sinewave.Frame(1) + f;

	// Update time
	m_time += GetSamplePeriod();

	// Tell the component to generate an audio 
	bool valid = m_ar.Generate();
	// Read the component's sample and make it our resulting frame.

	// Update time
	m_time += GetSamplePeriod();

	double const GAIN = 10;
	double R = 1 - 0.01 / 2;
	double costheta = (2 * R * cos(2 * PI * 0.02)) / (1 + pow(R, 2));
	double sintheta = sqrt(1 - pow(costheta, 2));
	double A = (1 - pow(R, 2)) * sintheta;
	A = A * GAIN;

	m_wrloc = (m_wrloc + 1) % QUEUESIZE;

	double outframe[2];
	outframe[0] = A * m_frame[0] + (2 * R * costheta) * m_queue_0[(m_wrloc + QUEUESIZE - 1) % QUEUESIZE] - R * R * m_queue_0[(m_wrloc + QUEUESIZE - 2) % QUEUESIZE];
	outframe[1] = A * m_frame[1] + (2 * R * costheta) * m_queue_1[(m_wrloc + QUEUESIZE - 1) % QUEUESIZE] - R * R * m_queue_1[(m_wrloc + QUEUESIZE - 2) % QUEUESIZE];

	m_frame[0] = RangeBound(outframe[0]);
	m_frame[1] = RangeBound(outframe[1]);

	m_queue_0[m_wrloc] = m_frame[0];
	m_queue_1[m_wrloc] = m_frame[1];

	// We return true until the time reaches the duration returned by the AR object.
	return valid;
}

void CSnareDrumInstrument::SetNote(CNote *note)
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
			// SetDuration(value.dblVal); // play the note for the duration in terms of seconds
			m_ar.SetDuration(value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm));

		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
	}

}