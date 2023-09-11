#pragma once
#include "afxdialogex.h"

#include "Struct.h"

// CCPlayerTool 대화 상자

class CCPlayerTool : public CDialog
{
	DECLARE_DYNAMIC(CCPlayerTool)

public:
	CCPlayerTool(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCPlayerTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLAYER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateEditWaterLength();
	afx_msg void OnCustomdrawLengthSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnUpdateEditWaterCount();

	afx_msg void OnListBox();
	afx_msg void OnAddPlayer();
	afx_msg void OnDestroy();

	afx_msg void OnSaveData();
	afx_msg void OnLoadData();

	afx_msg void OnDeltaposSpinSpeed(NMHDR* pNMHDR, LRESULT* pResult);
public:
//	CEdit m_Nickname;

	CSliderCtrl m_CtrlwaterLength;
	int m_EditwaterLength;

	CSliderCtrl m_CtrlwaterCount;
	int m_EditwaterCount;

	CListBox m_ListBox;
	CString m_Nickname;

	map<CString, CHARACTERDATA*> m_mapCharacterData;

	CSpinButtonCtrl m_CtrlSpeed;
	int m_Speed;
};
