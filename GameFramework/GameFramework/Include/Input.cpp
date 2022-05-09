#include "Input.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()
{
}

CInput::~CInput()
{
	{
		auto iter = m_mapKeyState.begin();
		auto iterEnd = m_mapKeyState.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(iter->second);
		}

		m_mapKeyState.clear();
	}

	{
		auto iter = m_mapBindKey.begin();
		auto iterEnd = m_mapBindKey.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(iter->second);
		}

		m_mapBindKey.clear();
	}
}

bool CInput::Init()
{
	AddBindKey("MoveFront", 'W');
	AddBindKey("MoveBack", 'S');
	AddBindKey("GunRotation", 'D');
	AddBindKey("GunRotationInv", 'A');

	return true;
}

void CInput::Update(float DeltaTime)
{
}

KeyState* CInput::FindKeyState(unsigned char Key)
{
	auto iter = m_mapKeyState.find(Key);

	// ��ã���� ���
	if (iter == m_mapKeyState.end())
		return nullptr;

	// iter->first : key
	// iter->second : value
	return iter->second;
}

BindKey* CInput::FindBindKey(const std::string& Name)
{
	auto iter = m_mapBindKey.find(Name);

	// ��ã���� ���
	if (iter == m_mapBindKey.end())
		return nullptr;

	// iter->first : key
	// iter->second : value
	return iter->second;
}

bool CInput::AddBindKey(const std::string& Name,
	unsigned char Key)
{
	// ���� �̸����� BindKey�� ��ϵǾ� ���� ���
	if (FindBindKey(Name))
		return false;

	BindKey* NewKey = new BindKey;

	// �ش� Ű�� �̹� KeyState�� ��ϵǾ� �ִ����� ã�´�.
	KeyState* State = FindKeyState(Key);

	// ����� �ȵǾ� ���� ��� KeyState�� ���� ����Ѵ�.
	if (!State)
	{
		State = new KeyState;

		State->key = Key;

		m_mapKeyState.insert(std::make_pair(Key, State));
	}

	NewKey->key = State;
	NewKey->Name = Name;

	m_mapBindKey.insert(std::make_pair(Name, NewKey));

	return true;
}
