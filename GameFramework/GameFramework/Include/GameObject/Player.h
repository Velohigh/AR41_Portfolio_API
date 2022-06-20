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
	//int		m_PlayerDir;

	bool	m_Attack;

	int		m_HP;
	int		m_HPMax;

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
	void CreateAnimationSequence();
	void StateChange(ActorState State);
	void StateUpdate();

private:
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
	void RunUpdate();
	void AttackUpdate();

	void IdleStart();
	void RunStart();
	void AttackStart();

};

