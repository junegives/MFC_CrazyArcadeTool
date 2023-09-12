#pragma once
#include "afxdialogex.h"

#include "WaterAniView.h"

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
	afx_msg void OnItemchangedListCtrlwater(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;

	CEdit m_EditItem;

	//추가
	CImageList m_ImageList;

public:
	CWaterAniView* m_WateraniView;
	CStatic m_Picture;

	//물풍선들의 이미지를 저장할 맵 컨테이너
	map<CString, CImage*>		m_MapWaterBalloon;

	//클릭한 이미지에 맞게 하기 위해
	CString m_strFind = L"";
	int m_iImageCount = 0;

	bool m_bFrame = false;
public:
	void Update_Image();
	void Udate_Count();
};
