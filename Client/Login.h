#pragma once
#include "Scene.h"
#include "Include.h"

class CLogin :
	public CScene
{
public:
	CLogin();
	virtual ~CLogin();

public:
	virtual HRESULT Ready_Scene() override;
	virtual void Update_Scene() override;
	virtual void Late_Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;

public:
	wstring szID = L"";
};