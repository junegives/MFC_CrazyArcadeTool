#include "stdafx.h"
#include "BlockTerrain.h"
#include "..\Tool\Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

CBlockTerrain::CBlockTerrain()
{
	m_vecTile.reserve(TILEX * TILEY);
}

CBlockTerrain::~CBlockTerrain()
{
	Release();
}

HRESULT CBlockTerrain::Initialize(void)
{
	if (FAILED(Load_Tile(L"../Data/BlockCemetery.dat")))
	{
		ERR_MSG(L"Load_Block Tile Failed");
		return E_FAIL;
	}

	//if (CTextureMgr::Get_Instance()->ReadImgPath(L"../Data/ImgPath.txt"))
	//{
	//	ERR_MSG(L"Load Block Img Failed");
	//	return E_FAIL;
	//}

	return S_OK;
}

int CBlockTerrain::Update(void)
{
	return 0;
}

void CBlockTerrain::Late_Update(void)
{
}

void CBlockTerrain::Render(void)
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

		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Block", L"Block", m_vecTile[i]->byDrawID);

		float fCenterX = m_vecTile[i]->vImageCenter.x;
		float fCenterY = m_vecTile[i]->vImageCenter.y;


		//RECT rectTile = { (float)m_vecTile[i]->byDrawID * TILECX, 0, (float)m_vecTile[i]->byDrawID * TILECX + TILECX, TILECY };
		//RECT rectTile = { (float)m_vecTile[i]->byDrawID * TILECX, 0, -((float)(m_vecTile[i]->byDrawID * TILECX) + (TILECX * iblockX)), TILECY * iblockY};

 		//RECT rectTile = { ((float)(m_vecTile[i]->byDrawID * TILECX) - (TILECX * iblockX)), 0, (float)(m_vecTile[i]->byDrawID * TILECX), TILECY * iblockY };

		RECT rectTile = { (float)m_vecTile[i]->byDrawID * m_vecTile[i]->vSize.x, 0, (float)m_vecTile[i]->byDrawID * m_vecTile[i]->vSize.x + m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y };

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

}

void CBlockTerrain::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CBlockTerrain::RenderBlock(float fPlayerY, bool isFirst)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	for (int i = 0; i < m_vecTile.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[i]->vPos.x + 20,
			m_vecTile[i]->vPos.y + 40,
			m_vecTile[i]->vPos.z);

		if (isFirst)
		{
			if (m_vecTile[i]->vPos.y > fPlayerY)
				return;
		}
		else
		{
			if (m_vecTile[i]->vPos.y <= fPlayerY)
			{
				continue;
			}
		}

		matWorld = matScale * matTrans;

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Block", L"Block", m_vecTile[i]->byDrawID);

		float fCenterX = m_vecTile[i]->vImageCenter.x;
		float fCenterY = m_vecTile[i]->vImageCenter.y;


		//RECT rectTile = { (float)m_vecTile[i]->byDrawID * TILECX, 0, (float)m_vecTile[i]->byDrawID * TILECX + TILECX, TILECY };
		//RECT rectTile = { (float)m_vecTile[i]->byDrawID * TILECX, 0, -((float)(m_vecTile[i]->byDrawID * TILECX) + (TILECX * iblockX)), TILECY * iblockY};

		//RECT rectTile = { ((float)(m_vecTile[i]->byDrawID * TILECX) - (TILECX * iblockX)), 0, (float)(m_vecTile[i]->byDrawID * TILECX), TILECY * iblockY };

		RECT rectTile = { (float)m_vecTile[i]->byDrawID * m_vecTile[i]->vSize.x, 0, (float)m_vecTile[i]->byDrawID * m_vecTile[i]->vSize.x + m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y };

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

HRESULT CBlockTerrain::Load_Tile(const TCHAR* pTilePath)
{
	HANDLE		hFile = CreateFile(pTilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

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
