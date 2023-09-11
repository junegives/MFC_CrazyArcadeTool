#pragma once
#include "afxdialogex.h"


// CAnimTool 대화 상자

class CAnimTool : public CDialog
{
	DECLARE_DYNAMIC(CAnimTool)

public:
	CAnimTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAnimTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedTextcenter1();
	afx_msg void OnEnChangeEditcentery1();
	afx_msg void OnNMCustomdrawSlidercentery1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStnClickedTextsizey2();
	afx_msg void OnPaint();

public:
	void SetFont();

	CTreeCtrl m_TreeObjectKey;
};
