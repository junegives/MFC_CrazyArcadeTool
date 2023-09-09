// MapTool.cpp : 구현 파일입니다.

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "MainFrm.h"
#include "ToolView.h"


// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnListBox)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnSaveData)
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.


void CMapTool::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString		strFindName;
	CString		strFindNameCopy;

	int	iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	m_ListBox.GetText(iIndex, strFindName);

	auto	iter = m_MapPngImg.find(strFindName);

	if (iter == m_MapPngImg.end())
		return;

	m_Picture.SetBitmap(*(iter->second));

	int i = 0;

	for (; i < strFindName.GetLength(); ++i)
	{
		// isdigit : 매개 변수로 전달받은 문자가 글자 형태의 문자인지 숫자 형태의 문자인지 판별하는 함수
			//       만약 숫자 형태의 글자라 판명되면 0이 아닌 값을 리턴
		if (0 != isdigit(strFindName[i]))
			break;
	}

	strFindNameCopy = strFindName;
	
	strFindName.Delete(i, i + 2);
	m_strStateKey = strFindName;

	// Delete(index, count) : index 위치로부터 카운트 만큼 문자를 삭제하는 함수
	strFindNameCopy.Delete(0, i);

	// _tstoi : 문자를 정수형으로 변환하는 함수
	m_iDrawID = _tstoi(strFindNameCopy);

	m_bTileSelected = true;

	UpdateData(FALSE);
}


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);
	
	CDialog::OnDropFiles(hDropInfo);

	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MIN_STR] = L"";

	// DragQueryFile : 드롭된 파일의 정보를 얻어오는 함수

	// 두 번째 매개 변수 : 0xffffffff(-1)을 지정하면 드롭된 파일의 개수를 반환 

	int	iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);
		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());

		// 파일의 확장자 명을 제거하는 함수
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage*		pPngImg = new CImage;

			pPngImg->Load(strRelative);
			
			m_MapPngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName);
		}		
	}	

	Horizontal_Scroll();

	m_bTileSelected = false;

	UpdateData(FALSE);
}

void CMapTool::Horizontal_Scroll()
{
	CString		strFineName;

	CSize		size;
	int			iWidth = 0;

	CDC*		pDC = m_ListBox.GetDC();

	// GetCount : 현재 리스트 박스에 있는 목록의 개수를 반환
	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strFineName);

		// GetTextExtent : 현재 문자열의 길이를 픽셀단위로 변환
		size = pDC->GetTextExtent(strFineName);

		if (size.cx > iWidth)
			iWidth = size.cx;
	}

	m_ListBox.ReleaseDC(pDC);

	// GetHorizontalExtent : 리스트 박스가 가로로 스크롤 할 수 있는 최대 길이를 얻어오는 함수
	if (iWidth > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iWidth);	// 가장 길 문자열 길이대로 스크롤 범위 확장

}


void CMapTool::OnDestroy()
{
	for_each(m_MapPngImg.begin(), m_MapPngImg.end(), [](auto& MyPair)
	{
		MyPair.second->Destroy();
		Safe_Delete(MyPair.second);
	});
	m_MapPngImg.clear();


	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMapTool::OnSaveData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

		const TCHAR*	pGetPath = str.GetString();
		// pGetPath = 0x0e7eda10 L"C:\\GitHub\\CrazyArcadeTool\\Data\\Test.dat"

		HANDLE	hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 0));
		CMyTerrain*	pMyTerrain = pMainView->m_pMyTerrain;

		vector<TILE*>&	vecTile = pMyTerrain->Get_VecTile();

		if (vecTile.empty())
			return;
		
		DWORD	dwByte(0);

		for (auto& iter : vecTile)
			WriteFile(hFile, iter, sizeof(TILE), &dwByte, nullptr);
			

		CloseHandle(hFile);
	}

}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	vector<CString> vecImgPath;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	vecImgPath = CTextureMgr::Get_Instance()->GetImgPath(L"../Data/ImgPath.txt", L"Tile");
	if (vecImgPath.size() == 0)
		return true;

	for (auto& iter : vecImgPath)
	{
		TCHAR		szFileName[MIN_STR] = L"";
		CString		strFileName = PathFindFileName(iter);
		CString		strFilePath = iter;


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
			m_ListBox.AddString(szFileName);
		}
	}

	UpdateData(TRUE);

	Horizontal_Scroll();

	m_bTileSelected = false;

	UpdateData(FALSE);

	return TRUE;
}
