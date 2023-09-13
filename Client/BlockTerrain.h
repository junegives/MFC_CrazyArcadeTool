#pragma once
#include "Obj.h"
class CBlockTerrain : public CObj
{
public:
	CBlockTerrain();
	virtual~CBlockTerrain();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void		RenderBlock(float fPlayerY, bool isFirst);

public:
	vector<TILE*> Get_BlockTile() { return m_vecTile; }

private:
	HRESULT		Load_Tile(const TCHAR* pTilePath);

private:
	vector<TILE*>		m_vecTile;
};

