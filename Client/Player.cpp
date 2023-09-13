#include "stdafx.h"
#include "Player.h"
#include "Device.h"
#include "TextureMgr.h"
#include "KeyMgr.h"

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
	Key_Input();

	D3DXMATRIX		matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matTrans;

	return 0;
}

void CPlayer::Late_Update(void)
{
	Change_Anim();

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
			m_iSpeed /= 3;
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

		m_vecAnim.push_back(pData);

		delete[]pObjKey;
		delete[]pStateKey;
	}

	CloseHandle(hFileAnimation);
}

void CPlayer::Key_Input()
{
	if(CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
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
		// 물풍선 생성
	}
}

void CPlayer::Change_Anim()
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