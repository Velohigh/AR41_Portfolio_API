
#include "Tile.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Scene/SceneManager.h"

CTile::CTile()	:
	m_Option(ETile_Option::Normal),
	m_Scene(nullptr),
	m_Owner(nullptr),
	m_IndexX(0),
	m_IndexY(0),
	m_Index(0),
	m_TileFrame(0)
{
}

CTile::~CTile()
{
}

void CTile::SetTileInfo(const Vector2& Pos, const Vector2& Size, 
	int IndexX, int IndexY, int Index, CTexture* Texture)
{
	m_Texture = Texture;
	m_Pos = Pos;
	m_Size = Size;
	m_IndexX = IndexX;
	m_IndexY = IndexY;
	m_Index = Index;
}

void CTile::Render(HDC hDC)
{
	Vector2	Pos;
	Vector2	CameraPos;
	Vector2	Resolution;

	if (m_Scene)
	{
		CameraPos = m_Scene->GetCamera()->GetPos();
		Resolution = m_Scene->GetCamera()->GetResolution();
		Pos = m_Pos - m_Scene->GetCamera()->GetPos();
	}

	else
	{
		CScene* Scene = CSceneManager::GetInst()->GetScene();
		Pos = m_Pos - Scene->GetCamera()->GetPos();
		CameraPos = Scene->GetCamera()->GetPos();
		Resolution = Scene->GetCamera()->GetResolution();
	}

	if (m_Texture)
	{
		if (m_Texture->GetEnableColorKey())
		{
			if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
			{
				TransparentBlt(hDC, (int)Pos.x, (int)Pos.y,
					(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
					(int)m_StartFrame.x, (int)m_StartFrame.y,
					(int)m_Size.x, (int)m_Size.y, m_Texture->GetColorKey());
			}

			else
			{
				TransparentBlt(hDC, (int)Pos.x, (int)Pos.y,
					(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(m_TileFrame),
					0, 0,
					(int)m_Size.x, (int)m_Size.y, m_Texture->GetColorKey(m_TileFrame));
			}
		}

		else
		{
			if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
			{
				BitBlt(hDC, (int)Pos.x, (int)Pos.y,
					(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
					(int)m_StartFrame.x, (int)m_StartFrame.y, SRCCOPY);
			}

			else
			{
				BitBlt(hDC, (int)Pos.x, (int)Pos.y,
					(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(m_TileFrame),
					0, 0, SRCCOPY);
			}
		}
	}
}
