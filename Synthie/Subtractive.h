/**
 * \file Subtractive.h
 *
 * \author Scott Holzknecht
 *
 * \brief Subtractive synth class
 */

#pragma once

#include <vector>
#include "Instrument.h"

/**
 * \brief Subtractive synth class
 */
class CSubtractive :
	public CInstrument
{
public:
	CSubtractive();
	/** \brief Copy constructor disabled */
	CSubtractive(const CSubtractive &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CSubtractive &) = delete;

	virtual ~CSubtractive();

	virtual void Start();
	virtual bool Generate();

	void SquareWave();
	void SawtoothWave();
	void TriangleWave();

	void SetFrequency(double f) { m_freq = f; }

protected:
	double m_freq; //< frequency of wave
	double m_phase;
	short m_wavetype;
	double m_duration;
};
