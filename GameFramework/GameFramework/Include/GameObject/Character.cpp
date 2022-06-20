
#include "Character.h"

CCharacter::CCharacter()	:
	m_CurState(ActorState::End),
	m_PreState(ActorState::End)
{
	SetTypeID<CCharacter>();
}

CCharacter::CCharacter(const CCharacter& Obj) :
	CGameObject(Obj),
	m_CurState(ActorState::End),
	m_PreState(ActorState::End)
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

void CCharacter::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CCharacter::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

float CCharacter::InflictDamage(float Damage)
{
	return CGameObject::InflictDamage(Damage);
}
