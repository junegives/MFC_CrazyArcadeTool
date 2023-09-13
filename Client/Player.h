#pragma once
#include "Obj.h"
class CPlayer : public CObj
{
	enum class ePlayerState
	{
		STAND,
		WALK,
		BUBBLE,
		REVIVAL,
		DIE,
		JUMP
	};


public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void Load_Player(wstring _szID, wstring _szCharacter);
	void Key_Input();
	void Change_State();
	void Change_Anim();

	void Change_Character(wstring _szCharacter);
	void Change_Balloon(wstring _szBalloon);

	bool ReDefine_vPos(const D3DXVECTOR3& vPos, const int& iIndex);
	//get_tileIndex�� ���� ����
	int Get_PosTileIndex(const D3DXVECTOR3& vPos);

	void Set_BlockTile(vector<TILE*> _vecTile) { m_vecTile = _vecTile; }

private:
	wstring m_strNickName;
	int		m_iWaterLength;
	int		m_iWaterCount;
	int		m_iSpeed;

	int		m_iDir = 2;
	int		m_iPreDir = 2;
	ePlayerState m_eState = ePlayerState::STAND;
	wstring	m_wstrPreStateKey = L"";
	wstring m_wstrWaterBalloon = L"";

	vector<ANIMINFO*> m_vecAnim;
	vector<wstring> m_vecImgPath;

	vector<TILE*> m_vecTile;

	int m_iLength = 3;
	int m_iCount = 3;
};

