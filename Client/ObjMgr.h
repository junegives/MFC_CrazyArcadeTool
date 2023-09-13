#pragma once

#include "Include.h"

class CObj; 
class CObjMgr final 
{
	DECLARE_SINGLETON(CObjMgr)

public:
	enum ID {TERRAIN, FLOW, WATERBALLOON, BLOCK, PLAYER, MONSTER, EFFECT, UI, END };




private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Terrain() { return m_listObject[TERRAIN].front(); }
	CObj* Get_Player() { return m_listObject[PLAYER].front(); }
	CObj* Get_Block() { return m_listObject[BLOCK].front(); }

public:
	void Add_Object(ID eID,/* RENDERID renderID,*/ CObj* pObject);
	bool ExistPlayer();

public:
	void Update(); 
	void Late_Update(); 
	void Render(); 
	void Release(); 

private:
	list<CObj*>		m_listObject[END];
	list<CObj*>		m_RenderList[RENDER_END];
};

