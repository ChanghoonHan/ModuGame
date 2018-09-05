#pragma once
#include "../HCHEngine/Scene.h"
#include "../HCHEngine/BitMap.h"
#include "../HCHEngine/OperatorManager.h"
#include "../HCHEngine/Button.h"
#include "Paper.h"
#include "Bullet.h"
#include "Star.h"
#include "Airplane.h"

#define MAXTIME 45
#define MAXFEVER 3000
#define MINUSFEVER 1000
#define CLOUDSPEED 125

class AirplaneGameScene :
	public Scene
{
	BitMap* m_pBackGround;
	BitMap* m_pCloud;
	BitMap* m_pBackFrame;
	BitMap* m_pTimerBar;
	BitMap* m_pReadyEndBitMap;
	BitMap* m_pFeverBar[3];
	Button m_button;

	int m_bulletIdx;
	int m_starIdx;
	float m_fBulletInstatiateTime;
	float m_fStarInstatiateTime;
	Bullet m_bullet[100];
	Star m_star[100];
	Airplane m_airplane;

	GAMESTATE m_gameState;
	string m_strFever;

	vector<void*> saveCollObject;

	bool m_secondCloud;
	float m_fCloudDrawPos;
	float m_fCloudLendPos;
	float m_fGameReadyTimer;
	float m_fElapsedTimeForTimer;
	float m_fElapsedTimeForScore;
	float m_fTimer;
	int m_feverLevel;
	int m_feverCount;
	float m_fFeverBarTime;

	int m_score;
	int m_addScoreSize;
	int m_fever;
	
	int CallBack();

public:
	virtual void Init();
	virtual void InputOperator(float fElapsedTime);
	virtual void Update(float fElapsedTime);
	virtual bool Draw();
	virtual void Release();

	AirplaneGameScene();
	~AirplaneGameScene();
};

