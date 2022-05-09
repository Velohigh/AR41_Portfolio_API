#pragma once

#include "GameInfo.h"

class CRef
{
public:
	CRef();
	CRef(const CRef& ref);
	virtual ~CRef();

protected:
	int		m_RefCount;
	std::string	m_Name;
	std::string m_TypeName;
	size_t	m_TypeID;
	bool	m_Enable;	// Ȱ��, ��Ȱ��
	bool	m_Active;	// ��� �ִ��� �׾�����

public:
	void AddRef();
	void Release();

public:
	bool GetEnable() const
	{
		return m_Enable;
	}

	bool GetActive() const
	{
		return m_Active;
	}

	size_t GetTypeID() const
	{
		return m_TypeID;
	}

	const std::string& GetTypeName() const
	{
		return m_TypeName;
	}

	const std::string& GetName() const
	{
		return m_Name;
	}

	void SetEnable(bool Enable)
	{
		m_Enable = Enable;
	}

	void SetActive(bool Active)
	{
		m_Active = Active;
	}

	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}

	template <typename T>
	bool CheckTypeID() const
	{
		return m_TypeID == typeid(T).hash_code();
	}

public:
	template <typename T>
	void SetTypeID()
	{
		// Ÿ�� �̸��� ���ڿ��� ���´�.
		m_TypeName = typeid(T).name();

		// Ÿ���� ������ ��ȣ�� ���´�.
		// �� Ŭ������ ������ ��ȣ�� ������ �ִ�.
		m_TypeID = typeid(T).hash_code();
	}
};
