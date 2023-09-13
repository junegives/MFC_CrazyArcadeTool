#include "stdafx.h"
#include "Terrain.h"
#include "..\Tool\Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"


CTerrain::CTerrain()
{
	m_vecTile.reserve(TILEX * TILEY);
}


CTerrain::~CTerrain()
{
	Release();
}

HRESULT CTerrain::Initialize(void)
{
	if (FAILED(Load_Tile(L"../Data/HeartMap.dat")))
	{
		ERR_MSG(L"Load_Tile Failed");
		return E_FAIL;
	}

	//CTextureMgr::Get_Instance()->Insert_Texture(TEX_MULTI, L"Tile", (m_vecTile[0]->wstrStateKey).c_str(), 6);

	if (CTextureMgr::Get_Instance()->ReadImgPath(L"../Data/ImgPath.txt"))
	{
		ERR_MSG(L"Load Img Failed");
		return E_FAIL;
	}

	return S_OK;
}

int CTerrain::Update(void)
{
	return 0;
}

void CTerrain::Late_Update(void)
{
}

void CTerrain::Render(void)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	for (int i = 0; i < m_vecTile.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[i]->vPos.x,
			m_vecTile[i]->vPos.y,
			m_vecTile[i]->vPos.z);

		matWorld = matScale * matTrans;

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Tile", (m_vecTile[i]->wstrStateKey).c_str(), m_vecTile[i]->byDrawID);

		float	fCenterX = TILECX / 2.f;
		float	fCenterY = TILECX / 2.f;

		RECT rectTile = { (float)m_vecTile[i]->byDrawID * TILECX, 0, (float)m_vecTile[i]->byDrawID * TILECX + TILECX, TILECY };

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			&rectTile,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

}

void CTerrain::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

HRESULT CTerrain::Load_Tile(const TCHAR* pTilePath)
{
	HANDLE		hFile = CreateFile(pTilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	//DWORD	dwByte(0);
	//TILE* pTile = nullptr;
	//
	//while (true)
	//{
	//	pTile = new TILE;
	//
	//	ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);
	//
	//	if (0 == dwByte)
	//	{
	//		Safe_Delete(pTile);
	//		break;
	//	}
	//
	//	m_vecTile.push_back(pTile);
	//}
	//
	//CloseHandle(hFile);
	//
	//return S_OK;

	DWORD	dwByte(0), dwstrByte(0);
	TILE pTile = {};

	while (true)
	{
		ReadFile(hFile, &dwstrByte, sizeof(DWORD), &dwByte, nullptr);

		TCHAR* pName = new TCHAR[dwstrByte];
		ReadFile(hFile, pName, dwstrByte, &dwByte, nullptr);

		ReadFile(hFile, &(pTile.bPick), sizeof(bool), &dwByte, nullptr);
		ReadFile(hFile, &(pTile.byDrawID), sizeof(BYTE), &dwByte, nullptr);
		ReadFile(hFile, &(pTile.byOption), sizeof(BYTE), &dwByte, nullptr);
		ReadFile(hFile, &(pTile.byOption_Burst), sizeof(BYTE), &dwByte, nullptr);
		ReadFile(hFile, &(pTile.byOption_Move), sizeof(BYTE), &dwByte, nullptr);
		ReadFile(hFile, &(pTile.vPos), sizeof(D3DXVECTOR3), &dwByte, nullptr);
		ReadFile(hFile, &(pTile.vSize), sizeof(D3DXVECTOR3), &dwByte, nullptr);
		ReadFile(hFile, &(pTile.vImageCenter), sizeof(D3DXVECTOR3), &dwByte, nullptr);


		if (0 == dwByte)
		{
			delete[]pName;
			break;
		}

		TILE* pData = new TILE;

		pData->wstrStateKey = pName;
		delete[]pName;

		pData->bPick = pTile.bPick;
		pData->byDrawID = pTile.byDrawID;
		pData->byOption = pTile.byOption;
		pData->byOption_Burst = pTile.byOption_Burst;
		pData->byOption_Move = pTile.byOption_Move;
		pData->vPos = pTile.vPos;
		pData->vSize = pTile.vSize;
		pData->vImageCenter = pTile.vImageCenter;

		m_vecTile.push_back(pData);
	}

	CloseHandle(hFile);

	return S_OK;
}
