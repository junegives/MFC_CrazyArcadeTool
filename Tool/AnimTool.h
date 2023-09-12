#pragma once
#include "afxdialogex.h"
#include "Include.h"


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
	afx_msg void OnPaint();
	afx_msg void OnDestroy();

	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelObject(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStateList();
	afx_msg void OnFileList();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	void SetFont();
	void GetImg(const wstring& pObjKey, HTREEITEM hRoot);
	int SelNextFile();
	void ChangeImage(int iIndex);

	CTreeCtrl m_TreeBox;
	// 파일명에 해당하는 이미지를 가지고 있는 변수
	map<CString, CImage*>			m_MapPngImg;
	// StateKey에 따른 파일명을 가지고 있는 변수
	map<wstring, vector<CString>>	m_mapStateFileName;

	HTREEITEM hRoot1, hRoot2, hRoot3;

	CListBox m_StateList;
	CListBox m_FileList;
	CStatic m_FileImage;

	CString	m_objKey;
	CString	m_stateKey;
	CString m_imagePath;

	int		m_iTimer = 100;
	CEdit m_EditFrameSpeed;
	CSliderCtrl m_SlideFrameSpeed;
	CListBox m_ListAnim;
	bool	m_isLoop = true;
	bool	m_isPlay = false;

	vector<ANIMINFO*>	m_vecAnim;

	afx_msg void OnEditFameSpeedUpdate();
	afx_msg void OnNMCustomdrawSliderframespeed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSave();
	afx_msg void OnBtnLoad();
	afx_msg void OnBtnCreate();
	virtual void OnCancel();
	afx_msg void OnAnimList();
};