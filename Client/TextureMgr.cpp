#include "stdafx.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}

CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEXINFO * CTextureMgr::Get_Texture(const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCnt)
{
	auto		iter = find_if(m_mapTex.begin(), m_mapTex.end(), [&](auto& MyPair)->bool
	{
		if (pObjKey == MyPair.first)
			return true;

		return false;
	});

	if (iter == m_mapTex.end())
		return nullptr;

	return iter->second->Get_Texture(pStateKey, iCnt);
}

HRESULT CTextureMgr::ReadImgPath(const wstring & wstrPath)
{
	wifstream		fin;

	fin.open(wstrPath, ios::in);

	if (!fin.fail())
	{
		TCHAR		szObjKey[MAX_STR] = L"";
		TCHAR		szStateKey[MAX_STR] = L"";
		TCHAR		szCount[MAX_STR] = L"";
		TCHAR		szPath[MAX_PATH] = L"";
			
		while (true)
		{
			fin.getline(szObjKey, MAX_STR, '|');
			fin.getline(szStateKey, MAX_STR, '|');
			fin.getline(szCount, MAX_STR, '|');
			fin.getline(szPath, MAX_PATH);

			if (fin.eof())
				break;

			int	iCount = _ttoi(szCount);

			if (FAILED(Insert_Texture(TEX_MULTI, szPath, szObjKey, szStateKey, iCount)))
			{
				ERR_MSG(L"ImgTxt Insert Failed");
				return E_FAIL;
			}
		}

		fin.close();
	}

	return S_OK;
}

HRESULT CTextureMgr::Insert_Texture(TEXTYPE eType, const TCHAR * pFilePath, const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCnt)
{
	auto		iter = find_if(m_mapTex.begin(), m_mapTex.end(), [&](auto& MyPair)->bool
	{
		if (pObjKey == MyPair.first)
			return true;

		return false;
	});

	if (m_mapTex.end() == iter)
	{
		CTexture*	pTexture = nullptr;

		switch (eType)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;

		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->Insert_Texture(pFilePath, pStateKey, iCnt)))
		{
			Safe_Delete(pTexture);
			ERR_MSG(pFilePath);
			return E_FAIL;
		}

		m_mapTex.insert({ pObjKey, pTexture });
	}
	else if (TEX_MULTI == eType)
		iter->second->Insert_Texture(pFilePath, pStateKey, iCnt);
	
	return S_OK;
}

void CTextureMgr::Release()
{
	for_each(m_mapTex.begin(), m_mapTex.end(), [](auto& MyPair) {

		Safe_Delete(MyPair.second);
	});

	m_mapTex.clear();
}

