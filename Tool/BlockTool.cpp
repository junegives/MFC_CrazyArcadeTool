// BlockTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "BlockTool.h"
#include "FileInfo.h"

#include "TextureMgr.h"

// CBlockTool 대화 상자

IMPLEMENT_DYNAMIC(CBlockTool, CDialog)

CBlockTool::CBlockTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CBLOCKTOOL, pParent)
{

}

CBlockTool::~CBlockTool()
{
}

void CBlockTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_FICTURE3, m_Picture);
	DDX_Control(pDX, IDC_RADIO1, m_Radio_Move[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio_Move[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio_Burst[0]);
	DDX_Control(pDX, IDC_RADIO4, m_Radio_Burst[1]);
	DDX_Control(pDX, IDC_EDIT_X, m_Collider_X);
	DDX_Control(pDX, IDC_EDIT_Y, m_Collider_Y);
}


BEGIN_MESSAGE_MAP(CBlockTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CBlockTool::OnListBox)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_X, &CBlockTool::OnChangeEditX)
	ON_EN_CHANGE(IDC_EDIT_Y, &CBlockTool::OnChangeEditY)
	ON_BN_CLICKED(IDC_BLOCK_SAVE, &CBlockTool::OnBlockSave)
	ON_BN_CLICKED(IDC_BLOCK_LOAD, &CBlockTool::OnBlockLoad)
END_MESSAGE_MAP()


// CBlockTool 메시지 처리기


void CBlockTool::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString		strFindName;

	int	iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	m_ListBox.GetText(iIndex, strFindName);

	auto	iter = m_MapPngImg.find(strFindName);

	if (iter == m_MapPngImg.end())
		return;

	m_Picture.SetBitmap(*(iter->second));

	//이미지의 가로 세로 사이즈를 가져오는 함수
	m_ImageWidth = iter->second->GetWidth();
	m_ImageHeight = iter->second->GetHeight();

	int i = 0;

	for (; i < strFindName.GetLength(); ++i)
	{
		// isdigit : 매개 변수로 전달받은 문자가 글자 형태의 문자인지 숫자 형태의 문자인지 판별하는 함수
			//       만약 숫자 형태의 글자라 판명되면 0이 아닌 값을 리턴
		if (0 != isdigit(strFindName[i]))
			break;
	}

	// Delete(index, count) : index 위치로부터 카운트 만큼 문자를 삭제하는 함수
	strFindName.Delete(0, i);

	m_iDrawID = _tstoi(strFindName);

	m_bFirst = true;

	for (size_t i = 0; i < 2; i++)
	{
		if (m_Radio_Move[i].GetCheck())
		{
			m_Option_Move = i;
			break;
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		if (m_Radio_Burst[i].GetCheck())
		{
			m_Option_Burst = i;
			break;
		}
	}

	UpdateData(FALSE);
}


void CBlockTool::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDialog::OnDropFiles(hDropInfo);

	//CDialog::OnDropFiles(hDropInfo);

	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MIN_STR] = L"";

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
			CImage* pPngImg = new CImage;

			pPngImg->Load(strRelative);

			m_MapPngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName);
		}
	}

	
	UpdateData(FALSE);
}


void CBlockTool::OnDestroy()
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


void CBlockTool::OnChangeEditX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Coll_X = GetDlgItemInt(IDC_EDIT_X);
}


void CBlockTool::OnChangeEditY()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Coll_Y = GetDlgItemInt(IDC_EDIT_Y);
}



void CBlockTool::OnBlockSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dig(FALSE,
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
		CString str = Dig.GetPathName().GetString();

		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte(0), dwStrByte(0);

		for (auto& iter : (*m_vecTile))
		{
			//dwStrByte = sizeof(TCHAR) * (Mypair.first.GetLength() + 1);
			dwStrByte = sizeof(TCHAR) * (iter->wstrStateKey.length() + 1);

			//스테이트 키
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, iter->wstrStateKey.c_str(), dwStrByte, &dwByte, nullptr);

			//선택되었는지
			WriteFile(hFile, (&iter->bPick), sizeof(bool), &dwByte, nullptr);
			//출력 이미지
			WriteFile(hFile, (&iter->byDrawID), sizeof(BYTE), &dwByte, nullptr);
			//옵션 값
			WriteFile(hFile, (&iter->byOption), sizeof(BYTE), &dwByte, nullptr);
			//터지는지 옵션
			WriteFile(hFile, (&iter->byOption_Burst), sizeof(BYTE), &dwByte, nullptr);
			//움직이는지
			WriteFile(hFile, (&iter->byOption_Move), sizeof(BYTE), &dwByte, nullptr);
			//중점, 사이즈, 이미지의 중점
			WriteFile(hFile, (&iter->vPos), sizeof(D3DXVECTOR3), &dwByte, nullptr);
			WriteFile(hFile, (&iter->vSize), sizeof(D3DXVECTOR3), &dwByte, nullptr);
			WriteFile(hFile, (&iter->vImageCenter), sizeof(D3DXVECTOR3), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}
}


void CBlockTool::OnBlockLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		//먼저 원래 들어있던 맵 데이터 제거
		for (auto& iter : (*m_vecTile))
			delete iter;

		(*m_vecTile).clear();

		CString str = Dig.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte(0), dwStrByte(0);

		TILE tTile{};

		while (true)
		{
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

			TCHAR* pName = new TCHAR[dwStrByte];
			ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);

			ReadFile(hFile, &(tTile.bPick), sizeof(bool), & dwByte, nullptr);
			ReadFile(hFile, &(tTile.byDrawID), sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &(tTile.byOption), sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &(tTile.byOption_Burst), sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &(tTile.byOption_Move), sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &(tTile.vPos), sizeof(D3DXVECTOR3), &dwByte, nullptr);
			ReadFile(hFile, &(tTile.vSize), sizeof(D3DXVECTOR3), &dwByte, nullptr);
			ReadFile(hFile, &(tTile.vImageCenter), sizeof(D3DXVECTOR3), &dwByte, nullptr);

			if (0 == dwByte)
			{
				delete[]pName;
				break;
			}

			TILE* pData = new TILE;

			pData->wstrStateKey = pName;
			delete[]pName;

			pData->bPick = tTile.bPick;
			pData->byDrawID = tTile.byDrawID;
			pData->byOption = tTile.byOption;
			pData->byOption_Burst = tTile.byOption_Burst;
			pData->byOption_Move = tTile.byOption_Move;
			pData->vPos = tTile.vPos;
			pData->vSize = tTile.vSize;
			pData->vImageCenter = tTile.vImageCenter;

			(*m_vecTile).push_back(pData);
		}


		CloseHandle(hFile);
	}
}


BOOL CBlockTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(TRUE);

	vector<CString> vecImgPath;

	vecImgPath = CTextureMgr::Get_Instance()->GetImgPath(L"../Data/ImgPath2.txt", L"Block");

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

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage* pImage = new CImage;

			pImage->Load(strFilePath);

			m_MapPngImg.insert({ strFileName, pImage });
			m_ListBox.AddString(szFileName);
		}
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
