#pragma once

#include "SingleTexture.h"
#include "MultiTexture.h"

class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

private:
	CTextureMgr();
	~CTextureMgr();

public:
	const TEXINFO*		Get_Texture(const TCHAR* pObjKey, const TCHAR* pStateKey = L"", const int& iCnt = 0);

public:
	HRESULT			ReadImgPath(const wstring& wstrPath);
	vector<CString>		GetImgPath(const wstring& wstrPath, const wstring& pObjKey);
	HRESULT			Insert_Texture(TEXTYPE eType, const TCHAR* pFilePath, const TCHAR* pObjKey, const TCHAR* pStateKey = L"", const int& iCnt = 0);
	void			Release();

private:
	map<wstring, CTexture*>			m_mapTex;
};

