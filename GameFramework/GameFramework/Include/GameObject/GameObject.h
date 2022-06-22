#pragma once

#include "../Ref.h"
#include "../Animation/Animation.h"
#include "../Widget/WidgetComponent.h"

class CGameObject	:
	public CRef
{
	friend class CScene;
	friend class CInput;

protected:
	CGameObject();
	CGameObject(const CGameObject& Obj);
	virtual ~CGameObject();

protected:
	class CScene* m_Scene;

protected:
	ERender_Layer	m_RenderLayer;
	Vector2		m_PrevPos;		// 이전 프레임 위치
	Vector2		m_Move;			// 이동량 (현재 프레임 위치 - 과거 프레임 위치)
	Vector2		m_MoveDir;		// 이동 방향 벡터
	Vector2		m_Pos;			// 위치
	Vector2		m_Size;			// 크기
	Vector2		m_Pivot;		// 피봇
	CSharedPtr<class CTexture>	m_Texture;	// 출력 텍스쳐
	CSharedPtr<class CTexture>	m_MapColTexture;	// 충돌맵 텍스쳐
	CAnimation* m_Animation;	// 애니메이션
	float		m_TimeScale;	// 타임스케일 ( 시간 흐름 배속 )
	float		m_MoveSpeed;	// 움직이는 속도
	std::list<CSharedPtr<class CCollider>>	m_ColliderList;	// 충돌체
	std::list<CSharedPtr<CWidgetComponent>>	m_WidgetComponentList;	// 위젯컴포넌트
	bool		m_PhysicsSimulate;		// 물리효과 온/오프
	bool		m_Ground;			// 땅을 밟고 있는 상태인지 아닌지
	float		m_GravityAccel;		// 중력가속도
	float		m_FallTime;			// 떨어지기 시작하고 지난 시간
	float		m_FallStartY;		// 떨어지기 시작한 위치
	bool		m_Jump;				// 점프중인지 아닌지
	float		m_JumpVelocity;		// 점프 속도
	bool		m_SideWallCheck;	// 타일맵 사이드 체크
	bool		m_Start;
	int			m_RenderScale = 1;	// 출력 배율

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
	void SetSideWallCheck(bool Check)
	{
		m_SideWallCheck = Check;
	}

	void SetPhysicsSimulate(bool Physics)
	{
		m_PhysicsSimulate = Physics;
	}

	void SetGravityAccel(float Accel)
	{
		m_GravityAccel = Accel;
	}

	void SetJumpVelocity(float JumpVelocity)
	{
		m_JumpVelocity = JumpVelocity;
	}

	void Jump()
	{
		if (!m_Jump)
		{
			m_Jump = true;
			m_Ground = false;

			m_FallTime = 0.f;
			m_FallStartY = m_Pos.y;
		}
	}

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

	inline void SetRenderScale(const int Scale)
	{
		m_RenderScale = Scale;
	}

	void SetSpeed(const float Speed)
	{
		m_MoveSpeed = Speed;
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
		void SetMapTexture(const std::string& Name);
		void SetMapTexture(class CTexture* Texture);
		void SetMapTexture(const std::string& Name, const TCHAR* FileName,
			const std::string& PathName = TEXTURE_PATH);
		void SetMapTextureFullPath(const std::string& Name, const TCHAR* FullPath);

#ifdef UNICODE

		void SetMapTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
			const std::string& PathName = TEXTURE_PATH);
		void SetMapTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

		void SetMapTexture(const std::string& Name, const std::vector<std::string>& vecFileName,
			const std::string& PathName = TEXTURE_PATH);
		void SetMapTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif // UNICODE


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
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	void SaveFullPath(const char* FullPath);
	void LoadFullPath(const char* FullPath);
	void SaveFileName(const char* FileName, const std::string& PathName);
	void LoadFileName(const char* FileName, const std::string& PathName);



private:
	void CheckMoveRight();
	void CheckMoveLeft();


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

	CWidgetComponent* FindWidgetComponent(const std::string& Name)
	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
				return *iter;
		}

		return nullptr;
	}

	template <typename T>
	CWidgetComponent* CreateWidgetComponent(const std::string& Name)
	{
		CWidgetComponent* Widget = FindWidgetComponent(Name);

		if (Widget)
			return Widget;

		Widget = new CWidgetComponent;

		Widget->m_Owner = this;
		Widget->m_Scene = m_Scene;
		Widget->SetName(Name);

		if (!Widget->Init())
		{
			SAFE_DELETE(Widget);
			return nullptr;
		}

		Widget->CreateWidget<T>(Name);

		m_WidgetComponentList.push_back(Widget);

		return Widget;
	}
};

