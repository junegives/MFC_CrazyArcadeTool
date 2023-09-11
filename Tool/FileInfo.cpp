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
	TCHAR		szRelativePath[MAX_PATH] = L"";		// 상대 경로를 저장할 문자열
	TCHAR		szCurDirPath[MAX_PATH] = L"";		// 현재 절대 경로를 저장할 문자열

	GetCurrentDirectory(MAX_PATH, szCurDirPath);	// 현재 프로젝트가 있는 디렉토리 경로를 얻어옴

	// PathRelativePathTo : szCurDirPath에서 strFullPath로 가는 상대경로를 구해서 szRelativePath에 저장하는 함수
	// 단, 같은 드라이브 내에서만 변경 가능

	PathRelativePathTo(szRelativePath, 
						szCurDirPath, 
						FILE_ATTRIBUTE_DIRECTORY, 
						strFullPath.GetString(),
						FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}
