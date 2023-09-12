#pragma once
#include "afxdialogex.h"

#include "Struct.h"

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

	afx_msg void OnChangeEditX();
	afx_msg void OnChangeEditY();

	afx_msg void OnBlockSave();
	afx_msg void OnBlockLoad();

public:
	void Set_VecTile(vector<TILE*>* _vecTile) { m_vecTile = _vecTile; }

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

	//이미지의 콜라이더를 설정해주기 위한 변수
	CEdit m_Collider_X;
	CEdit m_Collider_Y;

	float m_Coll_X = 0.f;
	float m_Coll_Y = 0.f;

	vector<TILE*>*		m_vecTile;

};
