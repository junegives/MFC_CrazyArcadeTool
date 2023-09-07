
// MainFrm.cpp : CMainFrame Ŭ������ ����
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
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_MapTool = new CMapTool;
	m_MapTool->Create(IDD_MAPTOOL, this);

	m_BlockTool = new CBlockTool;
	m_BlockTool->Create(IDD_CBLOCKTOOL, this);
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return TRUE;
}

// CMainFrame ����

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


// CMainFrame �޽��� ó����



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_MainSplitter.CreateStatic(this, 1, 2);

	// ���ø��� ���� (���� ȭ��)
	m_MainSplitter.CreateView(0, 0, RUNTIME_CLASS(CToolView), CSize(WINCX, WINCY), pContext);
	
	// ���ø��� ������
	m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CMyform), CSize(300, WINCY), pContext);

	// SetColumnInfo(�� ��ȣ, ���� ũ�� ����, ��� ������ �ּ� ũ��)
	//m_MainSplitter.SetColumnInfo(0, WINCX - 300, WINCX - 300);
	// SetColumnInfo(�� ��ȣ, ���� ũ�� ����, ��� ������ �ּ� ũ��)
	m_MainSplitter.SetColumnInfo(1, 300, 300);

	return TRUE;
}

void CMainFrame::OnMapTool()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_MapTool->ShowWindow(SW_SHOW);
}


void CMainFrame::OnObjectTool()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//m_UnitTool.DoModal();

	m_BlockTool->ShowWindow(SW_SHOW);
}

void CMainFrame::OnMonsterTool()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CMainFrame::OnRoomTool()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CMainFrame::OnPlayerTool()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
