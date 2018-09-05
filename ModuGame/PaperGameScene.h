#pragma once
#include "../HCHEngine/Scene.h"
#include "../HCHEngine/BitMap.h"
#include "../HCHEngine/OperatorManager.h"
#include "../HCHEngine/Button.h"
#include "Paper.h"

#define MAXTIME 45
#define MAXFEVER 3000
#define MINUSFEVER 1000

class PaperGameScene :
	public Scene
{
	BitMap* m_pBackGround;
	BitMap* m_pTimerBar;
	BitMap* m_pReadyEndBitMap;
	BitMap* m_pFeverBar[3];
	Button m_button;
	Paper m_paper[3];
	
	GAMESTATE m_gameState;
	string m_strFever;
	const Point m_paperPos[2] = { {150, 325}, {160, 335} };
	float m_fGameReadyTimer;
	float m_fElapsedTimeForTimer;
	float m_fTimer;
	int m_feverLevel;
	float m_fFeverBarTime;
	float m_fSuperFeverBitMapTime;
	bool m_bSuperFeverBitMapChange;
	int m_topPaperIndex;
	int m_score;
	int m_fever;
	bool m_bSuperFever;

	int CallBack();

public:
	virtual void Init();
	virtual void InputOperator(float fElapsedTime);
	virtual void Update(float fElapsedTime);
	virtual bool Draw();
	virtual void Release();

	PaperGameScene();
	~PaperGameScene();
};

