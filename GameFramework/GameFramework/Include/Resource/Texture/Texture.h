#pragma once

#include "../../Ref.h"

struct ImageInfo
{
    HDC      hMemDC;
    HBITMAP  hBmp;
    HBITMAP  hPrevBmp;
    BITMAP   BmpInfo;
    COLORREF ColorKey;
    bool     EnableColorKey;

    ImageInfo() :
        hMemDC(0),
        hBmp(0),
        hPrevBmp(0),
        BmpInfo{},
        ColorKey(RGB(255, 0, 255)),
        EnableColorKey(false)
    {
    }

    ~ImageInfo()
    {
        // 도구를 원래대로 돌려준다.
        SelectObject(hMemDC, hPrevBmp);
        DeleteObject(hBmp);
        DeleteDC(hMemDC);
    }
};

class CTexture :
    public CRef
{
    friend class CTextureManager;

private:
    CTexture();
    ~CTexture();

private:
    ETexture_Type   m_Type;
    std::vector<ImageInfo*> m_vecImageInfo;

public:
    ETexture_Type GetTextureType()  const
    {
        return m_Type;
    }

    HDC GetDC(int Index = 0) const
    {
        return m_vecImageInfo[Index]->hMemDC;
    }

    void SetColorKey(unsigned char r, unsigned char g, unsigned char b,
        int Index = 0)
    {
        m_vecImageInfo[Index]->ColorKey = RGB(r, g, b);
        m_vecImageInfo[Index]->EnableColorKey = true;
    }

    void SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b)
    {
        size_t  Size = m_vecImageInfo.size();

        for (size_t i = 0; i < Size; ++i)
        {
            m_vecImageInfo[i]->ColorKey = RGB(r, g, b);
            m_vecImageInfo[i]->EnableColorKey = true;
        }
    }

    bool GetEnableColorKey(int Index = 0)    const
    {
        return m_vecImageInfo[Index]->EnableColorKey;
    }

    COLORREF GetColorKey(int Index = 0)    const
    {
        return m_vecImageInfo[Index]->ColorKey;
    }

public:
    bool LoadTexture(const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const TCHAR* FullPath);

#ifdef UNICODE

    bool LoadTexture(const std::vector<std::wstring>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const std::vector<std::wstring>& vecFullPath);

#else

    bool LoadTexture(const std::vector<std::string>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const std::vector<std::string>& vecFullPath);

#endif // UNICODE

};

