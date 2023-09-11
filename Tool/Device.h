#pragma once

#include "Include.h"

class CDevice
{
	DECLARE_SINGLETON(CDevice)

private:
	CDevice();
	~CDevice();

	// 장치 초기화 과정
	// 1. 장치(그래픽 카드)를 조사할 객체 생성
	// 2. 장치를 조사(지원 수준의 여부)
	// 3. 그래픽 카드 제어 객체 생성(1번에서 만든 객체가 모체가 됨)

public:
	LPDIRECT3DDEVICE9		Get_Device() { return m_pDevice; }
	LPD3DXSPRITE			Get_Sprite() { return m_pSprite; }
	LPD3DXFONT				Get_Font() { return m_pFont; }

public:
	HRESULT			Init_Device(void);
	void			Render_Begin();
	void			Render_End(HWND hWnd = nullptr);
	void			Release();

private:
	void			Set_Parameters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXSPRITE		m_pSprite;
	LPD3DXFONT			m_pFont;

};

