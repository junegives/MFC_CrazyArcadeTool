// Myform.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "Myform.h"


// CMyform

IMPLEMENT_DYNCREATE(CMyform, CFormView)

CMyform::CMyform()
	: CFormView(IDD_MYFORM)
{

}

CMyform::~CMyform()
{
}

void CMyform::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyform, CFormView)

	ON_BN_CLICKED(IDC_BUTTON1, &CMyform::OnUnitTool)

	ON_BN_CLICKED(IDC_BUTTON4, &CMyform::OnMapTool)
END_MESSAGE_MAP()


// CMyform 진단입니다.

#ifdef _DEBUG
void CMyform::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyform::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyform 메시지 처리기입니다.


void CMyform::OnUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// GetSafeHwnd : 현재 다이얼로그 윈도우 핸들을 반환, 핸들이 null이면 아직 생성되지 않았음을 의미
	if(nullptr == m_UnitTool.GetSafeHwnd())
		m_UnitTool.Create(IDD_UNITTOOL);

	m_UnitTool.ShowWindow(SW_SHOW);

}


void CMyform::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_Font.CreatePointFont(180, L"궁서");

	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON4)->SetFont(&m_Font);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CMyform::OnMapTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == m_MapTool.GetSafeHwnd())
		m_MapTool.Create(IDD_MAPTOOL);

	m_MapTool.ShowWindow(SW_SHOW);
}
