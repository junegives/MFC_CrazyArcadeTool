#pragma once
#include "Obj.h"
class CFlow : public CObj
{
public:
	CFlow();
	virtual~CFlow();

public:
	// CObj을(를) 통해 상속됨
	HRESULT Initialize(void) override;
	int Update(void) override;
	void Late_Update(void) override;
	void Render(void) override;
	void Release(void) override;

private:
	float m_fTimer = 0.f;
	float m_LimitTime = 0.5f;

};

