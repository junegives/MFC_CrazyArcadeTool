// BlockTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "BlockTool.h"
#include "FileInfo.h"


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
}


BEGIN_MESSAGE_MAP(CBlockTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CBlockTool::OnListBox)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
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



	CDialog::OnDropFiles(hDropInfo);

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
