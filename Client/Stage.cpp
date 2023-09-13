#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Terrain.h"
#include "Player.h"
#include "BlockTerrain.h"

#include "Device.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	if (FAILED(CTextureMgr::Get_Instance()->ReadImgPath(L"../Data/ImgPath.txt")))
	{
		ERR_MSG(L"Notepad Error");
		return E_FAIL;
	}

	CTextureMgr::Get_Instance()->Insert_Texture(TEX_SINGLE,
		L"../Image/BackGround/InGame/Select.png",
		L"InGame", L"Select", 1);


	CObj*	pObj = new CTerrain;
	
	if (nullptr == pObj)
		return E_FAIL;

	pObj->Initialize();	
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::TERRAIN, pObj);

	//블럭 오브젝트
	pObj = new CBlockTerrain;

	pObj->Initialize();
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::BLOCK, pObj);

	if (nullptr == pObj)
		return E_FAIL;

	// 플레이어

	if (!CObjMgr::Get_Instance()->ExistPlayer())
	{
		CObj* pObj = new CPlayer;
		if (nullptr == pObj)
			return E_FAIL;

		pObj->Initialize();
		dynamic_cast<CPlayer*>(pObj)->Load_Player(L"dubi", L"Bazzi");

		CObjMgr::Get_Instance()->Add_Object(CObjMgr::PLAYER, pObj);
	}
	
	return S_OK;
}

void CStage::Update_Scene()
{
	CObjMgr::Get_Instance()->Update();
}

void CStage::Late_Update_Scene()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render_Scene()
{
	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"InGame", L"Select", 1);

	if (pTexInfo)
	{
		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(400, 300, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	CObjMgr::Get_Instance()->Render();
}

void CStage::Release_Scene()
{
}
