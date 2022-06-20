#pragma once

#include "Character.h"

enum class PlayerDir
{
	Left,
	Right,
	END
};

enum class PlayerState
{
	Idle,
	IdleToRun,
	Run,
	RunToIdle,
	Jump,
	Landing,
	Attack,
	Fall,
	Dodge,
	PlaySong,
	END
};

class CPlayer :
    public CCharacter
{
	friend class CScene;

protected:
	CPlayer();
	CPlayer(const CPlayer& Obj);
	virtual ~CPlayer();

private:

	CSharedPtr<class CWidgetComponent>	m_HPBar;
	CSharedPtr<class CWidgetComponent>	m_NameBar;
	PlayerDir	m_CurDir;								// 현재 바라보고 있는 방향
	std::string	m_AnimationName;
	std::string m_ChangeDirText;
	PlayerState	m_CurState;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

protected:
	void DirAnimationCheck();

private:
	bool IsMoveKey();	// 무브 키(wasd)를 눌렀는지 확인하는 함수, 눌렀다면 true
	void CreateAnimationSequence();
	void StateChange(PlayerState State);
	void StateUpdate();

private:
	// 키와 바인딩될 함수포인터
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void Fire();
	void JumpKey();

private:
	void AttackEnd();
	void Attack();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

private:
	void IdleUpdate();
	void IdleToRunUpdate();
	void RunUpdate();
	void RunToIdleUpdate();
	void JumpUpdate();
	void LandingUpdate();
	void AttackUpdate();
	void FallUpdate();
	void DodgeUpdate();
	void PlaySongUpdate();

	void IdleStart();
	void IdleToRunStart();
	void RunStart();
	void RunToIdleStart();
	void JumpStart();
	void LandingStart();
	void AttackStart();
	void FallStart();
	void DodgeStart();
	void PlaySongStart();

};

