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
	HurtFlyLoop,
	HurtGround,
	Dead,
	END
};

class CPlayer :
    public CCharacter
{
	friend class CScene;
	friend class CStage_1;

protected:
	CPlayer();
	CPlayer(const CPlayer& Obj);
	virtual ~CPlayer();

private:

	//CSharedPtr<class CWidgetComponent>	m_HPBar;
	//CSharedPtr<class CWidgetComponent>	m_NameBar;
	PlayerDir	m_CurDir;								// 현재 바라보고 있는 방향
	std::string	m_AnimationName;
	std::string m_ChangeDirText;
	PlayerState	m_CurState;
	float		m_StateTime[static_cast<int>(PlayerState::END)];	// 해당 상태가 되고 지난 시간
	float	m_Gravity = 10.f;		// 플레이어 중력
	float	m_JumpPower = 300.f;
	float	m_LongJumpPower = 2000.f;
	bool	m_IsLongJump = false;
	int		m_AttackCount = 0;
	float		m_GameTime = 0.f;
	int			m_Battery = 11;
	float		m_BatteryRechargeTime = 0.f;
	float		m_BatteryPushTime = 0.f;
	bool		m_SlowModeSound = false;
	CCollider* m_PlayerAttackCollision = nullptr;
	Vector2		m_EnemyAttackDir = {};


public:
	PlayerState GetState() const
	{
		return m_CurState;
	}

public:
	void SetEnemyAttackDir(Vector2 Value)
	{
		m_EnemyAttackDir = Value;
	}

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
	void SlowModeKeyPush();
	void SlowModeKeyUp();

	// Notify
	void RunningSound();
	void HeadphoneSound();
	void CarsetteRewindSound();
	void CarsettePlaySound();

private:
	void AttackEnd();
	void Attack();

private:
	void HitBoxCollisionBegin(CCollider* Src, CCollider* Dest);
	void HitBoxCollisionEnd(CCollider* Src, CCollider* Dest);


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
	void HurtFlyLoopUpdate();
	void HurtGroundUpdate();
	void DeadUpdate();


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
	void HurtFlyLoopStart();
	void HurtGroundStart();
	void DeadStart();


private:
	// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
	void MapCollisionCheckMoveGround();
	void MapCollisionCheckMoveAir();


};

