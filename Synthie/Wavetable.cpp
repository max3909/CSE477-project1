#include "stdafx.h"
#include "Wavetable.h"
#include "Notes.h"
#include "audio/DirSoundSource.h"
#include <string>
CWavetable::CWavetable()
{
	m_duration = .5;
}

CWavetable::CWavetable(double bpm)
{
	m_duration = .5;
	m_bpm = bpm;
	m_numsamples = 0;
	m_samples = NULL;
}

CWavetable::~CWavetable()
{
}

void CWavetable::Start()
{
	//m_ar.SetSource(&m_sinewave);
	m_wavePlayer.SetSampleRate(GetSampleRate());
	m_wavePlayer.Start();
}

bool CWavetable::Generate()
{
	bool valid = m_wavePlayer.Generate();

	m_frame[0] = m_wavePlayer.Frame(0);
	m_frame[1] = m_wavePlayer.Frame(1);
	
	return valid;
}

bool CWavetable::LoadFile(const char *filename)
{
	m_wave.clear();

	CDirSoundSource m_file;
	if (!m_file.Open(filename))
	{
		CString msg = L"Unable to open audio file: ";
		msg += filename;
		AfxMessageBox(msg);
		return false;
	}

	for (int i = 0; i<m_file.NumSampleFrames(); i++)
	{
		short frame[2];
		m_file.ReadFrame(frame);
		m_wave.push_back(frame[0]);
		m_wave.push_back(frame[1]);
	}
	m_sounds.push_back(m_wave);

	m_file.Close();
	return true;
}


void CWavetable::SetNote(CNote *note)
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
			m_wavePlayer.SetDuration(value.dblVal); // play the note for the duration in terms of seconds
			//m_ar.SetDuration(value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm));

		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
			//set something at note
			value.ChangeType(VT_I4);
			m_notevalue = value.intVal;
			
		}
	}
}
CWaveInstrument *CWavetable::CreateInstrument()
{
	CWaveInstrument *instrument = new CWaveInstrument();
	instrument->GetPlayer()->SetSamples(&m_sounds[m_notevalue][0], (int)m_sounds[m_notevalue].size());

	return instrument;
}