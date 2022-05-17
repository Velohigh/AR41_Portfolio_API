
#include "Character.h"

CCharacter::CCharacter()
{
	SetTypeID<CCharacter>();
}

CCharacter::CCharacter(const CCharacter& Obj) :
	CGameObject(Obj)
{
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	return true;
}

void CCharacter::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CCharacter::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}
