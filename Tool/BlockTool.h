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
	afx_msg void OnDestroy();

public:
	CListBox m_ListBox;
	CStatic m_Picture;
	CButton m_Radio_Move[2];
	CButton m_Radio_Burst[2];

	map<CString, CImage*>		m_MapPngImg;

	int m_iDrawID = 0;
	bool m_bFirst = false;

	float m_ImageWidth = 0;
	float m_ImageHeight = 0;

	BYTE  m_Option_Move = 0;
	BYTE  m_Option_Burst = 0;

};
