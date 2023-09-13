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
		L"../Image/BackGround/InGame/InGame.png",
		L"InGame", L"InGame", 1);


	CObj*	pObj = new CTerrain;
	
	if (nullptr == pObj)
		return E_FAIL;

	pObj->Initialize();	
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::TERRAIN, /*BACKGROUND,*/ pObj);

	//블럭 오브젝트
	CObj* pBlockObj = new CBlockTerrain;

	pBlockObj->Initialize();
	CObjMgr::Get_Instance()->Add_Object(CObjMgr::BLOCK, /*GAMEOBJECT,*/ pBlockObj);

	if (nullptr == pBlockObj)
		return E_FAIL;


	//CObj* block = CObjMgr::Get_Instance()->Get_Block();
	
	// 플레이어
	//dynamic_cast<CPlayer*>((CObjMgr::Get_Instance()->Get_Player()))->Set_BlockTile(&(dynamic_cast<CBlockTerrain*>(block)->Get_BlockTile()));



	if (!CObjMgr::Get_Instance()->ExistPlayer())
	{
		CObj* pObj = new CPlayer;
		if (nullptr == pObj)
			return E_FAIL;

		pObj->Initialize();
		dynamic_cast<CPlayer*>(pObj)->Load_Player(L"dubi", L"Bazzi");

		CObjMgr::Get_Instance()->Add_Object(CObjMgr::PLAYER, /*GAMEOBJECT,*/ pObj);
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
	D3DXMATRIX	matWorld, matTrans;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

	matWorld = matTrans;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"InGame", L"InGame", 1);

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
