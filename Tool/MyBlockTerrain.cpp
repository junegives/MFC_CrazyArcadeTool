#include "stdafx.h"
#include "MyBlockTerrain.h"
#include "TextureMgr.h"
#include "Device.h"
#include "ToolView.h"

CMyBlockTerrain::CMyBlockTerrain() : m_pMainView(nullptr)
{
	m_vecTile.reserve(TILEX * TILEY);
}

CMyBlockTerrain::~CMyBlockTerrain()
{
	Release();
}

void CMyBlockTerrain::Tile_Move(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vSize, const int& iDrawID)
{
	if (m_Tile == nullptr)
	{
		m_Tile = new TILE;
	}
	m_Tile->vPos = { vPos.x, vPos.y, 0.f };
	m_Tile->vSize = { vSize.x, vSize.y, 0.f };
	m_Tile->byOption = 0;
	m_Tile->byDrawID = iDrawID;

	m_vImageSize = vSize;
}

void CMyBlockTerrain::Tile_Change(const D3DXVECTOR3& vPos, D3DXVECTOR3& vSize, const BYTE& byMove, const BYTE& byBurst, const int& iDrawID)
{
	int	iIndex = Get_TileIndex(vPos);

	if (-1 == iIndex)
		return;

	float	fCenterX = (TILECX / 2.f);
	float	fCenterY = vSize.y - (TILECY / 2.f);

	//이미지의 칸 갯수 파악을 위함
	int iBlockX = vSize.x / TILECX;
	int iBlockY = vSize.y / TILECY;


	if (0 != (int)vSize.x % TILECX)
	{
		iBlockX = iBlockX + 1;
	}
	if ((int)vSize.y % TILECY != 0)
	{
		iBlockY = iBlockY + 1;
	}

	if (CanInstall(iIndex, iBlockX, iBlockY))
	{
		if (iBlockX <= 1 && iBlockY <= 1)
		{
			m_vecTile[iIndex]->byDrawID = iDrawID;
			m_vecTile[iIndex]->byOption_Move = byMove;
			m_vecTile[iIndex]->byOption_Burst = byBurst;

			m_vecTile[iIndex]->vImageCenter = { fCenterX, fCenterY, 0.f };
			m_vecTile[iIndex]->bPick = true;
		}
		else
		{
			m_vecTile[iIndex]->byDrawID = iDrawID;

			for (size_t i = 0; i < iBlockY; i++)
			{
				for (size_t j = 0; j < iBlockX; j++)
				{
					int iImageIndex = iIndex + j - (i * 15);

					m_vecTile[iImageIndex]->byOption_Move = byMove;
					m_vecTile[iImageIndex]->byOption_Burst = byBurst;

					m_vecTile[iIndex]->vImageCenter = { fCenterX, fCenterY, 0.f };
					m_vecTile[iImageIndex]->bPick = true;
				}
			}
		}
	}
}

void CMyBlockTerrain::Tile_Change(const D3DXVECTOR3& vPos, const int& iDrawID)
{
	int	iIndex = Get_TileIndex(vPos);

	if (-1 == iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = iDrawID;
	m_vecTile[iIndex]->byOption = 1;
}

int CMyBlockTerrain::Get_TileIndex(const D3DXVECTOR3& vPos)
{
	for (size_t index = 0; index < m_vecTile.size(); ++index)
	{
		if (Picking(vPos, index))
		{
			return index;
		}
	}

	return -1;
}

bool CMyBlockTerrain::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
{
	bool bCheck[4]{ false };

	if ((m_vecTile[iIndex]->vPos.x - TILECX / 2.f) <= vPos.x)
	{
		bCheck[0] = true;
	}
	if ((m_vecTile[iIndex]->vPos.x + TILECX / 2.f) > vPos.x)
	{
		bCheck[1] = true;
	}
	if ((m_vecTile[iIndex]->vPos.y - TILECY / 2.f) <= vPos.y)
	{
		bCheck[2] = true;
	}
	if ((m_vecTile[iIndex]->vPos.y + TILECY / 2.f) > vPos.y)
	{
		bCheck[3] = true;
	}

	return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];

	//// y = ax + b
	//// 12 -> 3 -> 6 - > 9
	//
	//float	fGradient[4]{
	//
	//	(TILECY / 2.f) / (TILECX / 2.f) * -1.f,
	//	(TILECY / 2.f) / (TILECX / 2.f),
	//	(TILECY / 2.f) / (TILECX / 2.f) * -1.f,
	//	(TILECY / 2.f) / (TILECX / 2.f)
	//
	//};
	//
	//D3DXVECTOR3		vPoint[4]
	//{
	//	{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
	//	{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y , 0.f },
	//	{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
	//	{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f }
	//};
	//
	//// y = ax + b
	//// -b = ax - y
	//// b = y - ax
	//
	//float	fB[4]
	//{
	//	vPoint[0].y - fGradient[0] * vPoint[0].x,
	//	vPoint[1].y - fGradient[1] * vPoint[1].x,
	//	vPoint[2].y - fGradient[2] * vPoint[2].x,
	//	vPoint[3].y - fGradient[3] * vPoint[3].x
	//};
	//
	//// 0 == ax + b - y
	//// 0 > ax + b - y(위)
	//// 0 < ax + b - y(아래) 
	//
	//bool	bCheck[4]{ false };
	//
	//if (0 < fGradient[0] * vPos.x + fB[0] - vPos.y)
	//	bCheck[0] = true;
	//
	//if (0 >= fGradient[1] * vPos.x + fB[1] - vPos.y)
	//	bCheck[1] = true;
	//
	//if (0 >= fGradient[2] * vPos.x + fB[2] - vPos.y)
	//	bCheck[2] = true;
	//
	//if (0 < fGradient[3] * vPos.x + fB[3] - vPos.y)
	//	bCheck[3] = true;
	//
	//return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];
}

bool CMyBlockTerrain::Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex)
{
	D3DXVECTOR3		vPoint[4]
	{
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y , 0.f },
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f }
	};

	D3DXVECTOR3		vDir[4]
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	D3DXVECTOR3		vNormal[4]{
		{-vDir[0].y, vDir[0].x, 0.f },
		{ -vDir[1].y, vDir[1].x, 0.f },
		{ -vDir[2].y, vDir[2].x, 0.f },
		{ -vDir[3].y, vDir[3].x, 0.f }

	};

	D3DXVECTOR3	vMouseDir[4]
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);

		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;
}

bool CMyBlockTerrain::CanInstall(int _iIdenx, int _iBlockX, int _iBlockY)
{

	for (size_t i = 0; i < _iBlockY; i++)
	{
		for (size_t j = 0; j < _iBlockX; j++)
		{
			int iImageIndex = _iIdenx + j - (i * 15);

			if (j != 0)
			{
				if (iImageIndex % TILEX == 0) return false;
			}

			if (iImageIndex < 0 || iImageIndex >= m_vecTile.size()) return false;

			if (m_vecTile[iImageIndex]->bPick) return false;
		}
	}

	return true;
}

HRESULT CMyBlockTerrain::Initialize()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(TEX_MULTI, L"../Image/Block/Obj (%d).png", L"Image", L"Block", 30)))
	{
		AfxMessageBox(L"Tile Texture Insert Failed");
		return E_FAIL;
	}

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			TILE* pTile = new TILE;

			float	fX = TILECX * j + TILECX / 2;
			float	fY = TILECY * i + TILECY / 2;

			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { TILECX, TILECY, 0.f };
			pTile->byOption = 0;
			pTile->byDrawID = 29;

			pTile->byOption_Move = 0;
			pTile->byOption_Burst = 0;

			pTile->bPick = false;

			pTile->vImageCenter = { 0.f, 0.f, 0.f };

			//vImageSize = { TILECX, TILECY, 0.f };

			m_vecTile.push_back(pTile);
		}
	}


	return S_OK;
}

void CMyBlockTerrain::Update()
{
}

void CMyBlockTerrain::Render()
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR		szBuf[MIN_STR] = L"";
	int			iIndex = 0;
	RECT		rc{};

	for (auto& iter : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			iter->vPos.x,
			iter->vPos.y,
			iter->vPos.z);

		matWorld = matScale * matTrans;

		GetClientRect(m_pMainView->m_hWnd, &rc);

		float	fX = WINCX / float(rc.right - rc.left);
		float	fY = WINCY / float(rc.bottom - rc.top);

		Set_Ratio(&matWorld, fX, fY);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Image", L"Block", iter->byDrawID);

		//iter->vSize.x
		//iter->vSize.y

		//float	fCenterX = TILECX / 2.f;
		//float	fCenterY = TILECY / 2.f;

		//if (iter->vImageCenter.x == 0)
		//{
		//	float	fCenterX = (TILECX / 2.f);
		//	float	fCenterY = m_vImageSize.y - (TILECY / 2.f);

		//	iter->vImageCenter.x = fCenterX;
		//	iter->vImageCenter.y = fCenterY;
		//}



		RECT rectTile = { (float)iter->byDrawID * iter->vSize.x, 0, (float)iter->byDrawID * iter->vSize.x + iter->vSize.x, iter->vSize.y };

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(iter->vImageCenter.x, iter->vImageCenter.y, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		/*RECT rectTile = { (float)iter->byDrawID * TILECX, 0, (float)iter->byDrawID * TILECX + TILECX, TILECY };*/

		//CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		//	&rectTile,
		//	&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		//	nullptr,
		//	D3DCOLOR_ARGB(255, 255, 255, 255));




		//swprintf_s(szBuf, L"%d", iIndex);

		//CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(), // 스프라이트 객체
		//	szBuf,	// 출력할 문자열
		//	lstrlen(szBuf), // 문자열의 길이
		//	nullptr, //출력학 렉트의 주소
		//	0, // 정렬 옵션
		//	D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 폰트 색상
		//++iIndex;
	}
}

void CMyBlockTerrain::Mini_Render()
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR		szBuf[MIN_STR] = L"";

	for (auto& iter : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			iter->vPos.x,
			iter->vPos.y,
			iter->vPos.z);

		matWorld = matScale * matTrans;

		Set_Ratio(&matWorld, 0.3f, 0.3f);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Image", L"Block", iter->byDrawID);

		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMyBlockTerrain::Mouse_Render()
{
	if (m_Tile != nullptr)
	{
		D3DXMATRIX		matWorld, matScale, matTrans;

		TCHAR		szBuf[MIN_STR] = L"";
		RECT		rc{};

		int	iIndex = Get_TileIndex(Get_Mouse());
		
		if (iIndex == -1) return;

		m_Tile->vPos.x = m_vecTile[iIndex]->vPos.x;
		m_Tile->vPos.y = m_vecTile[iIndex]->vPos.y;
		m_Tile->vPos.z = m_vecTile[iIndex]->vPos.z;

		//이미지의 칸 갯수 파악을 위함
		int iBlockX = m_Tile->vSize.x / TILECX;
		int iBlockY = m_Tile->vSize.y / TILECY;

		if (0 != (int)m_Tile->vSize.x % TILECX)
		{
			iBlockX = iBlockX + 1;
		}
		if ((int)m_Tile->vSize.y % TILECY != 0)
		{
			iBlockY = iBlockY + 1;
		}

		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans,
			m_Tile->vPos.x,
			m_Tile->vPos.y,
			m_Tile->vPos.z);

		matWorld = matScale * matTrans;

		GetClientRect(m_pMainView->m_hWnd, &rc);

		float	fX = WINCX / float(rc.right - rc.left);
		float	fY = WINCY / float(rc.bottom - rc.top);

		Set_Ratio(&matWorld, fX, fY);

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Image", L"Block", m_Tile->byDrawID);

		float	fCenterX = (TILECX / 2.f);
		float	fCenterY = m_vImageSize.y - (TILECY / 2.f);

		if (CanInstall(iIndex, iBlockX, iBlockY))
		{
			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
				nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				nullptr,
				D3DCOLOR_ARGB(150, 0, 255, 0));
		}

		else
		{
			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
				nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				nullptr,
				D3DCOLOR_ARGB(150, 255, 0, 0));
		}

	}
}

void CMyBlockTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();

	Safe_Delete(m_Tile);
}

void CMyBlockTerrain::Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY)
{
	pOut->_11 *= fRatioX;
	pOut->_21 *= fRatioX;
	pOut->_31 *= fRatioX;
	pOut->_41 *= fRatioX;

	pOut->_12 *= fRatioY;
	pOut->_22 *= fRatioY;
	pOut->_32 *= fRatioY;
	pOut->_42 *= fRatioY;
}
