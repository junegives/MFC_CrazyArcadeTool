#pragma once
#include "afxdialogex.h"


// CBlockTool 대화 상자

class CBlockTool : public CDialog
{
	DECLARE_DYNAMIC(CBlockTool)

public:
	CBlockTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBlockTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CBLOCKTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnListBox();
	afx_msg void OnDropFiles(HDROP hDropInfo);

public:
	CListBox m_ListBox;
	CStatic m_Picture;
	CButton m_Radio_Move[2];
	CButton m_Radio_Burst[2];

	map<CString, CImage*>		m_MapPngImg;
};
