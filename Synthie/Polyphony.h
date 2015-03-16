/**
 * \file Polyphony.h
 *
 * \author Scott Holzknecht
 *
 * \brief plays more than one note at a time
 */

#pragma once
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
};

