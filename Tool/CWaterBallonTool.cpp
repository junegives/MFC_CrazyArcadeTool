// CWaterBallonTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CWaterBallonTool.h"
#include "TextureMgr.h"
//#include <atlimage.h>

// CCWaterBallonTool 대화 상자

IMPLEMENT_DYNAMIC(CCWaterBallonTool, CDialog)

CCWaterBallonTool::CCWaterBallonTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_WATERBALLOON, pParent)
	/*, m_wateraniView(nullptr)*/
{

}

CCWaterBallonTool::~CCWaterBallonTool()
{
}

void CCWaterBallonTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTRLWATER, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT_ITEM, m_EditItem);
	DDX_Control(pDX, IDC_WATERPICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CCWaterBallonTool, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTRLWATER, &CCWaterBallonTool::OnItemchangedListCtrlwater)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCWaterBallonTool 메시지 처리기


BOOL CCWaterBallonTool::OnInitDialog()
{

	CDialog::OnInitDialog();

	vector<CString> vecImgPath;

	vecImgPath = CTextureMgr::Get_Instance()->GetImgPath(L"../Data/ImgPath.txt", L"WaterBalloon");

	if (vecImgPath.size() == 0)
		return false;

	for (auto& iter : vecImgPath)
	{
		TCHAR		szFileName[MIN_STR] = L"";
		CString		strFileName = PathFindFileName(iter);
		CString		strFilePath = iter;


		lstrcpy(szFileName, strFileName);

		// 파일의 확장자 명을 제거하는 함수
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapWaterBalloon.find(strFileName);

		if (iter == m_MapWaterBalloon.end())
		{
			CImage* pImage = new CImage;

			pImage->Load(strFilePath);

			m_MapWaterBalloon.insert({ strFileName, pImage });
		}
	}

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(TRUE);


	m_ImageList.Create(72, 76, ILC_COLOR16/* | ILC_MASK*/, 1, 1);

	//int iIndex = 0;

	//for (auto& iter : m_MapWaterBalloon)
	//{
	//	CBitmap bit;

	//	bit.Attach((&iter)->second);

	//	m_ImageList.Add(&bit, RGB(255, 255, 255));

	//	//CString str;
	//	//str.Replace((&iter)->first, _T("0"));
	//	//str.Replace((&iter)->first, _T("1"));
	//	//str.Replace((&iter)->first, _T("2"));

	//	m_ListCtrl.InsertItem(iIndex, (&iter)->first, iIndex);

	//	iIndex++;
	//}
	//m_ListCtrl.SetImageList(&m_ImageList, LVSIL_NORMAL);

#pragma region 하드주소

	TCHAR szPath[MAX_PATH] = L"../Image/WaterBalloon/Cottoncandy/Cottoncandy0.png";

	CImage pngImage;

	CBitmap bit;

	pngImage.Load(szPath);
	bit.Attach(pngImage);

	//CBitmap* Bit = CBitmap::FromHandle(pngImage);

	m_ImageList.Add(&bit, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(0, L"Cottoncandy", 0);

	//lstrcpy(L"../Image/WaterBalloon/Blueblock/Blueblock01.png", szPath);

	TCHAR szPath1[MAX_PATH] = L"../Image/WaterBalloon/Blueblock/Blueblock0.png";
	
	CImage pngImage1;

	CBitmap bit1;

	pngImage1.Load(szPath1);

	bit1.Attach(pngImage1);

	m_ImageList.Add(&bit1, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(1, L"Blueblock", 1);

	TCHAR szPath2[MAX_PATH] = L"../Image/WaterBalloon/Bluestreak/Bluestreak0.png";

	CImage pngImage2;

	CBitmap bit2;

	pngImage2.Load(szPath2);

	bit2.Attach(pngImage2);

	m_ImageList.Add(&bit2, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(2, L"Bluestreak", 2);

	TCHAR szPath3[MAX_PATH] = L"../Image/WaterBalloon/Greenheart/Greenheart0.png";

	CImage pngImage3;

	CBitmap bit3;

	pngImage3.Load(szPath3);

	bit3.Attach(pngImage3);

	m_ImageList.Add(&bit3, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(3, L"Greenheart", 3);

	TCHAR szPath4[MAX_PATH] = L"../Image/WaterBalloon/Greenstreak/Greenstreak0.png";

	CImage pngImage4;

	CBitmap bit4;

	pngImage4.Load(szPath4);

	bit4.Attach(pngImage4);

	m_ImageList.Add(&bit4, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(4, L"Greenstreak", 4);

	//TCHAR szPath4[MAX_PATH] = L"../Image/WaterBalloon/Greenstreak/Greenstreak0.png";

	//CImage pngImage4;

	//CBitmap bit4;

	//pngImage4.Load(szPath4);

	//bit4.Attach(pngImage4);

	//m_ImageList.Add(&bit4, RGB(255, 255, 255));

	//m_ListCtrl.InsertItem(4, L"Greenstreak", 4);

	//Orangeblock
	TCHAR szPath5[MAX_PATH] = L"../Image/WaterBalloon/Orangeblock/Orangeblock0.png";

	CImage pngImage5;

	CBitmap bit5;

	pngImage5.Load(szPath5);

	bit5.Attach(pngImage5);

	m_ImageList.Add(&bit5, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(5, L"Orangeblock", 5);

	TCHAR szPath6[MAX_PATH] = L"../Image/WaterBalloon/Redblock/Redblock0.png";

	CImage pngImage6;

	CBitmap bit6;

	pngImage6.Load(szPath6);

	bit6.Attach(pngImage6);

	m_ImageList.Add(&bit6, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(6, L"Redblock", 6);

	TCHAR szPath7[MAX_PATH] = L"../Image/WaterBalloon/Redheart/Redheart0.png";

	CImage pngImage7;

	CBitmap bit7;

	pngImage7.Load(szPath7);

	bit7.Attach(pngImage7);

	m_ImageList.Add(&bit7, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(7, L"Redheart", 7);

	TCHAR szPath8[MAX_PATH] = L"../Image/WaterBalloon/Redstreak/Redstreak0.png";

	CImage pngImage8;

	CBitmap bit8;

	pngImage8.Load(szPath8);

	bit8.Attach(pngImage8);

	m_ImageList.Add(&bit8, RGB(255, 255, 255));

	m_ListCtrl.InsertItem(8, L"Redstreak", 8);

	m_ListCtrl.SetImageList(&m_ImageList, LVSIL_NORMAL);
#pragma endregion 하드주소


	SetTimer(1, 200, NULL);
	//SetTimer(2, 250, NULL);
	//CCreateContext pContext;
	//CWnd* pFrameWnd = this;

	//pContext.m_pCurrentDoc = new CDocument;
	//pContext.m_pNewViewClass = RUNTIME_CLASS(CWaterAniView);

		//CWaterAniView* pWaterView = (CWaterAniView*)((CFrameWnd*)pFrameWnd)->CreateView(&pContext);
	//ASSERT(pWaterView);
	//pWaterView->ShowWindow(SW_NORMAL);

	//pWaterView->MoveWindow(CRect(400, 20, 600, 250));

#pragma region 일단 뷰 하지마
	//m_WateraniView = new CWaterAniView;

	//m_WateraniView->Create(NULL, L"", WS_CHILD | WS_BORDER | WS_VISIBLE, CRect(400, 20, 600, 250), this, 50001);

	//m_WateraniView->OnInitialUpdate();
#pragma endregion 일단 뷰 하지마

	UpdateData(FALSE);

	//CRuntimeClass* pObject;
	//pObject = RUNTIME_CLASS(CWaterAniView);
	//CWaterAniView* pView = (CWaterAniView*)pObject->CreateObject();

	//if (!pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
	//	CRect(400, 20, 600, 250), this, AFX_IDW_PANE_FIRST, NULL))
	//{
	//	TRACE0("Failed");
	//	return -1;
	//}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCWaterBallonTool::OnItemchangedListCtrlwater(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (pNMLV && pNMLV->uNewState == (UINT)(LVIS_FOCUSED | LVIS_SELECTED))
	{
		int iItem = pNMLV->iItem;

		m_strFind = m_ListCtrl.GetItemText(iItem, 0);

		//임시 클릭한 아이템이 무엇인지 알기 위해 에딧 컨트롤 설정
		CString str;
		str.Format(_T("%d"), iItem);
		
		m_EditItem.SetWindowTextW(str);

		m_iImageCount = 0;
	}

	*pResult = 0;
}

//다이얼로그에서 타이머를 활용하기 위함
void CCWaterBallonTool::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
	case 1:
		Update_Image();
		break;
	case 2:
		Udate_Count();
	default:
		break;
	}

	CDialog::OnTimer(nIDEvent);
}


void CCWaterBallonTool::OnDestroy()
{
	CDialog::OnDestroy();

	//Safe_Delete(m_WateraniView);

	for_each(m_MapWaterBalloon.begin(), m_MapWaterBalloon.end(), [](auto& MyPair) {

		Safe_Delete(MyPair.second);
		});

	m_MapWaterBalloon.clear();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CCWaterBallonTool::Update_Image()
{
	UpdateData(TRUE);
	CString		conversion;
	conversion.Format(_T("%d"), m_iImageCount);
	CString szFindName;

	szFindName = m_strFind + conversion;

	auto	iter = m_MapWaterBalloon.find(szFindName);

	if (iter == m_MapWaterBalloon.end())
		return;

	m_Picture.SetBitmap(*(iter->second));

	if (m_iImageCount < 3)
	{
		m_iImageCount++;
	}
	if (m_iImageCount == 3)
	{
		m_iImageCount = 0;
	}

	//if (m_iImageCount < 3 && m_bFrame == false)
	//{
	//	m_iImageCount++;
	//	//return;
	//	if (m_iImageCount == 3)
	//	{
	//		m_bFrame = true;
	//	}

	//}

	//if (m_iImageCount <= 3 && m_bFrame == true)
	//{
	//	m_iImageCount--;
	//	if (m_iImageCount == 0)
	//		m_bFrame = false;
	//}

	//m_strFind = L"";

	UpdateData(FALSE);
}

void CCWaterBallonTool::Udate_Count()
{
	//if (m_iImageCount < 3)
	//{
	//	m_iImageCount++;
	//	//return;
	//}

	//if (m_iImageCount == 3)
	//{
	//	m_iImageCount = 0;
	//}
}
