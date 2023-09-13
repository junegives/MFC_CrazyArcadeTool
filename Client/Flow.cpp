#include "stdafx.h"
#include "Flow.h"

#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

CFlow::CFlow()
{
}

CFlow::~CFlow()
{
}

HRESULT CFlow::Initialize(void)
{

	m_wstrObjKey = L"WaterBomb";
	m_wstrStateKey = L"Flow";

	m_tFrame = { 0.f, 4.f, 2.f, false };

	return S_OK;
}

int CFlow::Update(void)
{
	m_fTimer += CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (m_fTimer > m_LimitTime)
	{
		return OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}

void CFlow::Late_Update(void)
{
	__super::Move_Frame();
}

void CFlow::Render(void)
{
	D3DXMATRIX		matTrans, matScale;

	//d3dxsca
	D3DXMatrixScaling(&matScale, 0.7f, 0.7f, 0.7f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + 20,
		m_tInfo.vPos.y + 40,
		0.f);

	m_tInfo.matWorld = matScale * matTrans;

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

void CFlow::Release(void)
{
}
