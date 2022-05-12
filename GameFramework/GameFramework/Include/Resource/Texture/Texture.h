#pragma once

#include "../../Ref.h"

class CTexture :
    public CRef
{
    friend class CTextureManager;

private:
    CTexture();
    ~CTexture();

private:
    HDC     m_hMemDC;
    HBITMAP m_hBmp;
    HBITMAP m_hPrevBmp;
    BITMAP  m_BmpInfo;

public:
    HDC GetDC() const
    {
        return m_hMemDC;
    }

public:
    bool LoadTexture(const TCHAR* FileName, 
        const std::string& PathName = TEXTURE_PATH);
};

