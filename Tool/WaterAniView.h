#pragma once


// CWaterAniView 보기

class CWaterAniView : public CView
{
	DECLARE_DYNCREATE(CWaterAniView)

public:
	CWaterAniView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CWaterAniView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual void OnInitialUpdate();

public:
	map<CString, CImage*>		m_MapWaterBalloon;
	afx_msg void OnDestroy();
};


