
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView() : m_pMyTerrain(nullptr), m_pMyBlockTerrain(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
}

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// AfxGetMainWnd : 현재의 메인 윈도우를 반환하는 전역 함수
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};

	// GetWindowRect : 현재 윈도우의 정보를 얻어와 rect에 채워줌
	pMainFrm->GetWindowRect(&rcWnd);


	// SetRect : 렉트의 정보를 기록하는 함수

	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};

	// GetClientRect : 현재 view 창의 렉트 정보를 얻어오는 함수
	GetClientRect(&rcMainView);

	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	// SetWindowPos : 매개 변수대로 윈도우의 위치와 크기를 조정하는 함수
	// SetWindowPos(배치할 윈도우의 Z순서에 대한 포인터, X, Y 좌표, 가로 크기, 세로 크기, 배치할 윈도우의 크기 및 위치 지정 옵션)
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

	m_pMyBlockTerrain = new CMyBlockTerrain;

	if (FAILED(m_pMyBlockTerrain->Initialize()))
	{
		AfxMessageBox(L"Block Terrain Initialize Failed");
		return;
	}

	m_pMyBlockTerrain->Set_MainView(this);

}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDevice::Get_Instance()->Render_Begin();

	m_pMyTerrain->Render();

	m_pMyBlockTerrain->Render();

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());


	CMapTool* pMapTool = pMain->m_MapTool;
	if (pMapTool->IsWindowVisible() && pMapTool->m_bTileSelected)
	{
		m_pMyTerrain->Mouse_Render();
	}
	

	CBlockTool* pBlockTool = pMain->m_BlockTool;
	if (pBlockTool->IsWindowVisible())
	{
		m_pMyBlockTerrain->Mouse_Render();
	}


	CDevice::Get_Instance()->Render_End();
}

#pragma region 숨김

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}
// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


#pragma endregion 숨김



void CToolView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	Safe_Delete(m_pMyTerrain);
	Safe_Delete(m_pMyBlockTerrain);

	CTextureMgr::Get_Instance()->Destroy_Instance();
	CDevice::Get_Instance()->Destroy_Instance();
}


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO : 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);


	// AfxGetApp : 메인 스레드를 갖고 있는 현재 메인 app을 반환
	CMainFrame*	pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

	CMapTool*	pMapTool = pMain->m_MapTool;

	CBlockTool* pBlockTool = pMain->m_BlockTool;

	if (pMapTool->IsWindowVisible() && pMapTool->m_bTileSelected)
	{
		m_pMyTerrain->Tile_Change(D3DXVECTOR3(point.x,
			point.y,
			0.f),
			pMapTool->m_strStateKey,
			pMapTool->m_iDrawID);
	}

	if (pBlockTool->IsWindowVisible())
	{
		m_pMyBlockTerrain->Tile_Change(D3DXVECTOR3(point.x + GetScrollPos(0),
			point.y + GetScrollPos(1), 0.f), D3DXVECTOR3(pBlockTool->m_ImageWidth, pBlockTool->m_ImageHeight, 0.f)
			, pBlockTool->m_Option_Move, pBlockTool->m_Option_Burst,
			pBlockTool->m_iDrawID);
	}

	// Invalidate : 호출 시 윈도우에 WM_PAINT와 WM_ERASEBKGND 메세지를 발생 시킴, 이때 OnDraw 함수를 다시 한 번 호출

	// TRUE : WM_PAINT와 WM_ERASEBKGND가 둘 다 발생
	// FALSE : WM_PAINT와 메시지만 발생

	Invalidate(FALSE);

	// GetParentFrame : 현재 view창을 둘러싸고 있는 상위 FrameWnd를 반환
	// CMainFrame*	pMain = dynamic_cast<CMainFrame*>(GetParentFrame());
	
}

// 직선의 방정식을 이용하여 클릭한 타일의 이미지를 교체하라

// y = ax + b

// a : 기울기
// b : y절편

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		// AfxGetApp : 메인 스레드를 갖고 있는 현재 메인 app을 반환
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

		CMapTool* pMapTool = pMain->m_MapTool;
		CBlockTool* pBlockTool = pMain->m_BlockTool;

		
		if (pMapTool->IsWindowVisible() && pMapTool->m_bTileSelected)
		{
			m_pMyTerrain->Tile_Preview(D3DXVECTOR3(point.x, point.y, 0.f),
										pMapTool->m_strStateKey, pMapTool->m_iDrawID);

			m_pMyTerrain->Tile_Change(D3DXVECTOR3(point.x,
				point.y,
				0.f),
				pMapTool->m_strStateKey,
				pMapTool->m_iDrawID);
		}


		if (pBlockTool->IsWindowVisible())
		{

			if (pBlockTool->m_bFirst)
			{
				m_pMyBlockTerrain->Tile_Move(D3DXVECTOR3(point.x,
					point.y,
					0.f), D3DXVECTOR3(pBlockTool->m_ImageWidth, pBlockTool->m_ImageHeight, 0.f)
					, pBlockTool->m_iDrawID);
			}

			m_pMyBlockTerrain->Tile_Change(D3DXVECTOR3(point.x + GetScrollPos(0),
				point.y + GetScrollPos(1), 0.f), D3DXVECTOR3(pBlockTool->m_ImageWidth, pBlockTool->m_ImageHeight, 0.f)
				, pBlockTool->m_Option_Move, pBlockTool->m_Option_Burst,
				pBlockTool->m_iDrawID);
		}

		// Invalidate : 호출 시 윈도우에 WM_PAINT와 WM_ERASEBKGND 메세지를 발생 시킴, 이때 OnDraw 함수를 다시 한 번 호출

		// TRUE : WM_PAINT와 WM_ERASEBKGND가 둘 다 발생
		// FALSE : WM_PAINT와 메시지만 발생

		Invalidate(FALSE);
	}
	else
	{
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

		CMapTool* pMapTool = pMain->m_MapTool;
		CBlockTool* pBlockTool = pMain->m_BlockTool;

		if (pMapTool->IsWindowVisible() && pMapTool->m_bTileSelected)
		{
			m_pMyTerrain->Tile_Preview(D3DXVECTOR3(point.x, point.y, 0.f),
				pMapTool->m_strStateKey, pMapTool->m_iDrawID);
		}

		if (pBlockTool->IsWindowVisible())
		{
			if (pBlockTool->m_bFirst)
			{
				m_pMyBlockTerrain->Tile_Move(D3DXVECTOR3(point.x,
					point.y,
					0.f), D3DXVECTOR3(pBlockTool->m_ImageWidth, pBlockTool->m_ImageHeight, 0.f)
					, pBlockTool->m_iDrawID);
			}
		}

		Invalidate(FALSE);
	}

}
