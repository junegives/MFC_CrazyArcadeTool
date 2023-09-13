#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release(); 
}

void CObjMgr::Add_Object(ID eID,/* RENDERID renderID,*/ CObj * pObject)
{
	if (nullptr == pObject || END <= eID)
		return; 

	//if (nullptr == pObject || RENDER_END <= renderID)
	//	return;

	m_listObject[eID].emplace_back(pObject); 
	//m_RenderList[renderID].emplace_back(pObject);
}

bool CObjMgr::ExistPlayer()
{
	if (m_listObject[PLAYER].size() > 0)
		return true;
}

void CObjMgr::Update()
{
	for (int i = 0 ; i < END; ++i)
	{
		for (auto& iter = m_listObject[i].begin() ; iter != m_listObject[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				if(i != EFFECT)
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
	for (int i = 0 ; i < END ; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->Late_Update();
	}
}

void CObjMgr::Render()
{
	for (int i = 0; i < END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->Render();
	}

	//for (size_t i = 0; i < RENDER_END; ++i)
	//{
	//	 

	//	//m_RenderList[i].sort([](CObj* pDst, CObj* pSrc) ->bool
	//	//	{
	//	//		return pDst->Get_Info().fY < pSrc->Get_Info().fY;
	//	//	});

	//	for (auto& iter : m_RenderList[i])
	//		iter->Render();

	//	m_RenderList[i].clear();
	//}
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
