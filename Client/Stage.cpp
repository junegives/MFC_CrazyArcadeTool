#include "stdafx.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
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
	if (FAILED(CTextureMgr::Get_Instance()->ReadImgPath(L"../Data/ImgPath2.txt")))
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
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		D3DXVECTOR3	vMouse = Get_Mouse();

		if (vMouse.x >= 655 && vMouse.x <= 780)
		{
			// 배찌
			if (vMouse.y >= 98 && vMouse.y <= 138)
			{
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Character(L"Bazzi");
			}

			// 캐피
			else if (vMouse.y >= 141 && vMouse.y <= 181)
			{
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Character(L"Cappi");
			}

			// 마리드
			else if (vMouse.y >= 184 && vMouse.y <= 222)
			{
				dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Character(L"LuxuryMarid");
			}

			// 물풍선 왼쪽 줄
			else if (vMouse.x <= 714)
			{
				if (vMouse.y >= 258 && vMouse.y <= 311)
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Balloon(L"Cottoncandy");
				}

				else if (vMouse.y >= 316 && vMouse.y <= 369)
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Balloon(L"Bluestreak");
				}

				else if (vMouse.y >= 374 && vMouse.y <= 427)
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Balloon(L"Greenstreak");
				}
				
				else if (vMouse.y >= 432 && vMouse.y <= 485)
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Balloon(L"Redblock");
				}

				else if (vMouse.y >= 490 && vMouse.y <= 543)
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Balloon(L"Redstreak");
				}
			}

			// 물풍선 오른쪽 줄
			else if (vMouse.x >= 720)
			{
				if (vMouse.y >= 258 && vMouse.y <= 311)
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Balloon(L"Blueblock");
				}

				else if (vMouse.y >= 316 && vMouse.y <= 369)
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Balloon(L"Greenheart");
				}

				else if (vMouse.y >= 374 && vMouse.y <= 427)
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Balloon(L"Orangeblock");
				}

				else if (vMouse.y >= 432 && vMouse.y <= 485)
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Balloon(L"Redheart");
				}

				else if (vMouse.y >= 490 && vMouse.y <= 543)
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Change_Balloon(L"Chicken");
				}
			}
		}
	}

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
