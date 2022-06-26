#pragma once

#include "GameObject.h"

class CEffect :
    public CGameObject
{
	friend class CScene;

protected:
	CEffect();
	CEffect(const CEffect& Obj);
	virtual ~CEffect();

private:
	EEffect_Type	m_EffectType;
	float			m_Duration;
	float			m_Time;
	CGameObject*	m_Owner = nullptr;

public:
	EEffect_Type GetEffectType()	const
	{
		return m_EffectType;
	}
	
	CGameObject* GetOwner() const
	{
		return m_Owner;
	}

public:
	void SetEffectType(EEffect_Type Type)
	{
		m_EffectType = Type;
	}

	void SetDuration(float Duration)
	{
		m_Duration = Duration;
	}

	void SetOwner(CGameObject* Owner)
	{
		m_Owner = Owner;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void AnimationEnd();
};

