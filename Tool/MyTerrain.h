#pragma once

#include "Include.h"

class CToolView;
class CMyTerrain
{
public:
	CMyTerrain();
	~CMyTerrain();

public:
	vector<TILE*>&		Get_VecTile() { return m_vecTile; }

public:
	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }

	void		Tile_Change(const D3DXVECTOR3& vPos, const TCHAR* pObjKey, const int& iDrawID);
	int			Get_TileIndex(const D3DXVECTOR3& vPos);
	bool		Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool		Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);

	void		Tile_Preview(const D3DXVECTOR3& vPos, const TCHAR* pObjKey, const int& iDrawID);

public:
	HRESULT		Initialize();
	void		Update();
	void		Render();
	void		Mini_Render();
	void		Mouse_Render();
	void		Release();

private:
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

private:
	TILE*				m_pPreviewTile = nullptr;
	vector<TILE*>		m_vecTile;
	CToolView*			m_pMainView;
};

