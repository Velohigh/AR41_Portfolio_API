#pragma once

#include "GameInfo.h"
#include "SingletonMacro.h"

struct KeyState
{
	unsigned char	key;
	bool	Down;	// ������ �����Ҷ�
	bool	Push;	// ������ ���� ��
	bool	Up;		// ������ �ִ� Ű�� �ö�ö�

	KeyState() :
		key(0),
		Down(false),
		Push(false),
		Up(false)
	{
	}
};

struct BindFunction
{
	void* Obj;
	std::function<void()> func;

	BindFunction() :
		Obj(nullptr)
	{

	}
};

struct BindKey
{
	// �̸�
	std::string Name;
	// � Ű�� ����ϴ���.
	KeyState* key;
	bool	Ctrl;
	bool	Alt;
	bool	Shift;

	std::vector<BindFunction*> vecFunction;

	BindKey() :
		key(nullptr),
		Ctrl(false),
		Alt(false),
		Shift(false)
	{
	}
};

class CInput
{
private:
	std::unordered_map<unsigned char, KeyState*>	m_mapKeyState;
	std::unordered_map<std::string, BindKey*>		m_mapBindKey;

public:
	bool Init();
	void Update(float DeltaTime);

private:
	KeyState* FindKeyState(unsigned char Key);
	BindKey* FindBindKey(const std::string& Name);

public:
	bool AddBindKey(const std::string& Name, unsigned char Key);

	DECLARE_SINGLE(CInput)
};

