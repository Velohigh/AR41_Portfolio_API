#include "Ref.h"

CRef::CRef()	:
	m_RefCount(0),
	m_Enable(true),
	m_Active(true),
	m_TypeID(0)
{
}

CRef::CRef(const CRef& ref)	:
	m_RefCount(0),
	m_TypeName(ref.m_TypeName),
	m_TypeID(ref.m_TypeID),
	m_Enable(true),
	m_Active(true)
{

}

CRef::~CRef()
{
}

void CRef::AddRef()
{
	++m_RefCount;
}

void CRef::Release()
{
	--m_RefCount;

	if (m_RefCount <= 0)
	{
		delete this;
		return;
	}
}
