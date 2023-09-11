#pragma once
#include "afxwin.h"
#include <atlimage.h>


// CMapTool 대화 상자입니다.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public	:
	afx_msg void OnListBox();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void	Horizontal_Scroll();
	afx_msg void OnDestroy();

public:
	CListBox m_ListBox;
	CStatic m_Picture;

	bool						m_bTileSelected = false;
	map<CString, CImage*>		m_MapPngImg;
	CString						m_strStateKey = L"Cemetory";
	int							m_iDrawID = 5;
	afx_msg void OnSaveData();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
