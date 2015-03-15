/**
 * \file Reson.h
 *
 * \author Scott Holzknecht
 *
 * \brief reson filter
 */

#pragma once
#include "Subtractive.h"

/**
 * \brief reson filter
 */
class CReson :
	public CSubtractive
{
public:
	CReson();

	/** \brief Copy constructor disabled */
	CReson(const CReson &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CReson &) = delete;

	virtual ~CReson();

	virtual void Start() {}
	virtual bool Generate() { return false; }

private:
	std::vector<short> m_queue_x;
	std::vector<short> m_queue_y;
	int m_wrloc = 0;
	int m_rdloc = 0;
};

