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
	public CAudioNode
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

	void SquareWave(double time);
	void SawtoothWave(double time);

	void SetFrequency(double f) { m_freq = f; }

private:
	double m_freq; //< frequency of wave

	std::vector<short> m_queue_x;
	std::vector<short> m_queue_y;
	int m_wrloc = 0;
	int m_rdloc = 0;
};

