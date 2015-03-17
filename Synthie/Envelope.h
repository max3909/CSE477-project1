/**
 * \file Envelope.h
 *
 * \author Scott Holzknecht
 *
 * \brief ADSR generator
 */

#pragma once
#include "Subtractive.h"

/**
 * \brief ADSR generator
 */
class CEnvelope :
	public CSubtractive
{
public:
	CEnvelope();

	/** \brief Copy constructor disabled */
	CEnvelope(const CEnvelope &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CEnvelope &) = delete;

	virtual ~CEnvelope();

	virtual void Start() override;
	virtual bool Generate() override;

private:
	double m_attackend;
	double m_delayend;
	double m_releasestart;
	double m_duration;
};

