// AnimTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "AnimTool.h"


// CAnimTool 대화 상자

IMPLEMENT_DYNAMIC(CAnimTool, CDialog)

CAnimTool::CAnimTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ANIMTOOL, pParent)
{

}

CAnimTool::~CAnimTool()
{
}

void CAnimTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREEOBJECT, m_TreeObjectKey);
}


BEGIN_MESSAGE_MAP(CAnimTool, CDialog)
	ON_STN_CLICKED(IDC_TEXTCENTER1, &CAnimTool::OnStnClickedTextcenter1)
	ON_EN_CHANGE(IDC_EDITCENTERY1, &CAnimTool::OnEnChangeEditcentery1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERCENTERY1, &CAnimTool::OnNMCustomdrawSlidercentery1)
	ON_STN_CLICKED(IDC_TEXTSIZEY2, &CAnimTool::OnStnClickedTextsizey2)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAnimTool 메시지 처리기


BOOL CAnimTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetFont();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAnimTool::OnStnClickedTextcenter1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAnimTool::OnEnChangeEditcentery1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAnimTool::OnNMCustomdrawSlidercentery1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CAnimTool::OnStnClickedTextsizey2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAnimTool::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.MoveTo(700, 50);
	dc.LineTo(700, 630);
}

void CAnimTool::SetFont()
{
	//폰트 변수 선언
	CFont fontLarge, fontMedium, fontSmall;

	//폰트 생성
	fontLarge.CreateFontW(
		30,                            // 글자높이
		10,                            // 글자너비
		0,                            // 출력각도
		0,                            // 기준 선에서의각도
		FW_HEAVY,                    // 글자굵기
		FALSE,                        // Italic 적용여부
		FALSE,                        // 밑줄적용여부
		FALSE,                        // 취소선적용여부
		DEFAULT_CHARSET,            // 문자셋종류
		OUT_DEFAULT_PRECIS,            // 출력정밀도
		CLIP_CHARACTER_PRECIS,        // 클리핑정밀도
		PROOF_QUALITY,                // 출력문자품질
		DEFAULT_PITCH,                // 글꼴Pitch
		L"궁서"                // 글꼴
	);

	fontMedium.CreateFontW(
		25,                            // 글자높이
		9,                            // 글자너비
		0,                            // 출력각도
		0,                            // 기준 선에서의각도
		FW_HEAVY,                    // 글자굵기
		FALSE,                        // Italic 적용여부
		FALSE,                        // 밑줄적용여부
		FALSE,                        // 취소선적용여부
		DEFAULT_CHARSET,            // 문자셋종류
		OUT_DEFAULT_PRECIS,            // 출력정밀도
		CLIP_CHARACTER_PRECIS,        // 클리핑정밀도
		PROOF_QUALITY,                // 출력문자품질
		DEFAULT_PITCH,                // 글꼴Pitch
		L"궁서"                // 글꼴
	);

	fontSmall.CreateFontW(
		18,                            // 글자높이
		8,                            // 글자너비
		0,                            // 출력각도
		0,                            // 기준 선에서의각도
		FW_LIGHT,                    // 글자굵기
		FALSE,                        // Italic 적용여부
		FALSE,                        // 밑줄적용여부
		FALSE,                        // 취소선적용여부
		DEFAULT_CHARSET,            // 문자셋종류
		OUT_DEFAULT_PRECIS,            // 출력정밀도
		CLIP_CHARACTER_PRECIS,        // 클리핑정밀도
		PROOF_QUALITY,                // 출력문자품질
		DEFAULT_PITCH,                // 글꼴Pitch
		L"궁서"                // 글꼴
	);

	//컨트롤의 폰트를 변경한다.
	GetDlgItem(IDC_TEXTOBJECT)->SetFont(&fontLarge);
	GetDlgItem(IDC_TEXTSTATE)->SetFont(&fontLarge);
	GetDlgItem(IDC_TEXTLIST)->SetFont(&fontLarge);

	GetDlgItem(IDC_TEXTCOLLIDER)->SetFont(&fontLarge);

	GetDlgItem(IDC_GROUPCOLLIDER1)->SetFont(&fontMedium);
	GetDlgItem(IDC_GROUPCOLLIDER2)->SetFont(&fontMedium);

	GetDlgItem(IDC_TEXTCENTER1)->SetFont(&fontMedium);
	GetDlgItem(IDC_TEXTCENTER2)->SetFont(&fontMedium);
	GetDlgItem(IDC_TEXTSIZE1)->SetFont(&fontMedium);
	GetDlgItem(IDC_TEXTSIZE2)->SetFont(&fontMedium);

	GetDlgItem(IDC_TEXTCENTERX1)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTCENTERX2)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTSIZEX1)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTSIZEX2)->SetFont(&fontSmall);

	GetDlgItem(IDC_TEXTCENTERY1)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTCENTERY2)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTSIZEY1)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTSIZEY2)->SetFont(&fontSmall);

	GetDlgItem(IDC_TEXTANMIATION)->SetFont(&fontLarge);

	GetDlgItem(IDC_TEXTFRAMESPEED)->SetFont(&fontMedium);

	GetDlgItem(IDC_CHECKSHOWCOLLIDER1)->SetFont(&fontSmall);
	GetDlgItem(IDC_CHECKSHOWCOLLIDER2)->SetFont(&fontSmall);


	fontLarge.Detach();
	fontMedium.Detach();
	fontSmall.Detach();
}
