// PathFinderTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "PathFinderTool.h"

#include "FileInfo.h"


// CPathFinderTool 대화 상자

IMPLEMENT_DYNAMIC(CPathFinderTool, CDialog)

CPathFinderTool::CPathFinderTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PATHFINDER, pParent)
{

}

CPathFinderTool::~CPathFinderTool()
{
}

void CPathFinderTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ListPath, m_ListBox);
}


BEGIN_MESSAGE_MAP(CPathFinderTool, CDialog)
	ON_BN_CLICKED(IDC_BTNPATHSAVE, &CPathFinderTool::OnSaveData)
	ON_BN_CLICKED(IDC_BTNPATHLOAD, &CPathFinderTool::OnLoadData)
	ON_LBN_SELCHANGE(IDC_ListPath, &CPathFinderTool::OnListBox)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPathFinderTool 메시지 처리기


void CPathFinderTool::OnSaveData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	wofstream		fout;

	fout.open(L"../Data/ImgPath.txt", ios::out);

	// 개방 성공
	if (!fout.fail())
	{
		for (auto& iter : m_PathList)
		{
			fout << iter->wstrObjKey << L"|" << iter->wstrStateKey << L"|" << iter->iCount << L"|" << iter->wstrPath << endl;
		}

		fout.close();
	}

	WinExec("notepad.exe ../Data/ImgPath.txt", SW_SHOW);
}


void CPathFinderTool::OnLoadData()
{
	UpdateData(TRUE);

	wifstream		fin;

	fin.open(L"../Data/ImgPath.txt", ios::in);

	if (!fin.fail())
	{
		TCHAR		szObjKey[MAX_STR] = L"";
		TCHAR		szStateKey[MAX_STR] = L"";
		TCHAR		szCount[MAX_STR] = L"";
		TCHAR		szPath[MAX_PATH] = L"";

		wstring		wstrCombined = L"";

		m_ListBox.ResetContent();

		while (true)
		{
			fin.getline(szObjKey, MAX_STR, '|');
			fin.getline(szStateKey, MAX_STR, '|');
			fin.getline(szCount, MAX_STR, '|');
			fin.getline(szPath, MAX_PATH);

			if (fin.eof())
				break;

			wstrCombined = wstring(szObjKey) + L"|" + szStateKey + L"|" + szCount + L"|" + szPath;

			m_ListBox.AddString(wstrCombined.c_str());
		}

		fin.close();
	}

	UpdateData(FALSE);

	WinExec("notepad.exe ../Data/ImgPath.txt", SW_SHOW);
}


void CPathFinderTool::OnListBox()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}


void CPathFinderTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialog::OnDropFiles(hDropInfo);

	UpdateData(TRUE);

	TCHAR		szFilePath[MAX_PATH] = L"";

	int	iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CFileInfo::DirInfoExtraction(szFilePath, m_PathList);
	}

	m_ListBox.ResetContent();

	wstring	wstrCombined = L"";
	TCHAR	szBuf[MIN_STR] = L"";

	for (auto& iter : m_PathList)
	{
		// _itow_s : 정수를 유니코드 문자열로 변환, 10진수 형태로 변환한다는 의미
		_itow_s(iter->iCount, szBuf, 10);

		wstrCombined = iter->wstrObjKey + L"|" + iter->wstrStateKey + L"|" + szBuf + L"|" + iter->wstrPath;

		m_ListBox.AddString(wstrCombined.c_str());
	}


	UpdateData(FALSE);
}


void CPathFinderTool::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for_each(m_PathList.begin(), m_PathList.end(), CDeleteObj());
	m_PathList.clear();
}
