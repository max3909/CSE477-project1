/**
 * \file Polyphony.h
 *
 * \author Scott Holzknecht
 *
 * \brief plays more than one note at a time
 */

#pragma once
#include <vector>
#include "Subtractive.h"

/**
 * \brief plays more than one note at a time
 */
class CPolyphony :
	public CSubtractive
{
public:
	CPolyphony();

	/** \brief Copy constructor disabled */
	CPolyphony(const CPolyphony &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CPolyphony &) = delete;

	virtual ~CPolyphony();

	virtual void Start() override;
	virtual bool Generate() override;

	void AddFreq(double f) { m_freqs.push_back(f); }

private:
	std::vector<double> m_freqs;
};

