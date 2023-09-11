#pragma once
#include "Define.h"

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vSize;

	D3DXMATRIX		matWorld;
}INFO;

typedef	struct tagFrame
{
	float		fFrame; // 프레임을 세기 위한 변수
	float		fMax;	// 최대 이미지의 프레임 수

}FRAME;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // 컴 객체

	D3DXIMAGE_INFO			tImgInfo;	// 구조체

}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;			// 타일의 중점 좌표
	D3DXVECTOR3 vSize;			// 타일의 가로, 세로 사이즈

	BYTE		byOption;		// 0, 1번(장애물)
	BYTE		byDrawID;		// 몇 번 타일 이미지

	// 추가
	CString		wstrStateKey = L"";	// 타일 키 (맵별로 구별)

	//추가한 부분
	BYTE		byOption_Move;   //움직이는지 안움직이는지
	BYTE        byOption_Burst;  //터지는지 안터지는지

	D3DXVECTOR3 vImageCenter;

	bool        bPick;

}TILE;

typedef	struct tagUnitData
{
#ifdef _AFX
	CString	strName;
#else
	wstring strName;
#endif
	
	int		iAttack;
	int		iHp;

	BYTE	byJobIndex;
	BYTE	byItem;

}UNITDATA;

typedef struct tagTexturePath
{
	wstring		wstrObjKey		= L"";
	wstring		wstrStateKey	= L"";
	wstring		wstrPath = L"";
	int			iCount = 0;

}IMGPATH;


static D3DXVECTOR3		Get_Mouse()
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}


//새로 추가
typedef	struct tagCharacterData
{
#ifdef _AFX
	CString	strName;			//이름
#else
	wstring strName;
#endif

	int		iSpeed;				//스피드
	int		iWaterLength;		//물풍선 길이
	int     iWaterCount;		//물풍선 갯수

}CHARACTERDATA;
