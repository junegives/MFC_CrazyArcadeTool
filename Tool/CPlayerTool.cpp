// CPlayerTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CPlayerTool.h"

#include "Functor.h"


// CCPlayerTool 대화 상자

IMPLEMENT_DYNAMIC(CCPlayerTool, CDialog)

CCPlayerTool::CCPlayerTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PLAYER, pParent)
	, m_EditwaterCount(0), m_EditwaterLength(0)
	, m_Nickname(_T(""))
	, m_Speed(0)
{

}

CCPlayerTool::~CCPlayerTool()
{
}

void CCPlayerTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT2, m_Nickname);
	DDX_Control(pDX, IDC_SLIDER1, m_CtrlwaterLength);
	DDX_Text(pDX, IDC_EDIT3, m_EditwaterLength);
	DDX_Control(pDX, IDC_SLIDER2, m_CtrlwaterCount);
	DDX_Text(pDX, IDC_EDIT4, m_EditwaterCount);

	DDX_Control(pDX, IDC_LIST2, m_ListBox);
	DDX_Text(pDX, IDC_EDIT2, m_Nickname);
	DDX_Control(pDX, IDC_SPIN_SPEED, m_CtrlSpeed);
	DDX_Text(pDX, IDC_EDIT5, m_Speed);
}


BEGIN_MESSAGE_MAP(CCPlayerTool, CDialog)
	ON_WM_HSCROLL()
	ON_EN_UPDATE(IDC_EDIT3, &CCPlayerTool::OnUpdateEditWaterLength)
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CCPlayerTool::OnCustomdrawLengthSlider)
	ON_EN_UPDATE(IDC_EDIT4, &CCPlayerTool::OnUpdateEditWaterCount)
	ON_LBN_SELCHANGE(IDC_LIST2, &CCPlayerTool::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON2, &CCPlayerTool::OnAddPlayer)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CCPlayerTool::OnSaveData)
	ON_BN_CLICKED(IDC_BUTTON4, &CCPlayerTool::OnLoadData)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SPEED, &CCPlayerTool::OnDeltaposSpinSpeed)
END_MESSAGE_MAP()


// CCPlayerTool 메시지 처리기


BOOL CCPlayerTool::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			m_CtrlwaterCount.SetPos(m_EditwaterCount);

			return TRUE;
		}
	}


	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CCPlayerTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	UpdateData(TRUE);
	//슬라이더의 범위 지정
	m_CtrlwaterLength.SetRange(0, 10);
	//슬라이더의 최솟값 지정
	m_CtrlwaterLength.SetRangeMin(0);
	//슬라이더의 최댓값 지정
	m_CtrlwaterLength.SetRangeMax(10);

	//슬라이더 위치 지정
	m_CtrlwaterLength.SetPos(5);

	//눈금 설정
	m_CtrlwaterLength.SetTicFreq(1);
	//키보드 값으로 움직일 크기 지정
	m_CtrlwaterLength.SetLineSize(1);

	int npos = m_CtrlwaterLength.GetPos();
	m_EditwaterLength = npos;

	//슬라이더의 범위 지정
	m_CtrlwaterCount.SetRange(0, 10);
	//슬라이더의 최솟값 지정
	m_CtrlwaterCount.SetRangeMin(0);
	//슬라이더의 최댓값 지정
	m_CtrlwaterCount.SetRangeMax(10);

	//슬라이더 위치 지정
	m_CtrlwaterCount.SetPos(5);

	//눈금 설정
	m_CtrlwaterCount.SetTicFreq(1);
	//키보드 값으로 움직일 크기 지정
	m_CtrlwaterCount.SetLineSize(1);

	npos = m_CtrlwaterCount.GetPos();
	m_EditwaterCount = npos;

	//윗 화살표를 눌렀을 떄 올라가도록, 그리고 최대 범위 설정
	m_CtrlSpeed.SetRange(0, 10);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCPlayerTool::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(TRUE);

	if (pScrollBar)
	{
		if (pScrollBar == (CScrollBar*)&m_CtrlwaterLength)
		{
			int nPos = m_CtrlwaterLength.GetPos();

			if (nPos >= 0 && nPos <= 10)
			{
				m_EditwaterLength = nPos;
			}

			//m_EditwaterLength.
		}
		if (pScrollBar == (CScrollBar*)&m_CtrlwaterCount)
		{
			int nPos = m_CtrlwaterCount.GetPos();

			m_EditwaterCount = nPos;
		}
	}

	UpdateData(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CCPlayerTool::OnUpdateEditWaterLength()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_EditwaterLength >= 0 && m_EditwaterLength <= 10)
	{
		UpdateData(TRUE);

		m_CtrlwaterLength.SetPos(m_EditwaterLength);

		UpdateData(FALSE);
	}


}


void CCPlayerTool::OnCustomdrawLengthSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//int nPos = m_CtrlwaterLength.GetPos();
	//m_EditwaterLength = nPos;

	*pResult = 0;
}


void CCPlayerTool::OnUpdateEditWaterCount()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	m_CtrlwaterCount.SetPos(m_EditwaterCount);

	UpdateData(FALSE);
}


void CCPlayerTool::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString szFindname;

	int iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	m_ListBox.GetText(iIndex, szFindname);

	auto iter = m_mapCharacterData.find(szFindname);

	if (iter == m_mapCharacterData.end())
		return;

	m_Nickname = iter->second->strName;
	m_EditwaterLength = iter->second->iWaterLength;
	m_EditwaterCount = iter->second->iWaterCount;
	m_Speed = iter->second->iSpeed;

	m_CtrlwaterLength.SetPos(m_EditwaterLength);
	m_CtrlwaterCount.SetPos(m_EditwaterCount);

	UpdateData(FALSE);
}


void CCPlayerTool::OnAddPlayer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_Nickname != L"" && m_Speed != 0)
	{
		CHARACTERDATA* pData = new CHARACTERDATA;

		pData->strName = m_Nickname;
		//임시
		pData->iSpeed = 0;

		pData->iWaterLength = m_EditwaterLength;

		pData->iWaterCount = m_EditwaterCount;

		pData->iSpeed = m_Speed;

		m_ListBox.AddString(pData->strName);

		m_mapCharacterData.insert({ pData->strName, pData });
	}
	else
	{
		MessageBox(_T("Unentered information that is not been entered."), _T("NO"), MB_OK);
	}


	UpdateData(FALSE);
}


void CCPlayerTool::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for_each(m_mapCharacterData.begin(), m_mapCharacterData.end(), CDeleteMap());
	m_mapCharacterData.clear();
}


//저장하기 버튼 눌렀을 시
void CCPlayerTool::OnSaveData()
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

		for (auto& Mypair : m_mapCharacterData)
		{
			dwStrByte = sizeof(TCHAR) * (Mypair.first.GetLength() + 1);

			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, Mypair.first.GetString(), dwStrByte, &dwByte, nullptr);

			WriteFile(hFile, &(Mypair.second->iSpeed), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(Mypair.second->iWaterLength), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(Mypair.second->iWaterCount), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(Mypair.second->iSpeed), sizeof(int), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}
}


//불러오기 버튼 눌렀을 시;
void CCPlayerTool::OnLoadData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		//먼저 원래 들어있던 맵 데이터 제거
		for (auto& Mypair : m_mapCharacterData)
			delete Mypair.second;

		m_mapCharacterData.clear();

		//리스트 박스 목록 초기화
		m_ListBox.ResetContent();

		m_Nickname.SetString(L"");
		m_EditwaterLength = 5;
		m_EditwaterCount = 5;
		m_CtrlwaterLength.SetPos(m_EditwaterLength);
		m_CtrlwaterCount.SetPos(m_EditwaterCount);

		m_Speed = 0;

		CString str = Dig.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte(0), dwStrByte(0);

		CHARACTERDATA tData{};

		while (true)
		{
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

			TCHAR* pName = new TCHAR[dwStrByte];
			ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);

			ReadFile(hFile, &(tData.iSpeed), sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(tData.iWaterLength), sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(tData.iWaterCount), sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(tData.iSpeed), sizeof(int), &dwByte, nullptr);

			if (0 == dwByte)
			{
				delete[]pName;
				break;
			}

			CHARACTERDATA* pData = new CHARACTERDATA;

			pData->strName = pName;
			delete[]pName;

			pData->iSpeed = tData.iSpeed;
			pData->iWaterLength = tData.iWaterLength;
			pData->iWaterCount = tData.iWaterCount;

			m_mapCharacterData.insert({ pData->strName, pData });

			m_ListBox.AddString(pData->strName);

		}


		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}


void CCPlayerTool::OnDeltaposSpinSpeed(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMUpDown->iDelta < 0)
	{
		if (m_Speed > 10)
			return;

		m_Speed -= 1;
	}
	else
	{
		if (m_Speed < 0)
			return;

		m_Speed += 1;
	}


	*pResult = 0;
}
