#include "stdafx.h"
#include "WaterBalloon.h"

#include "TimeMgr.h"
#include "Device.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Flow.h"

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

	m_tFrame = { 0.f, 3.f , 1.5f, false};
	return S_OK;
}


int CWaterBalloon::Update(void)
{
	//if (5 * CTimeMgr::Get_Instance()->Get_TimeDelta())
	//	return OBJ_DEAD;

	m_Timer += CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (m_Timer > m_LimitTime)
	{
		CObj* pFlow1 = new CFlow;
		pFlow1->Initialize();
		pFlow1->Set_Pos({ m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f });
		pFlow1->Set_StateKey(L"FlowStay");
		CObjMgr::Get_Instance()->Add_Object(CObjMgr::FLOW, pFlow1);

		for (int i = 1; i <= m_iLength; i++)
		{
			CObj* pFlow = new CFlow;
			pFlow->Initialize();
			pFlow->Set_Pos({ m_tInfo.vPos.x - TILECX * i, m_tInfo.vPos.y, 0.f });
			pFlow->Set_StateKey(L"FlowLeft");
			CObjMgr::Get_Instance()->Add_Object(CObjMgr::FLOW, pFlow);

			CObj* pFlow2 = new CFlow;
			pFlow2->Initialize();
			pFlow2->Set_Pos({ m_tInfo.vPos.x + TILECX * i, m_tInfo.vPos.y, 0.f });
			pFlow2->Set_StateKey(L"FlowRight");
			CObjMgr::Get_Instance()->Add_Object(CObjMgr::FLOW, pFlow2);

			CObj* pFlow3 = new CFlow;
			pFlow3->Initialize();
			pFlow3->Set_Pos({ m_tInfo.vPos.x, m_tInfo.vPos.y - TILECY * i, 0.f });
			pFlow3->Set_StateKey(L"FlowUp");
			CObjMgr::Get_Instance()->Add_Object(CObjMgr::FLOW, pFlow3);

			CObj* pFlow4 = new CFlow;
			pFlow4->Initialize();
			pFlow4->Set_Pos({ m_tInfo.vPos.x, m_tInfo.vPos.y + TILECY * i, 0.f });
			pFlow4->Set_StateKey(L"FlowDown");
			CObjMgr::Get_Instance()->Add_Object(CObjMgr::FLOW, pFlow4);
		}


		return OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}

void CWaterBalloon::Late_Update(void)
{
	__super::Move_Frame();
}

void CWaterBalloon::Render(void)
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

void CWaterBalloon::Release(void)
{

}

void CWaterBalloon::Set_Balloon(wstring _szBalloon)
{
	m_wstrStateKey = _szBalloon;
}

