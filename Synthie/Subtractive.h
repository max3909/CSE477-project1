/**
 * \file Subtractive.h
 *
 * \author Scott Holzknecht
 *
 * \brief Subtractive synth class
 */

#pragma once

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

	virtual void Start() {}
	virtual bool Generate() { return false; }
	virtual void SetNote(CNote *note) {}

	void SquareWave(double time);
	void SawtoothWave(double time);

	void SetFrequency(double f) { m_freq = f; }

private:

	double m_freq;

};

