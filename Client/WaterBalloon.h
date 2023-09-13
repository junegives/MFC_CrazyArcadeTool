#pragma once
#include "Obj.h"
class CWaterBalloon : public CObj
{
public:
	CWaterBalloon();
	virtual~CWaterBalloon();

public:
	// CObj을(를) 통해 상속됨
	HRESULT Initialize(void) override;
	int Update(void) override;
	void Late_Update(void) override;
	void Render(void) override;
	void Release(void) override;

public:
	////픽킹과 같은 역할
	//bool ReDefine_vPos(D3DXVECTOR3& vPos, const int& iIndex);
	////get_tileIndex와 같은 역할
	//void Get_PosTileIndex(const D3DXVECTOR3& vPos);
	//최종적으로 물풍선의 위치를 조정하는 함수
	// void Set_WaterBalloonPos()

public:
	int m_iCount = 0;
	float m_fTime = 0.f;

	
};

