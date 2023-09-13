#include "stdafx.h"
#include "WaterBalloon.h"

#include "TimeMgr.h"
#include "Device.h"
#include "TextureMgr.h"

CWaterBalloon::CWaterBalloon()
{
}

CWaterBalloon::~CWaterBalloon()
{
	Release();
}

HRESULT CWaterBalloon::Initialize(void)
{
	m_tInfo.vPos = { 1000.f, 0.f, 0.f };

	m_wstrObjKey = L"WaterBalloon";

	m_wstrStateKey = L"Redblock";

	m_tFrame = { 0.f, 3.f };
	return S_OK;
}


int CWaterBalloon::Update(void)
{
	//if (5 * CTimeMgr::Get_Instance()->Get_TimeDelta())
	//	return OBJ_DEAD;

	D3DXMATRIX		matTrans, matScale;

	//d3dxsca
	D3DXMatrixScaling(&matScale, 0.7f, 0.7f, 0.7f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		0.f);

	m_tInfo.matWorld = matScale * matTrans;

	return OBJ_NOEVENT;
}

void CWaterBalloon::Late_Update(void)
{
	__super::Move_Frame();
}

void CWaterBalloon::Render(void)
{
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	if (pTexInfo)
	{
		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CWaterBalloon::Release(void)
{
}

//bool CWaterBalloon::ReDefine_vPos(D3DXVECTOR3& vPos, const int& iIndex)
//{
//	return false;
//}
//
//void CWaterBalloon::Get_PosTileIndex(const D3DXVECTOR3& vPos)
//{
//}
