#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Terrain.h"
#include "Player.h"
#include "BlockTerrain.h"

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
	CObjMgr::Get_Instance()->Render();
}

void CStage::Release_Scene()
{
}
