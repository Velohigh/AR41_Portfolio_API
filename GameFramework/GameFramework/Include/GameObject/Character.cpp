#include "Character.h"

CCharacter::CCharacter()
{
	SetTypeID<CCharacter>();
}

CCharacter::CCharacter(const CCharacter& Obj)	:
	CGameObject(Obj)
{
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	return false;
}

void CCharacter::Update(float DeltaTime)
{
}

void CCharacter::Render(HDC hDC, float DeltaTime)
{
}
