#pragma once
#include "afxdialogex.h"

class CCPlayerTool;
class CCWaterBallonTool;
// CCharacterTool 대화 상자

class CCharacterTool : public CDialog
{
	DECLARE_DYNAMIC(CCharacterTool)

public:
	CCharacterTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCharacterTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARACTERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


public:
	CTabCtrl m_Tab;

	CCPlayerTool* m_Player;
	CCWaterBallonTool* m_Water;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChange(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void PostNcDestroy();
};
