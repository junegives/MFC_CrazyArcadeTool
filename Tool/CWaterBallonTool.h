#pragma once
#include "afxdialogex.h"


// CCWaterBallonTool 대화 상자

class CCWaterBallonTool : public CDialog
{
	DECLARE_DYNAMIC(CCWaterBallonTool)

public:
	CCWaterBallonTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCWaterBallonTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WATERBALLOON };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;

	//추가
	CImageList m_ImageList;
};
