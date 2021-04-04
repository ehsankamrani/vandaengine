//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "..\common\utility.h"
class CBase
{
protected:

	CChar m_name[MAX_NAME_SIZE];
	CChar m_docURI[MAX_URI_SIZE];

	std::string m_str_name;
	CBase* m_next;
	std::string m_str_docURI;

public:
	CBase();
	virtual ~CBase() { Destroy(); };

	// for auto deletion of the linked list 
	CVoid Destroy();
	CBase *GetNext();
	CBase *SetNext(CBase * next);
	CChar *GetName();
	CVoid SetName(const CChar * n);
	CVoid SetDocURI(const CChar * n);
	CChar *GetDocURI();

private:
	friend class boost::serialization::access;

	template <typename Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & m_str_name;
		ar & m_next;
		ar & m_str_docURI;
	}

};