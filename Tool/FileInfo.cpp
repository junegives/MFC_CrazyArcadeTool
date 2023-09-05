#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertRelativePath(CString strFullPath)
{
	TCHAR		szRelativePath[MAX_PATH] = L"";		// ��� ��θ� ������ ���ڿ�
	TCHAR		szCurDirPath[MAX_PATH] = L"";		// ���� ���� ��θ� ������ ���ڿ�

	GetCurrentDirectory(MAX_PATH, szCurDirPath);	// ���� ������Ʈ�� �ִ� ���丮 ��θ� ����

	// PathRelativePathTo : szCurDirPath���� strFullPath�� ���� ����θ� ���ؼ� szRelativePath�� �����ϴ� �Լ�
	// ��, ���� ����̺� �������� ���� ����

	PathRelativePathTo(szRelativePath, 
						szCurDirPath, 
						FILE_ATTRIBUTE_DIRECTORY, 
						strFullPath.GetString(),
						FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}
