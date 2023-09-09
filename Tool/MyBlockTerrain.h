#pragma once

#include "Include.h"

class CToolView;
class CMyBlockTerrain
{
public:
	CMyBlockTerrain();
	~CMyBlockTerrain();

public:
	vector<TILE*>& Get_VecTile() { return m_vecTile; }

public:
	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }

	void		Tile_Move(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vSize, const int& iDrawID);

	void		Tile_Change(const D3DXVECTOR3& vPos, D3DXVECTOR3& vSize, const BYTE& byMove, const BYTE& byBurst, const int& iDrawID);


	void		Tile_Change(const D3DXVECTOR3& vPos, const int& iDrawID);
	int			Get_TileIndex(const D3DXVECTOR3& vPos);
	bool		Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool		Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);
	bool		CanInstall(int _iIdenx, int _iBlockX, int _iBlockY);

public:
	HRESULT		Initialize();
	void		Update();
	void		Render();
	void		Mini_Render();
	void        Mouse_Render();
	void		Release();

private:
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

private:
	vector<TILE*>		m_vecTile;
	CToolView* m_pMainView;

	//마우스를 따라다니는 불투명이미지를 만들기 위해서
	TILE* m_Tile = nullptr;

	//들어온 이미지 정보를 저장하기 위해서
	D3DXVECTOR3 m_vImageSize;
};

