#pragma once

#include "../Ref.h"
#include "../Animation/Animation.h"

class CGameObject	:
	public CRef
{
	friend class CScene;

protected:
	CGameObject();
	CGameObject(const CGameObject& Obj);
	virtual ~CGameObject();

protected:
	class CScene* m_Scene;

protected:
	ERender_Layer	m_RenderLayer;
	Vector2		m_PrevPos;
	Vector2		m_Move;
	Vector2		m_Pos;
	Vector2		m_Size;
	Vector2		m_Pivot;
	CSharedPtr<class CTexture>	m_Texture;
	CAnimation* m_Animation;
	float		m_TimeScale;
	float		m_MoveSpeed;
	std::list<CSharedPtr<class CCollider>>	m_ColliderList;

public:
	class CCollider* FindCollider(const std::string& Name);

	ERender_Layer GetRenderLayer()	const
	{
		return m_RenderLayer;
	}

	float GetTimeScale()	const
	{
		return m_TimeScale;
	}

	const Vector2& GetPos()	const
	{
		return m_Pos;
	}

	const Vector2& GetSize()	const
	{
		return m_Size;
	}

	const Vector2& GetPivot()	const
	{
		return m_Pivot;
	}

public:
	void SetTimeScale(float Scale)
	{
		m_TimeScale = Scale;
	}

	virtual void SetPos(float x, float y)
	{
		m_Pos.x = x;
		m_Pos.y = y;
	}

	virtual void SetPos(const Vector2& Pos)
	{
		m_Pos = Pos;
	}

	void SetSize(float x, float y)
	{
		m_Size.x = x;
		m_Size.y = y;
	}

	void SetSize(const Vector2& Size)
	{
		m_Size = Size;
	}

	void SetPivot(float x, float y)
	{
		m_Pivot.x = x;
		m_Pivot.y = y;
	}

	void SetPivot(const Vector2& Pivot)
	{
		m_Pivot = Pivot;
	}

public:
	void SetTexture(const std::string& Name);
	void SetTexture(class CTexture* Texture);
	void SetTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);

#ifdef UNICODE

	void SetTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

	void SetTexture(const std::string& Name, const std::vector<std::string>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif // UNICODE

	bool SetColorKey(unsigned char r, unsigned char g, unsigned char b,
		int Index = 0);
	bool SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b);

public:
	void CreateAnimation();
	void AddAnimation(const std::string& SequenceName, bool Loop = true,
		float PlayTime = 1.f, float PlayScale = 1.f,
		bool Reverse = false);
	void SetPlayTime(const std::string& Name, float PlayTime);
	void SetPlayScale(const std::string& Name, float PlayScale);
	void SetPlayLoop(const std::string& Name, bool Loop);
	void SetPlayReverse(const std::string& Name, bool Reverse);
	void SetCurrentAnimation(std::string& Name);
	void ChangeAnimation(const std::string& Name);
	bool CheckCurrentAnimation(const std::string& Name);


public:
	void MoveDir(const Vector2& Dir);
	void Move(const Vector2& MoveValue);
	void Move(float Angle);



public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);


public:
	template <typename T>
	void SetEndFunction(const std::string& Name, T* Obj, void(T::* Func)())
	{
		if (m_Animation)
			m_Animation->SetEndFunction<T>(Name, Obj, Func);
	}

	template <typename T>
	void SetCurrentAnimationEndFunction(T* Obj, void(T::* Func)())
	{
		if (m_Animation)
			m_Animation->SetCurrentAnimationEndFunction<T>(Obj, Func);
	}

	template <typename T>
	void AddNotify(const std::string& Name, int Frame, T* Obj, void(T::* Func)())
	{
		if (m_Animation)
			m_Animation->AddNotify<T>(Name, Frame, Obj, Func);
	}

	template <typename T>
	T* AddCollider(const std::string& Name)
	{
		T* Collider = new T;

		Collider->SetName(Name);
		Collider->m_Owner = this;
		Collider->m_Scene = m_Scene;

		if (!Collider->Init())
		{
			SAFE_DELETE(Collider);
			return nullptr;
		}

		m_ColliderList.push_back(Collider);

		return Collider;
	}
};

