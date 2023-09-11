
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once

#include "Myform.h"
#include "ToolView.h"
#include "BlockTool.h"
#include "AnimTool.h"
#include "CharacterTool.h"

class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

public:
	// CSplitterWnd : 창 분할을 위한 클래스

	CSplitterWnd			m_MainSplitter;
	CSplitterWnd			m_SecondSplitter;

	CUnitTool*	m_UnitTool;
	CMapTool*	m_MapTool;
	CBlockTool* m_BlockTool;
	CAnimTool*	m_AnimTool;
	CCharacterTool* m_CharacterTool;
	

	afx_msg void OnMapTool();
	afx_msg void OnObjectTool();
	afx_msg void OnMonsterTool();
	afx_msg void OnRoomTool();
	afx_msg void OnPlayerTool();
	afx_msg void OnAnimTool();
};


