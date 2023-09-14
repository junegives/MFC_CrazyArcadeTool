#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "BlockTerrain.h"
#include "Player.h"
#include "Device.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(ID eID, CObj* pObject)
{
	if (nullptr == pObject || END <= eID)
		return;

	m_listObject[eID].emplace_back(pObject);
}

bool CObjMgr::ExistPlayer()
{
	if (m_listObject[PLAYER].size() > 0)
		return true;

	return false;
}

void CObjMgr::Update()
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& iter = m_listObject[i].begin(); iter != m_listObject[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				if (i != EFFECT)
					Safe_Delete(*iter);

				iter = m_listObject[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->Late_Update();
	}
}

void CObjMgr::Render()
{
	float fPlayerY = (*m_listObject[PLAYER].begin())->Get_Info().vPos.y;
	bool	isFirst = true;

	for (int i = 0; i < END; ++i)
	{
		if (i == WATERBALLOON)
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

			for (auto& pObject : m_listObject[i])
			{
				pObject->Render();
			}
		}
		if (i == BLOCK)
		{
			for (auto& pObject : m_listObject[i])
			{
				dynamic_cast<CBlockTerrain*>(pObject)->RenderBlock(fPlayerY, isFirst);
			}
			if (!isFirst)
				i = PLAYER;
			isFirst = false;
		}
		else if (i == PLAYER)
		{
			for (auto& pObject : m_listObject[i])
			{
				pObject->Render();
			}
			i = BLOCK - 1;
		}
		else
		{
			for (auto& pObject : m_listObject[i])
			{
				pObject->Render();
			}
		}
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			Safe_Delete(pObject);

		m_listObject[i].clear();
	}
}
