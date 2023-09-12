// WaterAniView.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "WaterAniView.h"

#include "Device.h"
#include "TextureMgr.h"


// CWaterAniView

IMPLEMENT_DYNCREATE(CWaterAniView, CView)

CWaterAniView::CWaterAniView()
{

}

CWaterAniView::~CWaterAniView()
{
}

BEGIN_MESSAGE_MAP(CWaterAniView, CView)
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CWaterAniView 그리기

void CWaterAniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	CDevice::Get_Instance()->Render_Begin();

	//D3DXVECTOR3 vPos{100.f, 165.f, 0.f};

	//D3DXMATRIX		matTrans;
	//D3DXMATRIX      matWorld;

	//D3DXMatrixTranslation(&matTrans,
	//	vPos.x,
	//	vPos.y,
	//	0.f);

	//matWorld = matTrans;

	//CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"WaterBalloon", L"Blueblock", 1);

	if (pTexInfo != nullptr)
	{
		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}


	CDevice::Get_Instance()->Render_End();
}


// CWaterAniView 진단

#ifdef _DEBUG
void CWaterAniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CWaterAniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CWaterAniView 메시지 처리기


int CWaterAniView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CWaterAniView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	if (FAILED(CDevice::Get_Instance()->Init_Device()))
	{
		AfxMessageBox(L"CDevice Init FAILED");
		return;
	}

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(TEX_MULTI, L"../Image/WaterBalloon/Blueblock/Blueblock%d.png", L"WaterBalloon", L"Blueblock", 3)))
	{
		AfxMessageBox(L"Cube Texture Insert Failed");
		return;
	}




	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//vector<CString> vecImgPath;

	//vecImgPath = CTextureMgr::Get_Instance()->GetImgPath(L"../Data/ImgPath.txt", L"WaterBalloon");

	//if (vecImgPath.size() == 0)
	//	return;

	//for (auto& iter : vecImgPath)
	//{
	//	TCHAR		szFileName[MIN_STR] = L"";
	//	CString		strFileName = PathFindFileName(iter);
	//	CString		strFilePath = iter;


	//	lstrcpy(szFileName, strFileName);

	//	// 파일의 확장자 명을 제거하는 함수
	//	PathRemoveExtension(szFileName);

	//	strFileName = szFileName;

	//	auto	iter = m_MapWaterBalloon.find(strFileName);

	//	if (iter == m_MapWaterBalloon.end())
	//	{
	//		CImage* pImage = new CImage;

	//		pImage->Load(strFilePath);

	//		m_MapWaterBalloon.insert({ strFileName, pImage });
	//	}
	//}

	return;
}


void CWaterAniView::OnDestroy()
{
	CView::OnDestroy();

	for_each(m_MapWaterBalloon.begin(), m_MapWaterBalloon.end(), [](auto& MyPair) {

		Safe_Delete(MyPair.second);
		});

	m_MapWaterBalloon.clear();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
