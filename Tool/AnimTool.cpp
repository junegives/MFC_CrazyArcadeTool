// AnimTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "AnimTool.h"
#include "TextureMgr.h"


// CAnimTool 대화 상자

IMPLEMENT_DYNAMIC(CAnimTool, CDialog)

CAnimTool::CAnimTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ANIMTOOL, pParent)
{

}

CAnimTool::~CAnimTool()
{
}

void CAnimTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREEOBJECT, m_TreeBox);
	DDX_Control(pDX, IDC_LISTSTATE, m_StateList);
	DDX_Control(pDX, IDC_LISTFILE, m_FileList);
	DDX_Control(pDX, IDC_FILEIMAGE, m_FileImage);
	DDX_Control(pDX, IDC_EDITFRAMESPEED, m_EditFrameSpeed);
	DDX_Control(pDX, IDC_SLIDERFRAMESPEED, m_SlideFrameSpeed);
	DDX_Control(pDX, IDC_LISTANIM, m_ListAnim);
	DDX_Control(pDX, IDC_IMGCOLLIDERMOVE, m_ImgColliderMove);
}


BEGIN_MESSAGE_MAP(CAnimTool, CDialog)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_ACTIVATE()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREELIST, &CAnimTool::OnSelObject)
	ON_LBN_SELCHANGE(IDC_LISTSTATE, &CAnimTool::OnStateList)
	ON_LBN_SELCHANGE(IDC_LISTFILE, &CAnimTool::OnFileList)
	ON_WM_TIMER()
	ON_EN_UPDATE(IDC_EDITFRAMESPEED, &CAnimTool::OnEditFameSpeedUpdate)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERFRAMESPEED, &CAnimTool::OnNMCustomdrawSliderframespeed)
	ON_BN_CLICKED(IDC_BTNANIMSAVE, &CAnimTool::OnBtnSave)
	ON_BN_CLICKED(IDC_BTNANIMLOAD, &CAnimTool::OnBtnLoad)
	ON_BN_CLICKED(IDC_BTNCREATEANIM, &CAnimTool::OnBtnCreate)
	ON_LBN_SELCHANGE(IDC_LISTANIM, &CAnimTool::OnAnimList)
	ON_BN_CLICKED(IDC_BTNCCOLLIDER, &CAnimTool::OnBtnCollider)
	ON_BN_CLICKED(IDC_BTNSPEED, &CAnimTool::OnBtnSpeed)
END_MESSAGE_MAP()


// CAnimTool 메시지 처리기


BOOL CAnimTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetFont();

	hRoot1 = m_TreeBox.InsertItem(L"Player", NULL, NULL);
	hRoot2 = m_TreeBox.InsertItem(L"Monster", NULL, NULL);
	hRoot3 = m_TreeBox.InsertItem(L"WaterBallon", NULL, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAnimTool::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.MoveTo(700, 50);
	dc.LineTo(700, 630);
}

void CAnimTool::SetFont()
{
	//폰트 변수 선언
	CFont fontLarge, fontMedium, fontSmall;

	//폰트 생성
	fontLarge.CreateFontW(
		30,                            // 글자높이
		10,                            // 글자너비
		0,                            // 출력각도
		0,                            // 기준 선에서의각도
		FW_HEAVY,                    // 글자굵기
		FALSE,                        // Italic 적용여부
		FALSE,                        // 밑줄적용여부
		FALSE,                        // 취소선적용여부
		DEFAULT_CHARSET,            // 문자셋종류
		OUT_DEFAULT_PRECIS,            // 출력정밀도
		CLIP_CHARACTER_PRECIS,        // 클리핑정밀도
		PROOF_QUALITY,                // 출력문자품질
		DEFAULT_PITCH,                // 글꼴Pitch
		L"궁서"                // 글꼴
	);

	fontMedium.CreateFontW(
		25,                            // 글자높이
		9,                            // 글자너비
		0,                            // 출력각도
		0,                            // 기준 선에서의각도
		FW_HEAVY,                    // 글자굵기
		FALSE,                        // Italic 적용여부
		FALSE,                        // 밑줄적용여부
		FALSE,                        // 취소선적용여부
		DEFAULT_CHARSET,            // 문자셋종류
		OUT_DEFAULT_PRECIS,            // 출력정밀도
		CLIP_CHARACTER_PRECIS,        // 클리핑정밀도
		PROOF_QUALITY,                // 출력문자품질
		DEFAULT_PITCH,                // 글꼴Pitch
		L"궁서"                // 글꼴
	);

	fontSmall.CreateFontW(
		18,                            // 글자높이
		8,                            // 글자너비
		0,                            // 출력각도
		0,                            // 기준 선에서의각도
		FW_LIGHT,                    // 글자굵기
		FALSE,                        // Italic 적용여부
		FALSE,                        // 밑줄적용여부
		FALSE,                        // 취소선적용여부
		DEFAULT_CHARSET,            // 문자셋종류
		OUT_DEFAULT_PRECIS,            // 출력정밀도
		CLIP_CHARACTER_PRECIS,        // 클리핑정밀도
		PROOF_QUALITY,                // 출력문자품질
		DEFAULT_PITCH,                // 글꼴Pitch
		L"궁서"                // 글꼴
	);

	//컨트롤의 폰트를 변경한다.
	GetDlgItem(IDC_TEXTOBJECT)->SetFont(&fontLarge);
	GetDlgItem(IDC_TEXTSTATE)->SetFont(&fontLarge);
	GetDlgItem(IDC_TEXTLIST)->SetFont(&fontLarge);

	GetDlgItem(IDC_TEXTCOLLIDER)->SetFont(&fontLarge);

	GetDlgItem(IDC_GROUPCOLLIDER1)->SetFont(&fontMedium);
	GetDlgItem(IDC_GROUPCOLLIDER2)->SetFont(&fontMedium);

	GetDlgItem(IDC_TEXTCENTER1)->SetFont(&fontMedium);
	GetDlgItem(IDC_TEXTCENTER2)->SetFont(&fontMedium);
	GetDlgItem(IDC_TEXTSIZE1)->SetFont(&fontMedium);
	GetDlgItem(IDC_TEXTSIZE2)->SetFont(&fontMedium);

	GetDlgItem(IDC_TEXTCENTERX1)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTCENTERX2)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTSIZEX1)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTSIZEX2)->SetFont(&fontSmall);

	GetDlgItem(IDC_TEXTCENTERY1)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTCENTERY2)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTSIZEY1)->SetFont(&fontSmall);
	GetDlgItem(IDC_TEXTSIZEY2)->SetFont(&fontSmall);

	GetDlgItem(IDC_TEXTANMIATION)->SetFont(&fontLarge);

	GetDlgItem(IDC_TEXTFRAMESPEED)->SetFont(&fontMedium);

	GetDlgItem(IDC_CHECKSHOWCOLLIDER1)->SetFont(&fontSmall);
	GetDlgItem(IDC_CHECKSHOWCOLLIDER2)->SetFont(&fontSmall);


	fontLarge.Detach();
	fontMedium.Detach();
	fontSmall.Detach();
}

void CAnimTool::GetImg(const wstring& pObjKey, HTREEITEM hRoot)
{
	HTREEITEM hObjKey;

	vector<CString> vecImgPath;

	vecImgPath = CTextureMgr::Get_Instance()->GetImgPath(L"../Data/ImgPath.txt", pObjKey);
	if (vecImgPath.size() == 0)
		return;

	hObjKey = m_TreeBox.InsertItem(pObjKey.c_str(), hRoot, NULL);

	for (auto& iter : vecImgPath)
	{
		TCHAR		szFileName[MIN_STR] = L"";
		CString		strFileName = PathFindFileName(iter);
		CString		strFilePath = iter;
		TCHAR		szPathBuf[MAX_STR] = L"";

		lstrcpy(szPathBuf, strFilePath.GetString());

		PathRemoveFileSpec(szPathBuf);

		// PathFindFileName : 파일명을 찾거나 마지막 폴더명을 찾아냄
		CString strStateKey = PathFindFileName(szPathBuf);

		lstrcpy(szFileName, strFileName);

		// 파일의 확장자 명을 제거하는 함수
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage* pPngImg = new CImage;

			pPngImg->Load(strFilePath);

			m_MapPngImg.insert({ strFileName, pPngImg });
			m_mapStateFileName[strStateKey.GetString()].push_back(strFileName);
		}
	}

	return;
}


void CAnimTool::OnDestroy()
{
	for_each(m_MapPngImg.begin(), m_MapPngImg.end(), [](auto& MyPair)
		{
			MyPair.second->Destroy();
			Safe_Delete(MyPair.second);
		});

	for_each(m_vecAnim.begin(), m_vecAnim.end(), [](auto& iter)
		{
			Safe_Delete(iter);
		}); 

	m_MapPngImg.clear();
	KillTimer(1);

	CDialog::OnDestroy();

}

void CAnimTool::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

}


void CAnimTool::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	GetImg(L"Bazzi", hRoot1);
	GetImg(L"LuxuryMarid", hRoot1);
	GetImg(L"Cappi", hRoot1);

	GetImg(L"Angry", hRoot2);
	GetImg(L"MummyRed", hRoot2);
	GetImg(L"MummyWhite", hRoot2);
	GetImg(L"Zzol", hRoot2);

	GetImg(L"WaterBallon", hRoot3);

	// 프레임 속도
	m_iSpeed = 5;
	m_iTimer = (11 - m_iSpeed) * 30;

	CString strSpeed;
	strSpeed.Format(L"%d", m_iSpeed);
	m_EditFrameSpeed.SetWindowTextW(strSpeed);
	SetTimer(1, m_iTimer, NULL);

	// 프레임 슬라이더 설정
	m_SlideFrameSpeed.SetRange(1, 10);
	m_SlideFrameSpeed.SetRangeMin(1);
	m_SlideFrameSpeed.SetRangeMax(10);
	m_SlideFrameSpeed.SetPos(5);
	//눈금 설정
	m_SlideFrameSpeed.SetTicFreq(1);
	//키보드 값으로 움직일 크기 지정
	m_SlideFrameSpeed.SetLineSize(1);


	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CAnimTool::OnSelObject(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_StateList.ResetContent();
	m_FileList.ResetContent();

	m_isPlay = false;

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0; 

	HTREEITEM hSel;

	hSel = m_TreeBox.GetSelectedItem();

	if (!hSel) return;
	if (hSel == hRoot1 || hSel == hRoot2 || hSel == hRoot3) return;

	CString sSel = L"";
	sSel = m_TreeBox.GetItemText(hSel);

	vector<CString> vecImgPath;

	vecImgPath = CTextureMgr::Get_Instance()->GetImgPath(L"../Data/ImgPath.txt", sSel.GetString());
	if (vecImgPath.size() == 0)
		return;

	m_objKey = sSel;

	CString pre_strStateKey = L"";

	for (auto& iter : vecImgPath)
	{
		TCHAR		szFileName[MIN_STR] = L"";
		CString		strFileName = PathFindFileName(iter);
		CString		strFilePath = iter;
		CString		strStateKey;
		TCHAR		szPathBuf[MAX_STR] = L"";

		lstrcpy(szPathBuf, strFilePath.GetString());

		PathRemoveFileSpec(szPathBuf);

		// PathFindFileName : 파일명을 찾거나 마지막 폴더명을 찾아냄
		strStateKey = PathFindFileName(szPathBuf);

		lstrcpy(szFileName, strFileName);

		// 파일의 확장자 명을 제거하는 함수
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage* pPngImg = new CImage;

			pPngImg->Load(strFilePath);

			m_MapPngImg.insert({ strFileName, pPngImg });
			m_mapStateFileName[strStateKey.GetString()].push_back(strFileName);
		}

		if (pre_strStateKey != strStateKey)
		{
			CString CutStateKey = strStateKey;

			if (m_objKey != L"WaterBallon")
			{
				AfxExtractSubString(CutStateKey, strStateKey, 1, '_');
			}

			m_StateList.AddString(CutStateKey);
		}

		pre_strStateKey = strStateKey;
	}
}


void CAnimTool::OnStateList()
{
	m_FileList.ResetContent();

	m_isPlay = false;

	int iIndex = m_StateList.GetCurSel();

	CString		strFindName;
	CString		strFindNameCopy;

	if (LB_ERR == iIndex)
		return;

	m_StateList.GetText(iIndex, strFindName);

	if(m_objKey != L"WaterBallon")
		strFindName = m_objKey + '_' + strFindName;

	auto	iter = m_mapStateFileName.find(strFindName.GetString());

	if (iter == m_mapStateFileName.end())
		return;

	m_stateKey = strFindName;

	for (auto& iterVec : iter->second)
	{
		CString CutFileName = iterVec;

		if(m_objKey != L"WaterBallon")
		{
			CutFileName = iterVec.Right(iterVec.GetLength() - m_objKey.GetLength());
		}
		m_FileList.AddString(CutFileName);
	}

	m_imagePath = L"../image/" + m_objKey + L"/" + m_stateKey;

	m_FileList.SetCurSel(0);
	OnFileList();

	UpdateData(FALSE);
}


void CAnimTool::OnFileList()
{
	int iIndex = m_FileList.GetCurSel();

	ChangeImage(iIndex);
}


void CAnimTool::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		ChangeImage(SelNextFile());
	}

	CDialog::OnTimer(nIDEvent);
}

int CAnimTool::SelNextFile()
{
	if (m_FileList.GetCount() == 0 || !m_isPlay) return -1;

	int iIndex = m_FileList.GetCurSel();

	iIndex++;

	if (m_FileList.GetCount() <= iIndex)
		iIndex = 0;

	m_FileList.SetCurSel(iIndex);

	return iIndex;
}

void CAnimTool::ChangeImage(int iIndex)
{
	CString		strFindName;
	CString		strFindNameCopy;

	if (LB_ERR == iIndex)
		return;

	m_FileList.GetText(iIndex, strFindName);

	if (m_objKey != L"WaterBallon")
		strFindName = m_objKey + strFindName;

	auto	iter = m_MapPngImg.find(strFindName);

	if (iter == m_MapPngImg.end())
		return;

	m_FileImage.SetBitmap(*(iter->second));

	UpdateData(FALSE);
}


void CAnimTool::OnEditFameSpeedUpdate()
{
	if (m_objKey == L"") return;

	UpdateData(TRUE);

	CString strEdit;
	m_iSpeed = GetDlgItemInt(IDC_EDITFRAMESPEED);
	m_SlideFrameSpeed.SetPos(m_iSpeed);

	// 전체를 선택
	m_EditFrameSpeed.SetSel(0, -1);

	// 현재의 데이터로 다시 치환
	CString strSpeed;
	strSpeed.Format(L"%d", m_iSpeed);
	m_EditFrameSpeed.ReplaceSel(strSpeed);

	//--> 포커스를 에디트 박스로 설정
	m_EditFrameSpeed.SetFocus();

	UpdateData(FALSE);
}

void CAnimTool::OnNMCustomdrawSliderframespeed(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData(TRUE);
	m_iSpeed = m_SlideFrameSpeed.GetPos();
	m_iTimer = (11 - m_iSpeed) * 30;

	CString strSpeed;
	strSpeed.Format(L"%d", m_iSpeed);
	m_EditFrameSpeed.SetWindowTextW(strSpeed);
	UpdateData(FALSE);

	SetTimer(1, m_iTimer, NULL);

	*pResult = 0;
}


void CAnimTool::OnBtnSave()
{
	CFileDialog		Dlg(FALSE,	// 모드 지정(true 열기, false 다른 이름으로 저장)
		L"dat",	// 기본 확장자명
		L"*.dat", // 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	//  OFN_HIDEREADONLY : 읽기 전용 체크박스 숨김, OFN_OVERWRITEPROMPT : 중복파일 저장 시 경고 메세지 띄움
		L"Data File(*.dat) | *.dat ||", // 대화 상자에 표시될 파일 형식, 콤보 박스에 출력될 문자열 | 실제 사용할 필터링 문자열
		this);	// 부모 윈도우 주소

	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	// szPath = 0x012fe070 L"C:\\GitHub\\CrazyArcadeTool\\Tool"

	// PathRemoveFileSpec : 전체 경로 중 맨 마지막 경로를 잘라냄
	PathRemoveFileSpec(szPath);
	// szPath = 0x012fe070 L"C:\\GitHub\\CrazyArcadeTool"

	lstrcat(szPath, L"\\Data");
	// szPath = 0x012fe070 L"C:\\GitHub\\CrazyArcadeTool\\Data"

	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : 대화 상자를 실행
	if (IDOK == Dlg.DoModal())
	{
		CString		str = Dlg.GetPathName().GetString();
		// str = L"C:\\GitHub\\CrazyArcadeTool\\Data\\Test.dat"

		const TCHAR* pGetPath = str.GetString();
		// pGetPath = 0x0e7eda10 L"C:\\GitHub\\CrazyArcadeTool\\Data\\Test.dat"

		HANDLE	hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		if (m_vecAnim.empty())
			return;

		DWORD	dwByte(0), dwStrByte(0);

		for (auto& iter : m_vecAnim) {
			dwStrByte = sizeof(wstring) * (iter->wstrObjectKey.length() + 1);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, iter->wstrObjectKey.c_str(), dwStrByte, &dwByte, nullptr);
			dwStrByte = sizeof(wstring) * (iter->wstrStateKey.length() + 1);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, iter->wstrStateKey.c_str(), dwStrByte, &dwByte, nullptr);

			WriteFile(hFile, &(iter->iFrameSpeed), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(iter->isLoop), sizeof(BOOL), &dwByte, nullptr);
			WriteFile(hFile, &(iter->vPos), sizeof(D3DXVECTOR3), &dwByte, nullptr);
			WriteFile(hFile, &(iter->iFrameCnt), sizeof(int), &dwByte, nullptr);
		}


		CloseHandle(hFile);
	}
}

void CAnimTool::OnBtnLoad()
{
	UpdateData(TRUE);

	CFileDialog Dig(TRUE,
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) | *.dat ||",
		this);

	TCHAR szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"Data");

	Dig.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dig.DoModal())
	{
		//먼저 원래 들어있던 애니메이션 데이터 제거
		for (auto& iter : m_vecAnim)
			delete iter;

		m_vecAnim.clear();

		//리스트 박스 목록 초기화
		m_ListAnim.ResetContent();

		CString str = Dig.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte(0), dwStrByte(0);

		ANIMINFO tData{};

		while (true)
		{
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			
			TCHAR* pObjKey = new TCHAR[dwStrByte];
			ReadFile(hFile, pObjKey, dwStrByte, &dwByte, nullptr);

			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

			TCHAR* pStateKey = new TCHAR[dwStrByte];
			ReadFile(hFile, pStateKey, dwStrByte, &dwByte, nullptr);

			ReadFile(hFile, &(tData.iFrameSpeed), sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(tData.isLoop), sizeof(BOOL), &dwByte, nullptr);
			ReadFile(hFile, &(tData.vPos), sizeof(D3DXVECTOR3), &dwByte, nullptr);
			ReadFile(hFile, &(tData.iFrameCnt), sizeof(int), &dwByte, nullptr);


			if (0 == dwByte)
			{
				delete[]pObjKey;
				delete[]pStateKey;
				break;
			}

			ANIMINFO* pData = new ANIMINFO;
			pData->wstrObjectKey = pObjKey;
			pData->wstrStateKey = pStateKey;
			pData->iFrameSpeed = tData.iFrameSpeed;
			pData->isLoop = tData.isLoop;
			pData->vPos = tData.vPos;
			pData->iFrameCnt = tData.iFrameCnt;

			m_vecAnim.push_back(pData);

			m_ListAnim.AddString(pData->wstrStateKey.c_str());

			delete[]pObjKey;
			delete[]pStateKey;
		}


		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CAnimTool::OnBtnCreate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_isPlay = true;
	m_ListAnim.AddString(m_stateKey);

	// 현재 애니메이션 구조체 생성
	ANIMINFO* tAnimInfo = new ANIMINFO;

	tAnimInfo->wstrObjectKey = m_objKey;
	tAnimInfo->wstrStateKey = m_stateKey;
	tAnimInfo->iFrameSpeed = GetDlgItemInt(IDC_EDITFRAMESPEED);
	tAnimInfo->iFrameCnt = m_FileList.GetCount();

	m_vecAnim.push_back(tAnimInfo);

	m_ListAnim.SetCurSel(m_ListAnim.GetCount() - 1);
}


void CAnimTool::OnCancel()
{
	m_isPlay = false;

	CDialog::OnCancel();
}


void CAnimTool::OnAnimList()
{
	//vector<CString> vecImgPath;

	//vecImgPath = CTextureMgr::Get_Instance()->GetImgPath(L"../Data/ImgPath.txt", sSel.GetString());
	//if (vecImgPath.size() == 0)
	//	return;

	//CString strSelState = L"";
	//int iIndex = m_ListAnim.GetCurSel();
	//m_ListAnim.GetText(iIndex, strSelState);

	//for (auto& iter : m_vecAnim)
	//{
	//	if (iter->wstrStateKey.c_str() == strSelState)
	//	{
	//		for (auto& iter : vecImgPath)
	//		{
	//			TCHAR		szFileName[MIN_STR] = L"";
	//			CString		strFileName = PathFindFileName(iter);
	//			CString		strFilePath = iter;
	//			CString		strStateKey;
	//			TCHAR		szPathBuf[MAX_STR] = L"";

	//			lstrcpy(szPathBuf, strFilePath.GetString());

	//			PathRemoveFileSpec(szPathBuf);

	//			// PathFindFileName : 파일명을 찾거나 마지막 폴더명을 찾아냄
	//			strStateKey = PathFindFileName(szPathBuf);

	//			lstrcpy(szFileName, strFileName);

	//			// 파일의 확장자 명을 제거하는 함수
	//			PathRemoveExtension(szFileName);

	//			strFileName = szFileName;

	//			auto	iter = m_MapPngImg.find(strFileName);

	//			if (iter == m_MapPngImg.end())
	//			{
	//				CImage* pPngImg = new CImage;

	//				pPngImg->Load(strFilePath);

	//				m_MapPngImg.insert({ strFileName, pPngImg });
	//				m_mapStateFileName[strStateKey.GetString()].push_back(strFileName);
	//			}

	//			CString CutStateKey = strStateKey;

	//			if (m_objKey != L"WaterBallon")
	//			{
	//				AfxExtractSubString(CutStateKey, strStateKey, 1, '_');
	//			}

	//			m_StateList.AddString(CutStateKey);
	//		}
	//	}
	//}
}


void CAnimTool::OnBtnCollider()
{
	//CString		strFindName;
	//CString		strFindNameCopy;

	//if (LB_ERR == iIndex)
	//	return;

	//m_FileList.GetText(iIndex, strFindName);

	//if (m_objKey != L"WaterBallon")
	//	strFindName = m_objKey + strFindName;

	//auto	iter = m_MapPngImg.find(strFindName);

	//if (iter == m_MapPngImg.end())
	//	return;

	//m_FileImage.SetBitmap(*(iter->second));
	//m_ImgColliderMove
}


void CAnimTool::OnBtnSpeed()
{
	m_vecAnim[m_ListAnim.GetCurSel()]->iFrameSpeed = GetDlgItemInt(IDC_EDITFRAMESPEED);
}
