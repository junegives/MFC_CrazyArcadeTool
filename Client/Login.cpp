#include "stdafx.h"
#include "Login.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Terrain.h"
#include "Player.h"
#include "Device.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CLogin::CLogin()
{
}

CLogin::~CLogin()
{
	Release_Scene();
}

HRESULT CLogin::Ready_Scene()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(TEX_SINGLE,
		L"../image/BackGround/Login/Login.png", 
		 L"BackGround", L"Login", 1)))
	{
		//ERR_MSG("Stage Tile Image Insert failed");
		return E_FAIL;
	}

	//CObj*	pObj = new CTerrain;
	//
	//if (nullptr == pObj)
	//	return E_FAIL;

	//pObj->Initialize();	
	//CObjMgr::Get_Instance()->Add_Object(CObjMgr::TERRAIN, pObj);

	return S_OK;
}

void CLogin::Update_Scene()
{
	if (CKeyMgr::Get_Instance()->Key_Down('D'))
	{
		szID += 'd';
	}

	if (CKeyMgr::Get_Instance()->Key_Down('U'))
	{
		szID += 'u';
	}

	if (CKeyMgr::Get_Instance()->Key_Down('B'))
	{
		szID += 'b';
	}

	if (CKeyMgr::Get_Instance()->Key_Down('I'))
	{
		szID += 'i';
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		szID += 'a';
	}

	if (CKeyMgr::Get_Instance()->Key_Down('P'))
	{
		szID += 'p';
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_BACK))
	{
		szID.pop_back();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CObj* pObj = new CPlayer;
		pObj->Initialize();
		dynamic_cast<CPlayer*>(pObj)->Load_Player(szID, L"Bazzi");

		CObjMgr::Get_Instance()->Add_Object(CObjMgr::PLAYER, /*GAMEOBJECT, */pObj);

		CSceneMgr::Get_Instance()->Change_SceneMgr(CSceneMgr::STAGE);
	}
}

void CLogin::Late_Update_Scene()
{
}

void CLogin::Render_Scene()
{
	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"BackGround", L"Login", 1);

	if (pTexInfo)
	{
		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(0, 0, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT r{ 405, 500, 500, 520 };

		CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(), // 스프라이트 객체
			szID.c_str(),	// 출력할 문자열
			lstrlen(szID.c_str()) + 5, // 문자열의 길이
			&r, //출력학 렉트의 주소
			0, // 정렬 옵션
			D3DCOLOR_ARGB(255, 0, 0, 0)); // 출력할 폰트 색상

		//TextOut(GetDC(g_hWnd), 405, 510, szID, 10);
	}
}

void CLogin::Release_Scene()
{
}
