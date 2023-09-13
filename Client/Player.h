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
	void Change_Anim();

private:
	wstring m_strNickName;
	int		m_iWaterLength;
	int		m_iWaterCount;
	int		m_iSpeed;

	int		m_iDir = 2;
	ePlayerState m_eState = ePlayerState::STAND;

	vector<ANIMINFO*> m_vecAnim;
};

