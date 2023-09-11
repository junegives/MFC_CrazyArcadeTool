// CWaterBallonTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CWaterBallonTool.h"

#include "TextureMgr.h"
//#include <atlimage.h>


// CCWaterBallonTool 대화 상자

IMPLEMENT_DYNAMIC(CCWaterBallonTool, CDialog)

CCWaterBallonTool::CCWaterBallonTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_WATERBALLOON, pParent)
{

}

CCWaterBallonTool::~CCWaterBallonTool()
{
}

void CCWaterBallonTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTRLWATER, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CCWaterBallonTool, CDialog)
END_MESSAGE_MAP()


// CCWaterBallonTool 메시지 처리기


BOOL CCWaterBallonTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(TRUE);

	m_ImageList.Create(72, 76, ILC_COLOR16/* | ILC_MASK*/, 1, 1);

	//CTextureMgr::Get_Instance()->Insert_Texture(TEX_SINGLE, L"../Image/WaterBalloon/Cottoncandy01.png", L"Image", L"Cottoncandy");

	TCHAR szPath[MAX_PATH] = L"../Image/WaterBalloon/Cottoncandy/Cottoncandy01.png";

	CImage pngImage;

	CBitmap bit;

	pngImage.Load(szPath);
	bit.Attach(pngImage);

	//CBitmap* Bit = CBitmap::FromHandle(pngImage);

	m_ImageList.Add(&bit, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(0, L"Cottoncandy", 0);

	//lstrcpy(L"../Image/WaterBalloon/Blueblock/Blueblock01.png", szPath);

	TCHAR szPath1[MAX_PATH] = L"../Image/WaterBalloon/Blueblock/Blueblock01.png";
	
	CImage pngImage1;

	CBitmap bit1;

	pngImage1.Load(szPath1);

	bit1.Attach(pngImage1);

	m_ImageList.Add(&bit1, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(1, L"Blueblock", 1);

	TCHAR szPath2[MAX_PATH] = L"../Image/WaterBalloon/Bluestreak/Bluestreak01.png";

	CImage pngImage2;

	CBitmap bit2;

	pngImage2.Load(szPath2);

	bit2.Attach(pngImage2);

	m_ImageList.Add(&bit2, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(2, L"Bluestreak", 2);

	TCHAR szPath3[MAX_PATH] = L"../Image/WaterBalloon/Greenheart/Greenheart01.png";

	CImage pngImage3;

	CBitmap bit3;

	pngImage3.Load(szPath3);

	bit3.Attach(pngImage3);

	m_ImageList.Add(&bit3, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(3, L"Greenheart", 3);

	TCHAR szPath4[MAX_PATH] = L"../Image/WaterBalloon/Greenstreak/Greenstreak01.png";

	CImage pngImage4;

	CBitmap bit4;

	pngImage4.Load(szPath4);

	bit4.Attach(pngImage4);

	m_ImageList.Add(&bit4, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(4, L"Greenstreak", 4);

	m_ListCtrl.SetImageList(&m_ImageList, LVSIL_NORMAL);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
