#include "stdafx.h"
#include "Synthesizer.h"
#include "Instrument.h"
#include "ToneInstrument.h"
#include "OddSinesInstrument.h"
#include "Polyphony.h"
#include "Envelope.h"
#include "xmlhelp.h"
#include <fstream>
#include <vector>
#include <algorithm>

using std::ofstream;
using std::endl;

CSynthesizer::CSynthesizer()
: m_time(0)
{
	CoInitialize(NULL);
	m_channels = 2;
	m_sampleRate = 44100.;
	m_samplePeriod = 1 / m_sampleRate;
	m_bpm = 120;            
	m_beatspermeasure = 4;
	m_secperbeat = 0.5;   
	m_waveinstfactory.LoadFile("drumriff.wav");

	m_wavetable.LoadFile("L1.wav");
	m_wavetable.LoadFile("L2.wav");
	m_wavetable.LoadFile("L3.wav");
	m_wavetable.LoadFile("L4.wav");
	m_wavetable.LoadFile("L5.wav");
	m_wavetable.LoadFile("S1.wav");
	m_wavetable.LoadFile("S2.wav");
	m_wavetable.LoadFile("S3.wav");
	m_wavetable.LoadFile("S4.wav");
	m_wavetable.LoadFile("S5.wav");

	m_drumtable.LoadFile("bass drum.wav");
	m_drumtable.LoadFile("bass drum 2.wav");
	m_drumtable.LoadFile("cymbal.wav");
	m_drumtable.LoadFile("cymbal 2.wav");
	m_drumtable.LoadFile("cymbal 3.wav");
	m_drumtable.LoadFile("cowbell.wav");
	m_drumtable.LoadFile("tom.wav");
	m_drumtable.LoadFile("tom 2.wav");
	m_drumtable.LoadFile("tom 3.wav");

}


CSynthesizer::~CSynthesizer()
{
}

//! Start the synthesizer
void CSynthesizer::Start()
{
	/*m_time = 0;
	CToneInstrument *ti = new CToneInstrument();
	ti->SetSampleRate(GetSampleRate());
	ti->SetFreq(440);
	ti->SetDuration(3);
	ti->Start();
	m_instruments.push_back(ti);*/
	m_instruments.clear();
	m_currentNote = 0;
	m_measure = 0;
	m_beat = 0;
	m_time = 0;
	effectsOn = false;
}


bool CSynthesizer::Generate(double * frame)
{
	/*double sample = 0.1 * sin(2 * PI * 440 * GetTime());

	for (int c = 0; c<GetNumChannels(); c++)
	{
		frame[c] = sample;
	}

	m_time += GetSamplePeriod();
	return m_time < 5;*/

	//
	// Phase 1: Determine if any notes need to be played.
	//
	bool send1 = false;
	bool send2 = false;
	bool send3 = false;
	bool send4 = false;

	double send1value = 0.0;
	double send2value = 0.0;
	double send3value = 0.0;
	double send4value = 0.0;

	while (m_currentNote < (int)m_notes.size())
	{
		// Get a pointer to the current note
		CNote *note = &m_notes[m_currentNote];

		// If the measure is in the future we can't play
		// this note just yet.
		if (note->Measure() > m_measure)
			break;

		// If this is the current measure, but the
		// beat has not been reached, we can't play
		// this note.
		if (note->Measure() == m_measure && note->Beat() > m_beat)
			break;

		//
		// Play the note!
		//

		// Create the instrument object
		CInstrument *instrument = NULL;
		if (note->Instrument() == L"ToneInstrument")
		{
			instrument = new CToneInstrument(GetBeatsPerMinute());
		}
		else if (note->Instrument() == L"OddSines")
		{
			
			m_oddsinesfactory.SetNote(note);
			instrument = m_oddsinesfactory.CreateInstrument();
		}
		else if (note->Instrument() == L"Wave")
		{
			m_waveinstfactory.SetNote(note);
			instrument = m_waveinstfactory.CreateInstrument();
		}
		else if (note->Instrument() == L"Echo")
		{
			m_echo.SetNote(note);
			
		}
		else if (note->Instrument() == L"Chorus")
		{
			m_chorus.SetNote(note);
			send1 = true;
			m_chorus.Start();
			send1value = m_chorus.GetSend();
			
		}
		else if (note->Instrument() == L"Flange")
		{
			m_flange.SetNote(note);
			send2 = true;
			m_flange.Start();
			send2value = m_flange.GetSend();
		}
		else if (note->Instrument() == L"NoiseGate")
		{
			m_noiseGate.SetNote(note);
			send3 = true;
			m_noiseGate.Start();
			send3value = m_noiseGate.GetSend();
		}
		else if (note->Instrument() == L"RingMod")
		{
			m_ringmod.SetNote(note);
			send4 = true;
			m_ringmod.Start();
			send4value = m_ringmod.GetSend();
		}
		else if (note->Instrument() == L"Wavetable")
		{
			m_wavetable.SetNote(note);
			instrument = m_wavetable.CreateInstrument();
		}
		else if (note->Instrument() == L"Drum")
		{
			m_drumtable.SetNote(note);
			instrument = m_drumtable.CreateInstrument();
		}
		else if (note->Instrument() == L"Reson")
		{
			CReson * reson = new CReson();
			instrument = reson;
		}
		else if (note->Instrument() == L"Polyphony")
		{
			CPolyphony * poly = new CPolyphony();
			instrument = poly;
		}
		else if (note->Instrument() == L"Snare")
		{
			CSnareDrumInstrument * snare = new CSnareDrumInstrument();
			instrument = snare;
		}
		else if (note->Instrument() == L"Envelope")
		{
			CEnvelope * env = new CEnvelope();
			instrument = env;
		}

		// Configure the instrument object
		if (instrument != NULL)
		{
			instrument->SetSampleRate(GetSampleRate());
			instrument->SetNote(note);
			instrument->Start();

			m_instruments.push_back(instrument);
		}

		m_currentNote++;
	}
	//
	// Phase 2: Clear all channels to silence 
	//
	double channelframes[5][2];
	for (int i = 0; i<5; i++)
	{
		for (int c = 0; c<GetNumChannels(); c++)
		{
			channelframes[i][c] = 0;
		}
	}
	for (int c = 0; c<GetNumChannels(); c++)
	{
		frame[c] = 0;
	}

	//
	// Phase 3: Play an active instruments
	//

	//
	// We have a list of active (playing) instruments.  We iterate over 
	// that list.  For each instrument we call generate, then add the
	// output to our output frame.  If an instrument is done (Generate()
	// returns false), we remove it from the list.
	//

	for (list<CInstrument *>::iterator node = m_instruments.begin(); node != m_instruments.end();)
	{
		// Since we may be removing an item from the list, we need to know in 
		// advance, what is after it in the list.  We keep that node as "next"
		list<CInstrument *>::iterator next = node;
		next++;

		// Get a pointer to the allocated instrument
		CInstrument *instrument = *node;

		// Call the generate function
		if (instrument->Generate())
		{
			if (send1){
				instrument->setSend(1, send1value);
				effectsOn = true;
			}
			if (send2){
				instrument->setSend(2, send2value);
				effectsOn = true;
			}
			if (send3){
				instrument->setSend(3, send3value);
				effectsOn = true;
			}
			if (send4){
				instrument->setSend(4, send4value);
				effectsOn = true;
			}
			/*for (int c = 0; c<GetNumChannels(); c++)
			{
				frame[c] += instrument->Frame(c);
				
			}*/

			// If we returned true, we have a valid sample.  Add it 
			// to the frame for each channel
			for (int i = 0; i<5; i++)
			{
				for (int c = 0; c<GetNumChannels(); c++)
				{
					
					channelframes[i][c] += instrument->Frame(c) * instrument->Send(i);
				}
			}
		}
		else
		{
			// If we returned false, the instrument is done.  Remove it
			// from the list and delete it from memory.
			m_instruments.erase(node);
			delete instrument;
		}

		// Phase 3a: Effects
		double frames[2];
		for (int c = 0; c < GetNumChannels(); c++){
			frames[c] = channelframes[0][c];
		}


		double cframes[2];
		for (int c = 0; c < 2; c++){
			cframes[c] = 0;
		}

		double fframes[2];
		for (int c = 0; c < 2; c++){
			fframes[c] = 0;
		}
		
		double nframes[2];
		for (int c = 0; c < 2; c++){
			nframes[c] = 0;
		}

		double rframes[2];
		for (int c = 0; c < 2; c++){
			rframes[c] = 0;
		}

		if (channelframes[1][0] != 0){
			m_chorus.Process(channelframes[1], cframes, m_time);
		}
		if (channelframes[2][0] != 0){
			m_flange.Process(channelframes[2], fframes, m_time);
		}
		if (channelframes[3][0] != 0){
			m_noiseGate.Process(channelframes[3], nframes, m_time);
		}
		if (channelframes[4][0] != 0){
			m_ringmod.Process(channelframes[4], rframes, m_time);
		}
		
		for (int c = 0; c < GetNumChannels(); c++){
			if (effectsOn == false){
				frame[c] += frames[c];
			}
			else{
				frame[c] += cframes[c];
				frame[c] += fframes[c];
				frame[c] += nframes[c];
				frame[c] += rframes[c];
			}
			
		}
		

		// Move to the next instrument in the list
		node = next;
	}
	//
	// Phase 4: Advance the time and beats
	//

	// Time advances by the sample period
	m_time += GetSamplePeriod();

	// Beat advances by the sample period divided by the 
	// number of seconds per beat.  The inverse of seconds
	// per beat is beats per second.
	m_beat += GetSamplePeriod() / m_secperbeat;

	// When the measure is complete, we move to
	// a new measure.  We might be a fraction into
	// the new measure, so we subtract out rather 
	// than just setting to zero.
	if (m_beat > m_beatspermeasure)
	{
		m_beat -= m_beatspermeasure;
		m_measure++;
	}
	//
	// Phase 5: Determine when we are done
	//

	// We are done when there is nothing to play.  We'll put something more 
	// complex here later.
	return !m_instruments.empty() || m_currentNote < (int)m_notes.size();
}


// Get the time since we started generating audio
double CSynthesizer::GetTime()
{
	return m_time;
}
void CSynthesizer::Clear()
{
	m_instruments.clear();
	m_notes.clear();
}
void CSynthesizer::XmlLoadScore(IXMLDOMNode * xml)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
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

		if (name == L"bpm")
		{
			value.ChangeType(VT_R8);
			m_bpm = value.dblVal;
			m_secperbeat = 1 / (m_bpm / 60);
		}
		else if (name == L"beatspermeasure")
		{
			value.ChangeType(VT_I4);
			m_beatspermeasure = value.intVal;
		}

	}


	CComPtr<IXMLDOMNode> node;
	xml->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR name;
		node->get_nodeName(&name);
		if (name == L"instrument")
		{
			XmlLoadInstrument(node);
		}
	}
}
void CSynthesizer::OpenScore(CString & filename)
{
	Clear();

	//
	// Create an XML document
	//

	CComPtr<IXMLDOMDocument>  pXMLDoc;
	bool succeeded = SUCCEEDED(CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
		IID_IXMLDOMDocument, (void**)&pXMLDoc));
	if (!succeeded)
	{
		AfxMessageBox(L"Failed to create an XML document to use");
		return;
	}

	// Open the XML document
	VARIANT_BOOL ok;
	succeeded = SUCCEEDED(pXMLDoc->load(CComVariant(filename), &ok));
	if (!succeeded || ok == VARIANT_FALSE)
	{
		AfxMessageBox(L"Failed to open XML score file");
		return;
	}

	//
	// Traverse the XML document in memory!!!!
	// Top level tag is <score>
	//

	CComPtr<IXMLDOMNode> node;
	pXMLDoc->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR nodeName;
		node->get_nodeName(&nodeName);
		if (nodeName == "score")
		{
			XmlLoadScore(node);
		}
	}
	sort(m_notes.begin(), m_notes.end());
}
void CSynthesizer::XmlLoadInstrument(IXMLDOMNode * xml)
{
	wstring instrument = L"";

	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
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

		// Get the value of the attribute.  
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "instrument")
		{
			instrument = value.bstrVal;
		}
	}


	CComPtr<IXMLDOMNode> node;
	xml->get_firstChild(&node);
	for (; node != NULL; NextNode(node))
	{
		// Get the name of the node
		CComBSTR name;
		node->get_nodeName(&name);

		if (name == L"note")
		{
			XmlLoadNote(node, instrument);
		}
	}

}
void CSynthesizer::XmlLoadNote(IXMLDOMNode * xml, std::wstring & instrument)
{
	m_notes.push_back(CNote());
	m_notes.back().XmlLoad(xml, instrument);
}
