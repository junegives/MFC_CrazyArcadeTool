#include "stdafx.h"
#include "Player.h"
#include "Device.h"
#include "TextureMgr.h"
#include "KeyMgr.h"

#include "ObjMgr.h"
#include "WaterBalloon.h"
#include "BlockTerrain.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_wstrObjKey = L"Bazzi";
	m_wstrStateKey = L"Bazzi_Stand";
	m_iDir = 2;

	m_tFrame = { 0.f, 0.f };

	return S_OK;
}

int CPlayer::Update(void)
{
	if (CObjMgr::Get_Instance()->Get_Block() != nullptr)
	{
		CObj* block = CObjMgr::Get_Instance()->Get_Block();
		m_vecTile = (dynamic_cast<CBlockTerrain*>(block)->Get_BlockTile());
	}

	Key_Input();

	m_wstrPreStateKey = m_wstrStateKey;

	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + 20,
		m_tInfo.vPos.y + 40,
		0.f);

	m_tInfo.matWorld = matTrans;

	return 0;
}

void CPlayer::Late_Update(void)
{
	Change_State();

	if (m_wstrStateKey != m_wstrPreStateKey || m_iDir != m_iPreDir)
		Change_Anim();

	m_wstrPreStateKey = m_wstrStateKey;
	m_iPreDir = m_iDir;

	if (m_eState != ePlayerState::STAND)
		__super::Move_Frame();
}

void CPlayer::Render(void)
{
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	if (pTexInfo)
	{
		float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CPlayer::Release(void)
{
}

void CPlayer::Load_Player(wstring _szID, wstring _szCharacter)
{
	m_strNickName = _szID;

	HANDLE		hFilePlayer = CreateFile(L"../Data/Player.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFilePlayer)
		return;

	DWORD	dwByte(0), dwStrByte(0);

	CHARACTERDATA tData{};

	while (true)
	{
		ReadFile(hFilePlayer, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

		TCHAR* pName = new TCHAR[dwStrByte];
		ReadFile(hFilePlayer, pName, dwStrByte, &dwByte, nullptr);

		if (pName == m_strNickName)
		{

			ReadFile(hFilePlayer, &(tData.iSpeed), sizeof(int), &dwByte, nullptr);
			ReadFile(hFilePlayer, &(tData.iWaterLength), sizeof(int), &dwByte, nullptr);
			ReadFile(hFilePlayer, &(tData.iWaterCount), sizeof(int), &dwByte, nullptr);
			ReadFile(hFilePlayer, &(tData.iSpeed), sizeof(int), &dwByte, nullptr);

			if (0 == dwByte)
			{
				delete[]pName;
				break;
			}

			delete[]pName;

			m_iSpeed = tData.iSpeed;
			m_iSpeed /= 4;
			m_iWaterLength = tData.iWaterLength;
			m_iWaterCount = tData.iWaterCount;

			break;
		}
	}

	CloseHandle(hFilePlayer);

	m_wstrObjKey = _szCharacter;

	HANDLE		hFileAnimation = CreateFile(L"../Data/Animation.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFileAnimation)
		return;

	dwByte = 0;
	dwStrByte = 0;

	ANIMINFO tDataAnim{};

	while (true)
	{
		ReadFile(hFileAnimation, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

		TCHAR* pObjKey = new TCHAR[dwStrByte];
		ReadFile(hFileAnimation, pObjKey, dwStrByte, &dwByte, nullptr);

		ReadFile(hFileAnimation, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

		TCHAR* pStateKey = new TCHAR[dwStrByte];
		ReadFile(hFileAnimation, pStateKey, dwStrByte, &dwByte, nullptr);

		ReadFile(hFileAnimation, &(tDataAnim.iFrameSpeed), sizeof(int), &dwByte, nullptr);
		ReadFile(hFileAnimation, &(tDataAnim.isLoop), sizeof(BOOL), &dwByte, nullptr);
		ReadFile(hFileAnimation, &(tDataAnim.vPos), sizeof(D3DXVECTOR3), &dwByte, nullptr);
		ReadFile(hFileAnimation, &(tDataAnim.iFrameCnt), sizeof(int), &dwByte, nullptr);


		if (0 == dwByte)
		{
			delete[]pObjKey;
			delete[]pStateKey;
			break;
		}

		if (pObjKey != _szCharacter)
		{
			delete[]pObjKey;
			delete[]pStateKey;
			continue;
		}

		ANIMINFO* pData = new ANIMINFO;
		pData->wstrObjectKey = pObjKey;
		pData->wstrStateKey = pStateKey;
		pData->iFrameSpeed = tDataAnim.iFrameSpeed;
		pData->isLoop = tDataAnim.isLoop;
		pData->vPos = tDataAnim.vPos;
		pData->iFrameCnt = tDataAnim.iFrameCnt;

		m_vecAnim.push_back(pData);

		delete[]pObjKey;
		delete[]pStateKey;
	}

	CloseHandle(hFileAnimation);
}

void CPlayer::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.vPos.y -= m_iSpeed;
		m_iDir = 0;
		m_eState = ePlayerState::WALK;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.vPos.x += m_iSpeed;
		m_iDir = 1;
		m_eState = ePlayerState::WALK;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.vPos.y += m_iSpeed;
		m_iDir = 2;
		m_eState = ePlayerState::WALK;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.vPos.x -= m_iSpeed;
		m_iDir = 3;
		m_eState = ePlayerState::WALK;
	}

	else
	{
		m_eState = ePlayerState::STAND;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		int  iIndex = Get_PosTileIndex(m_tInfo.vPos);

		if (-1 == iIndex)
			return;

		D3DXVECTOR3 WaterBalloonvPos;

		WaterBalloonvPos = (m_vecTile)[iIndex]->vPos;
		// 물풍선 생성
		CObj* pWater = new CWaterBalloon;
		pWater->Initialize();
		pWater->Set_Pos(WaterBalloonvPos);

		CObjMgr::Get_Instance()->Add_Object(CObjMgr::WATERBALLOON, pWater);
	}
}

void CPlayer::Change_State()
{
	switch (m_eState)
	{
	case CPlayer::ePlayerState::STAND:
		m_wstrStateKey = m_wstrObjKey + L"_Stand";
		break;
	case CPlayer::ePlayerState::WALK:
		switch (m_iDir)
		{
		case 0:
			m_wstrStateKey = m_wstrObjKey + L"_WalkUp";
			break;
		case 1:
			m_wstrStateKey = m_wstrObjKey + L"_WalkRight";
			break;
		case 2:
			m_wstrStateKey = m_wstrObjKey + L"_WalkDown";
			break;
		case 3:
			m_wstrStateKey = m_wstrObjKey + L"_WalkLeft";
			break;
		default:
			break;
		}
		break;
	case CPlayer::ePlayerState::BUBBLE:
		m_wstrStateKey = m_wstrObjKey + L"_Bubble";
		break;
	case CPlayer::ePlayerState::REVIVAL:
		m_wstrStateKey = m_wstrObjKey + L"_Revival";
		break;
	case CPlayer::ePlayerState::DIE:
		m_wstrStateKey = m_wstrObjKey + L"_Die";
		break;
	case CPlayer::ePlayerState::JUMP:
		m_wstrStateKey = m_wstrObjKey + L"_Jump";
		break;
	default:
		m_wstrStateKey = m_wstrObjKey + L"_Stand";
		break;
	}
}

void CPlayer::Change_Anim()
{
	// 애니메이션 데이터 불러와서 정보 다 가져오기
	for (auto& iter : m_vecAnim)
	{
		if (m_wstrStateKey == iter->wstrStateKey)
		{
			m_tFrame.fSpeed = (float)iter->iFrameSpeed;
			m_tFrame.isLoop = iter->isLoop;

			if (m_eState == ePlayerState::STAND)
			{
				m_tFrame.fFrame = (float)m_iDir;
				m_tFrame.fMax = (float)m_iDir;
			}
			else
			{
				m_tFrame.fFrame = 0.f;
				m_tFrame.fMax = (float)iter->iFrameCnt;
			}
		}
	}
}

int CPlayer::Get_PosTileIndex(const D3DXVECTOR3& vPos)
{
	for (size_t index = 0; index < (m_vecTile).size(); ++index)
	{
		if (ReDefine_vPos(vPos, index))
		{
			return index;
		}
	}

	return -1;
}


bool CPlayer::ReDefine_vPos(const D3DXVECTOR3& vPos, const int& iIndex)
{
	bool bCheck[4]{ false };

	vector<TILE*> vecTile = (m_vecTile);

	if ((vecTile[iIndex]->vPos.x - TILECX / 2.f) <= vPos.x)
	{
		bCheck[0] = true;
	}
	if ((vecTile[iIndex]->vPos.x + TILECX / 2.f) > vPos.x)
	{
		bCheck[1] = true;
	}
	if ((vecTile[iIndex]->vPos.y - TILECY / 2.f) <= vPos.y)
	{
		bCheck[2] = true;
	}
	if ((vecTile[iIndex]->vPos.y + TILECY / 2.f) > vPos.y)
	{
		bCheck[3] = true;
	}

	return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];

}