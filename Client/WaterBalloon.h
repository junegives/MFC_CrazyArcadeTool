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

	void Set_Length(int _Length) { m_iLength = _Length; }
private:
	float m_Timer = 0.f;
	float m_LimitTime = 2.3f;

	int m_iLength = 2;
};

