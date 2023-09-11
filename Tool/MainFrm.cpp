
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Tool.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_MENUMAP, &CMainFrame::OnMapTool)
	ON_COMMAND(ID_MENUOBJECT, &CMainFrame::OnObjectTool)
	ON_COMMAND(ID_MENUPLAYER, & CMainFrame::OnPlayerTool)
	ON_COMMAND(ID_MENUMONSTER, &CMainFrame::OnMonsterTool)
	ON_COMMAND(ID_MENUROOM, &CMainFrame::OnRoomTool)
	ON_COMMAND(ID_MENUANIMATION, &CMainFrame::OnAnimTool)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
	m_MapTool->DestroyWindow();
	m_BlockTool->DestroyWindow();
	m_CharacterTool->DestroyWindow();
	m_AnimTool->DestroyWindow();

	Safe_Delete(m_MapTool);
	Safe_Delete(m_BlockTool);
	Safe_Delete(m_CharacterTool);
	Safe_Delete(m_AnimTool);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_MapTool = new CMapTool;
	m_MapTool->Create(IDD_MAPTOOL, this);

	m_BlockTool = new CBlockTool;
	m_BlockTool->Create(IDD_CBLOCKTOOL, this);

	m_CharacterTool = new CCharacterTool;
	m_CharacterTool->Create(IDD_CHARACTERTOOL, this);
	

	m_AnimTool = new CAnimTool;
	m_AnimTool->Create(IDD_ANIMTOOL, this);
	
	return 0;
}

void CMainFrame::OnDestroy()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_MainSplitter.CreateStatic(this, 1, 2);

	// 스플리터 왼쪽 (적용 화면)
	m_MainSplitter.CreateView(0, 0, RUNTIME_CLASS(CToolView), CSize(WINCX, WINCY), pContext);
	
	// 스플리터 오른쪽
	m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CMyform), CSize(300, WINCY), pContext);

	// SetColumnInfo(열 번호, 열의 크기 지정, 허용 가능한 최소 크기)
	//m_MainSplitter.SetColumnInfo(0, WINCX - 300, WINCX - 300);
	// SetColumnInfo(열 번호, 열의 크기 지정, 허용 가능한 최소 크기)
	m_MainSplitter.SetColumnInfo(1, 300, 300);

	return TRUE;
}

void CMainFrame::OnMapTool()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_MapTool->ShowWindow(SW_SHOW);
	m_MapTool->m_bTileSelected = false;

}

void CMainFrame::OnObjectTool()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//m_UnitTool.DoModal();
	m_BlockTool->ShowWindow(SW_SHOW);
	
}

void CMainFrame::OnMonsterTool()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnRoomTool()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnPlayerTool()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_CharacterTool->ShowWindow(SW_SHOW);
}



void CMainFrame::OnAnimTool()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_AnimTool->ShowWindow(SW_SHOW);
}
