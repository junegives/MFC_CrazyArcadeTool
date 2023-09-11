// CharacterTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CharacterTool.h"

#include "CPlayerTool.h"
#include "CWaterBallonTool.h"

#include "Functor.h"

// CCharacterTool 대화 상자

IMPLEMENT_DYNAMIC(CCharacterTool, CDialog)

CCharacterTool::CCharacterTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CHARACTERTOOL, pParent)
{

}

CCharacterTool::~CCharacterTool()
{
}

void CCharacterTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_Tab);
}


BEGIN_MESSAGE_MAP(CCharacterTool, CDialog)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CCharacterTool::OnSelChange)
END_MESSAGE_MAP()


// CCharacterTool 메시지 처리기





BOOL CCharacterTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_Tab.InsertItem(0, _T("Character"));
	m_Tab.InsertItem(1, _T("WaterBalloon"));

	//탭 위치는 일단 첫번째로
	m_Tab.SetCurSel(0);

	CRect rect;
	m_Tab.GetWindowRect(&rect);

	m_Player = new CCPlayerTool;
	m_Player->Create(IDD_PLAYER, &m_Tab);
	m_Player->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_Player->ShowWindow(SW_SHOW);

	m_Water = new CCWaterBallonTool;
	m_Water->Create(IDD_WATERBALLOON, &m_Tab);
	m_Water->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_Water->ShowWindow(SW_HIDE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCharacterTool::OnSelChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	int iSel = m_Tab.GetCurSel();

	switch (iSel)
	{
	case 0:
		m_Player->ShowWindow(SW_SHOW);
		m_Water->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_Player->ShowWindow(SW_HIDE);
		m_Water->ShowWindow(SW_SHOW);
		break;
	}


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CCharacterTool::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	Safe_Delete(m_Player);
	Safe_Delete(m_Water);

	CDialog::PostNcDestroy();
}
