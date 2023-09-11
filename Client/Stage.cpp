#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Terrain.h"
#include "Player.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	//if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(TEX_SINGLE,
	//	L"../Texture/Stage/Tile/test.png", 
	//	 L"Terrain", L"Tile", 1)))
	//{
	//	//ERR_MSG("Stage Tile Image Insert failed");
	//	return E_FAIL;
	//}	

	if (FAILED(CTextureMgr::Get_Instance()->ReadImgPath(L"../Data/ImgPath.txt")))
	{
		ERR_MSG(L"메모장에 문제있다고");
		return E_FAIL;
	}
	
	CObj*	pObj = new CTerrain;
	
	if (nullptr == pObj)
		return E_FAIL;

	pObj->Initialize();	
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::TERRAIN, pObj);

	// 플레이어
	pObj = new CPlayer;
	if (nullptr == pObj)
		return E_FAIL;

	pObj->Initialize();

	CObjMgr::Get_Instance()->Add_Object(CObjMgr::PLAYER, pObj);
	
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
