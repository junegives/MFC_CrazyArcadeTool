
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CView)

BEGIN_MESSAGE_MAP(CToolView, CView)

	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView() : m_pMyTerrain(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
}

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// AfxGetMainWnd : ������ ���� �����츦 ��ȯ�ϴ� ���� �Լ�
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};

	// GetWindowRect : ���� �������� ������ ���� rect�� ä����
	pMainFrm->GetWindowRect(&rcWnd);


	// SetRect : ��Ʈ�� ������ ����ϴ� �Լ�

	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};

	// GetClientRect : ���� view â�� ��Ʈ ������ ������ �Լ�
	GetClientRect(&rcMainView);

	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	// SetWindowPos : �Ű� ������� �������� ��ġ�� ũ�⸦ �����ϴ� �Լ�
	// SetWindowPos(��ġ�� �������� Z������ ���� ������, X, Y ��ǥ, ���� ũ��, ���� ũ��, ��ġ�� �������� ũ�� �� ��ġ ���� �ɼ�)
	pMainFrm->SetWindowPos(nullptr, 0, 0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);


	g_hWnd = m_hWnd;

	if (FAILED(CDevice::Get_Instance()->Init_Device()))
	{
		AfxMessageBox(L"CDevice Init FAILED");
		return;
	}

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(TEX_SINGLE, L"../Texture/Cube.png", L"Cube")))
	{
		AfxMessageBox(L"Cube Texture Insert Failed");
		return;
	}

	m_pMyTerrain = new CMyTerrain;

	if (FAILED(m_pMyTerrain->Initialize()))
	{
		AfxMessageBox(L"Terrain Initialize Failed");
		return;
	}

	m_pMyTerrain->Set_MainView(this);

}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDevice::Get_Instance()->Render_Begin();

	m_pMyTerrain->Render();

	CDevice::Get_Instance()->Render_End();
}

#pragma region ����

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}
// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


#pragma endregion ����



void CToolView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	Safe_Delete(m_pMyTerrain);

	CTextureMgr::Get_Instance()->Destroy_Instance();
	CDevice::Get_Instance()->Destroy_Instance();
}


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO : ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonDown(nFlags, point);

	// AfxGetApp : ���� �����带 ���� �ִ� ���� ���� app�� ��ȯ
	CMainFrame*	pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyform*	pMyForm = dynamic_cast<CMyform*>(pMain->m_SecondSplitter.GetPane(1, 0));

	CMapTool*	pMapTool = &(pMyForm->m_MapTool);

	m_pMyTerrain->Tile_Change(D3DXVECTOR3(point.x + GetScrollPos(0), 
											point.y + GetScrollPos(1),
											0.f),
											pMapTool->m_iDrawID);

	// Invalidate : ȣ�� �� �����쿡 WM_PAINT�� WM_ERASEBKGND �޼����� �߻� ��Ŵ, �̶� OnDraw �Լ��� �ٽ� �� �� ȣ��

	// TRUE : WM_PAINT�� WM_ERASEBKGND�� �� �� �߻�
	// FALSE : WM_PAINT�� �޽����� �߻�

	Invalidate(FALSE);

	// GetParentFrame : ���� viewâ�� �ѷ��ΰ� �ִ� ���� FrameWnd�� ��ȯ
	// CMainFrame*	pMain = dynamic_cast<CMainFrame*>(GetParentFrame());
	

	

}

// ������ �������� �̿��Ͽ� Ŭ���� Ÿ���� �̹����� ��ü�϶�

// y = ax + b

// a : ����
// b : y����

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnMouseMove(nFlags, point);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		// AfxGetApp : ���� �����带 ���� �ִ� ���� ���� app�� ��ȯ
		CMainFrame*	pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		//CMyform*	pMyForm = dynamic_cast<CMyform*>(pMain->m_SecondSplitter.GetPane(1, 0));

		//CMapTool*	pMapTool = &(pMyForm->m_MapTool);

		/*m_pMyTerrain->Tile_Change(D3DXVECTOR3(point.x,
											  point.y, 
											  0.f), pMapTool->m_iDrawID);*/

		// Invalidate : ȣ�� �� �����쿡 WM_PAINT�� WM_ERASEBKGND �޼����� �߻� ��Ŵ, �̶� OnDraw �Լ��� �ٽ� �� �� ȣ��

		// TRUE : WM_PAINT�� WM_ERASEBKGND�� �� �� �߻�
		// FALSE : WM_PAINT�� �޽����� �߻�

		Invalidate(FALSE);
	}

}
