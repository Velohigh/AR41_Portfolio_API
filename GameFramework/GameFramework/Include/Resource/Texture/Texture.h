#pragma once

#include "../../Ref.h"

struct ImageInfo
{
    HDC     hMemDC;
    HBITMAP hBmp;
    HBITMAP hPrevBmp;
    BITMAP  BmpInfo;

    ImageInfo() :
        hMemDC(0),
        hBmp(0),
        hPrevBmp(0),
        BmpInfo{}
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
    HDC GetDC(int Index = 0) const
    {
        return m_vecImageInfo[Index]->hMemDC;
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

