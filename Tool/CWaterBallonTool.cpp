// CWaterBallonTool.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool.h"
#include "afxdialogex.h"
#include "CWaterBallonTool.h"


// CCWaterBallonTool 대화 상자

IMPLEMENT_DYNAMIC(CCWaterBallonTool, CDialog)

CCWaterBallonTool::CCWaterBallonTool(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_WATERBALLOON, pParent)
{

}

CCWaterBallonTool::~CCWaterBallonTool()
{
}

void CCWaterBallonTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCWaterBallonTool, CDialog)
END_MESSAGE_MAP()


// CCWaterBallonTool 메시지 처리기
