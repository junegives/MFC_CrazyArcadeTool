// PathFinderTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "PathFinderTool.h"


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
}


BEGIN_MESSAGE_MAP(CPathFinderTool, CDialog)
	ON_BN_CLICKED(IDC_BTNPATHSAVE, &CPathFinderTool::OnSaveData)
	ON_BN_CLICKED(IDC_BTNPATHLOAD, &CPathFinderTool::OnLoadData)
END_MESSAGE_MAP()


// CPathFinderTool 메시지 처리기


void CPathFinderTool::OnSaveData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPathFinderTool::OnLoadData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
