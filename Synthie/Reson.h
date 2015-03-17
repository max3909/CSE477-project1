/**
 * \file Reson.h
 *
 * \author Scott Holzknecht
 *
 * \brief reson filter
 */

#pragma once
#include "Subtractive.h"
#include "Note.h"

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

	virtual void Start() override;
	virtual bool Generate() override;

	void SetNote(CNote *note);

private:
	std::vector<short> m_queue_0;
	std::vector<short> m_queue_1;
	int m_wrloc;
	int m_rdloc;
};

