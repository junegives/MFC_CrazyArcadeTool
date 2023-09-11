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

void CFileInfo::DirInfoExtraction(const wstring& wstrPath, list<IMGPATH*>& rPathList)
{

	wstring		wstrFilePath = wstrPath + L"\\*.*";

	// CFileFind  : mfc에서 제공하는 파일 및 경로 제어 클래스
	CFileFind		Find;

	//FindFile : 매개 변수로 전달한 경로에서 파일의 유무를 판단하여 bool타입으로 반환
				// 파일이 없으면 FALSE, 있으면 TRUE를 리턴

	BOOL bContinue = Find.FindFile(wstrFilePath.c_str());

	while (bContinue)
	{
		// FindNextFile : 동일 경로 안에서 다음 파일을 탐색, 더이상 찾을게 없을 경우 또는 마지막 대상을 찾았을 경우 0을 반환
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		else if (Find.IsDirectory())
		{
			// GetFilePath : 현재 찾은 경로를 얻어오는 함수

			DirInfoExtraction(wstring(Find.GetFilePath()), rPathList);
		}

		else
		{
			if (Find.IsSystem())
				continue;

			IMGPATH* pImgPath = new IMGPATH;
			TCHAR			szPathBuf[MAX_STR] = L"";

			lstrcpy(szPathBuf, Find.GetFilePath().GetString());

			//szPathBuf = 0x00dfddbc L"D:\\유준환\\140기\\4개월차\\Frame140\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack0.png"

			// 현재 경로에서 맨 뒷 부분을 잘라냄
			PathRemoveFileSpec(szPathBuf);
			//szPathBuf = 0x00dfddbc L"D:\\유준환\\140기\\4개월차\\Frame140\\Texture\\Stage\\Effect\\BossMultiAttack"
			pImgPath->iCount = DirFileCount(szPathBuf);

			// GetFileTitle : 파일명만 추출하는 함수
			wstring	wstrTextureName = Find.GetFileTitle().GetString();
			//wstrTextureName = L"BossMultiAttack0"

			// substr(시작, 끝) : 시작에서 끝에 해당하는 문자열을 잘라냄
			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d.png";
			//wstrTextureName = L"BossMultiAttack%d.png"

			// PathCombine(dst, src1, src2) : src1과 src2를 이어붙여 완성된 경로를 dst에 저장
			//	src1과 src2사이에 \\를 자동으로 삽입하여 저장

			PathCombine(szPathBuf, szPathBuf, wstrTextureName.c_str());
			//szPathBuf = 0x00dfddbc L"D:\\유준환\\140기\\4개월차\\Frame140\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack%d.png"

			pImgPath->wstrPath = CFileInfo::ConvertRelativePath(szPathBuf);
			// pImgPath->wstrPath = L"..\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack%d.png"

			PathRemoveFileSpec(szPathBuf);
			// pImgPath->wstrPath = L"..\\Texture\\Stage\\Effect\\BossMultiAttack\\

			// PathFindFileName : 파일명을 찾거나 마지막 폴더명을 찾아냄
			pImgPath->wstrStateKey = PathFindFileName(szPathBuf);

			PathRemoveFileSpec(szPathBuf);
			// pImgPath->wstrPath = L"..\\Texture\\Stage\\Effect

			pImgPath->wstrObjKey = PathFindFileName(szPathBuf);

			rPathList.push_back(pImgPath);

			bContinue = FALSE;
		}

	}





}

int CFileInfo::DirFileCount(const wstring& wstrPath)
{
	wstring		wstrFilePath = wstrPath + L"\\*.*";

	CFileFind		Find;
	int		iFileCnt(0);

	BOOL bContinue = Find.FindFile(wstrFilePath.c_str());

	while (bContinue)
	{
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		if (Find.IsSystem())
			continue;

		++iFileCnt;
	}

	return iFileCnt;
}
