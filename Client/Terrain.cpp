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
	if (FAILED(Load_Tile(L"../Data/Test.dat")))
	{
		ERR_MSG(L"Load_Tile Failed");
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

		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);

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

	DWORD	dwByte(0);
	TILE* pTile = nullptr;

	while (true)
	{
		pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pTile);
			break;
		}

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);

	return S_OK;
}
