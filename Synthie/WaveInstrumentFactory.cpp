#include "stdafx.h"
#include "WaveInstrumentFactory.h"
#include "audio/DirSoundSource.h"
#include <cmath>



CWaveInstrumentFactory::CWaveInstrumentFactory()
{
	for (double time = 0; time<2; time += 1. / 44100.)
	{
		m_wave.push_back(short(3267 * sin(2 * 3.1415 * 1000 * time)));
	}
}


CWaveInstrumentFactory::~CWaveInstrumentFactory()
{
}

CWaveInstrument *CWaveInstrumentFactory::CreateInstrument()
{
	CWaveInstrument *instrument = new CWaveInstrument();
	instrument->GetPlayer()->SetSamples(&m_wave[0], (int)m_wave.size());

	return instrument;
}

void CWaveInstrumentFactory::SetNote(CNote *note)
{
}

bool CWaveInstrumentFactory::LoadFile(const char *filename)
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
	}

	m_file.Close();
	return true;
}
