#pragma once

#include "UnitTool.h"
#include "MapTool.h"

// CMyform �� ���Դϴ�.

class CMyform : public CFormView
{
	DECLARE_DYNCREATE(CMyform)

protected:
	CMyform();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyform();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUnitTool();

public:
	CFont		m_Font;
	CUnitTool	m_UnitTool;
	CMapTool	m_MapTool;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnMapTool();
};


