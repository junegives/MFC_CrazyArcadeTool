// MapTool.cpp : ���� �����Դϴ�.

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "MainFrm.h"
#include "ToolView.h"


// CMapTool ��ȭ �����Դϴ�.

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
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.


void CMapTool::OnListBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	int i = 0;

	for (; i < strFindName.GetLength(); ++i)
	{
		// isdigit : �Ű� ������ ���޹��� ���ڰ� ���� ������ �������� ���� ������ �������� �Ǻ��ϴ� �Լ�
			//       ���� ���� ������ ���ڶ� �Ǹ�Ǹ� 0�� �ƴ� ���� ����
		if (0 != isdigit(strFindName[i]))
			break;
	}

	// Delete(index, count) : index ��ġ�κ��� ī��Ʈ ��ŭ ���ڸ� �����ϴ� �Լ�
	strFindName.Delete(0, i);

	// _tstoi : ���ڸ� ���������� ��ȯ�ϴ� �Լ�
	m_iDrawID = _tstoi(strFindName);


	UpdateData(FALSE);
}


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UpdateData(TRUE);
	
	CDialog::OnDropFiles(hDropInfo);

	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MIN_STR] = L"";

	// DragQueryFile : ��ӵ� ������ ������ ������ �Լ�

	// �� ��° �Ű� ���� : 0xffffffff(-1)�� �����ϸ� ��ӵ� ������ ������ ��ȯ 

	int	iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);
		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());

		// ������ Ȯ���� ���� �����ϴ� �Լ�
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage*		pPngImg = new CImage;

			pPngImg->Load(strRelative);
			

			for (int i = 0; i < pPngImg->GetWidth() / TILECX; ++i)
			{
				m_MapPngImg.insert({ strFileName, pPngImg });
				m_ListBox.AddString(szFileName);
			}
		}		
	}	

	Horizontal_Scroll();

	UpdateData(FALSE);
}

void CMapTool::Horizontal_Scroll()
{
	CString		strFineName;

	CSize		size;
	int			iWidth = 0;

	CDC*		pDC = m_ListBox.GetDC();

	// GetCount : ���� ����Ʈ �ڽ��� �ִ� ����� ������ ��ȯ
	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strFineName);

		// GetTextExtent : ���� ���ڿ��� ���̸� �ȼ������� ��ȯ
		size = pDC->GetTextExtent(strFineName);

		if (size.cx > iWidth)
			iWidth = size.cx;
	}

	m_ListBox.ReleaseDC(pDC);

	// GetHorizontalExtent : ����Ʈ �ڽ��� ���η� ��ũ�� �� �� �ִ� �ִ� ���̸� ������ �Լ�
	if (iWidth > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iWidth);	// ���� �� ���ڿ� ���̴�� ��ũ�� ���� Ȯ��

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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CMapTool::OnSaveData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog		Dlg(FALSE,	// ��� ����(true ����, false �ٸ� �̸����� ����)
		L"dat",	// �⺻ Ȯ���ڸ�
		L"*.dat", // ��ȭ ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	//  OFN_HIDEREADONLY : �б� ���� üũ�ڽ� ����, OFN_OVERWRITEPROMPT : �ߺ����� ���� �� ��� �޼��� ���
		L"Data File(*.dat) | *.dat ||", // ��ȭ ���ڿ� ǥ�õ� ���� ����, �޺� �ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ�
		this);	// �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	// szPath = 0x003fe74c L"D:\\����ȯ\\140��\\4������\\Frame140\\Tool"

	// PathRemoveFileSpec : ��ü ��� �� �� ������ ��θ� �߶�
	PathRemoveFileSpec(szPath);
	// (szPath) = 0x003fe74c L"D:\\����ȯ\\140��\\4������\\Frame140"

	lstrcat(szPath, L"\\Data");
	// szPath = 0x003fe74c L"D:\\����ȯ\\140��\\4������\\Frame140\\Data"

	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : ��ȭ ���ڸ� ����
	if (IDOK == Dlg.DoModal())
	{
		CString		str = Dlg.GetPathName().GetString();

		const TCHAR*	pGetPath = str.GetString();

		HANDLE	hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		CMainFrame*	pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*	pMainView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
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
