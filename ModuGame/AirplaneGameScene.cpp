#include "AirplaneGameScene.h"
#include "../HCHEngine/DrawManager.h"
#include "../HCHEngine/CollisionManager.h"

int AirplaneGameScene::CallBack()
{
	m_airplane.Kill();
	GameManager::GetInstance()->LoadScene(1);
	return 0;
}

void AirplaneGameScene::Init()
{
	for (size_t i = 0; i < 100; i++)
	{
		m_bullet[i].Destroy();
		m_star[i].Destroy();
	}
	m_airplane.Instantiate();

	m_gameState = READY;
	m_fGameReadyTimer = 0.5;
	m_strFever = "";
	m_score = 0;
	m_addScoreSize = 100;
	m_fever = 0;
	m_feverLevel = 0;
	m_fFeverBarTime = 0;

	m_bulletIdx = 0;
	m_fBulletInstatiateTime = 0;

	m_starIdx = 0;
	m_fStarInstatiateTime = 0;
	m_fElapsedTimeForScore = 0;
	m_fCloudLendPos = 1400;
	m_fCloudDrawPos = 0;
	m_feverCount = 0;
	m_secondCloud = false;

	m_fElapsedTimeForTimer = 0;
	m_fTimer = MAXTIME;

	m_button.Init("backButton1.bmp", "backButton2.bmp", 355, 5, 40, 40, bind(&AirplaneGameScene::CallBack, this));
	m_pBackGround = DrawManager::GetInstnace()->GetBitMap("planegameBack.bmp");
	m_pCloud = DrawManager::GetInstnace()->GetBitMap("planeGameCloud.bmp");
	m_pBackFrame = DrawManager::GetInstnace()->GetBitMap("GameBackFrame.bmp");
	m_pTimerBar = DrawManager::GetInstnace()->GetBitMap("timerBar.bmp");
	m_pReadyEndBitMap = DrawManager::GetInstnace()->GetBitMap("ready.bmp");
	m_pFeverBar[0] = DrawManager::GetInstnace()->GetBitMap("feverBar1.bmp");
	m_pFeverBar[1] = DrawManager::GetInstnace()->GetBitMap("feverBar2.bmp");
	m_pFeverBar[2] = DrawManager::GetInstnace()->GetBitMap("feverBar3.bmp");
	CollisionManager::GetInstance()->ResetCircleCollier();

	OperatorManager::GetInstance()->KeyClear();
	OperatorManager::GetInstance()->RegisterKey(VK_LEFT);
	OperatorManager::GetInstance()->RegisterKey(VK_RIGHT);
	OperatorManager::GetInstance()->RegisterKey(VK_UP);
	OperatorManager::GetInstance()->RegisterKey(VK_DOWN);
	OperatorManager::GetInstance()->RegisterKey(VK_LBUTTON);
}

void AirplaneGameScene::InputOperator(float fElapsedTime)
{
	if (m_gameState == READY || m_gameState == GAMEOVER)
	{
		return;
	}

	m_airplane.InputOperator();
}

void AirplaneGameScene::Update(float fElapsedTime)
{
	if (m_gameState == READY)
	{
		m_fGameReadyTimer += fElapsedTime;
		if (m_fGameReadyTimer > 1)
		{
			m_pReadyEndBitMap = DrawManager::GetInstnace()->GetBitMap("go.bmp");
		}
		if (m_fGameReadyTimer > 2)
		{
			m_gameState = PLAY;
			m_fGameReadyTimer = 0;
		}
		return;
	}

	if (m_gameState == GAMEOVER)
	{
		m_fGameReadyTimer += fElapsedTime;
		if (m_fGameReadyTimer > 2)
		{
			m_airplane.Kill();
			GameManager::GetInstance()->LoadScene(1);
			return;
		}
	}
	else
	{
		m_airplane.Instantiate();
	}

	CollisionManager::GetInstance()->ResetCircleCollier();
	//오브젝트 업데이트
	m_airplane.Update(fElapsedTime);
	m_fBulletInstatiateTime += fElapsedTime;

	if (m_fBulletInstatiateTime >= 0.3)
	{
		m_fBulletInstatiateTime = 0;
		m_bullet[m_bulletIdx % 100].Instantiate(m_airplane.GetPlaneCenterPos());
		m_bulletIdx++;
	}

	m_fStarInstatiateTime += fElapsedTime;
	if (m_fStarInstatiateTime >= 0.7)
	{
		m_fStarInstatiateTime = 0;
		m_star[m_starIdx % 100].Instantiate(m_airplane.GetPlaneCenterPos());
		m_starIdx++;
	}

	for (size_t i = 0; i < 100; i++)
	{
		m_bullet[i].Update(fElapsedTime);
		m_star[i].Update(fElapsedTime);
	}

	//충돌검사 구간
	saveCollObject.clear();
	if (CollisionManager::GetInstance()->CheckCollCircleCollider("airplane", "star", saveCollObject))
	{
		for (auto iter = saveCollObject.begin(); iter < saveCollObject.end(); iter++)
		{
			m_fever += 600;
			m_score += m_addScoreSize;
			m_addScoreSize += 100;
			((Star*)*iter)->Destroy();
		}
	}

	if(CollisionManager::GetInstance()->CheckCollCircleCollider("airplane", "bullet", saveCollObject))
	{
		m_airplane.Destroy();
		m_fever = 0;
		m_addScoreSize = 100;
		for (size_t i = 0; i < 100; i++)
		{
			m_bullet[i].Destroy();
			m_star[i].Destroy();
		}
	}

	m_fCloudLendPos -= CLOUDSPEED * fElapsedTime;

	if (m_fCloudLendPos <= 0)
	{
		m_secondCloud = true;
		m_fCloudLendPos = 0;
		m_fCloudDrawPos += CLOUDSPEED * fElapsedTime;;

		if (m_fCloudDrawPos >= 700)
		{
			m_fCloudLendPos = 1400;
			m_fCloudDrawPos = 0;
			m_secondCloud = false;
		}
	}

	//fever관리
	m_fTimer -= fElapsedTime;
	m_fFeverBarTime += fElapsedTime;
	m_fElapsedTimeForScore += fElapsedTime;
	m_feverLevel = m_fever / MAXFEVER;

	switch (m_feverLevel)
	{
	case 0:
		m_strFever = "NOT FEVER";
		break;
	case 1:
		m_strFever = "FEVER";
		break;
	case 2:
		m_strFever = "SUPER FEVER";
		break;
	default:
		break;
	}


	if (m_fFeverBarTime > 0.1)
	{
		m_fever += 5;
		m_fFeverBarTime = 0;
	}

	if (m_fElapsedTimeForScore > 1)
	{
		m_fElapsedTimeForScore = 0;
		m_score += 30;
	}

	if (m_fever >= 3000)
	{
		if (m_feverCount == 0)
		{
			for (size_t i = 0; i < 7; i++)
			{
				m_star[m_starIdx % 100].Instantiate(m_airplane.GetPlaneCenterPos());
				m_starIdx++;
			}
			m_feverCount++;
		}
	}

	if (m_fever >= 6000)
	{
		if (m_feverCount == 1)
		{
			for (size_t i = 0; i < 7; i++)
			{
				m_star[m_starIdx % 100].Instantiate(m_airplane.GetPlaneCenterPos());
				m_starIdx++;
			}
			m_fever = 0;
			m_feverCount = 0;
		}
	}


	if (m_fTimer < 0)
	{
		m_pReadyEndBitMap = DrawManager::GetInstnace()->GetBitMap("gameover.bmp");
		m_gameState = GAMEOVER;
		m_fTimer = 0;
	}

	m_button.Update();
}

bool AirplaneGameScene::Draw()
{
	m_pBackGround->Draw(0, 0);
	m_pCloud->Draw(0, m_fCloudDrawPos, 400, 700 - m_fCloudDrawPos,
		0, m_fCloudLendPos, 400, 700 - m_fCloudDrawPos);
	if (m_secondCloud)
	{
		m_pCloud->Draw(0, 0, 400, m_fCloudDrawPos,
			0, 2100 - m_fCloudDrawPos, 400, m_fCloudDrawPos);
	}

	///게임그리기 
	m_airplane.Draw();

	for (size_t i = 0; i < 100; i++)
	{
		m_star[i].DrawStar(m_addScoreSize);
	}

	for (size_t i = 0; i < 100; i++)
	{
		m_bullet[i].Draw();
	}
	
	m_pBackFrame->Draw(0, 0);

	int sec = (int)m_fTimer;
	int mSec = (m_fTimer - (int)m_fTimer) * 100;

	int barLenth = (((float)365 / (MAXTIME * 100)) * (m_fTimer * 100));
	int barRendLenth = (((float)300 / (MAXTIME * 100)) * (m_fTimer * 100));
	m_pTimerBar->Draw(20, 668, barLenth, 30, 0, 0, barRendLenth);

	if (m_fever <= MAXFEVER)
	{
		barLenth = (((float)360 / MAXFEVER) * m_fever);
		barRendLenth = (((float)300 / MAXFEVER) * m_fever);
	}
	else
	{
		barLenth = 360;
		barRendLenth = 300;
	}
	m_pFeverBar[0]->Draw(18, 57, barLenth, 32, 0, 0, barRendLenth);

	if (m_fever > MAXFEVER && m_fever <= MAXFEVER * 2)
	{
		barLenth = (((float)360 / MAXFEVER) * (m_fever - MAXFEVER));
		barRendLenth = (((float)300 / MAXFEVER) * (m_fever - MAXFEVER));
	}
	else if (m_fever <= MAXFEVER)
	{
		barLenth = 0;
		barRendLenth = 0;
	}
	else
	{
		barLenth = 360;
		barRendLenth = 300;
	}
	m_pFeverBar[1]->Draw(18, 57, barLenth, 32, 0, 0, barRendLenth);

	if (m_fever > MAXFEVER * 2 && m_fever <= MAXFEVER * 3)
	{
		barLenth = (((float)360 / MAXFEVER) * (m_fever - MAXFEVER * 2));
		barRendLenth = (((float)300 / MAXFEVER) * (m_fever - MAXFEVER * 2));
	}
	else if (m_fever <= MAXFEVER * 2)
	{
		barLenth = 0;
		barRendLenth = 0;
	}
	else
	{
		barLenth = 360;
		barRendLenth = 300;
	}

	m_pFeverBar[2]->Draw(18, 57, barLenth, 32, 0, 0, barRendLenth);

	DrawManager::GetInstnace()->PutText(m_strFever, 100, 63, 300, 89);

	char buf[20];
	sprintf(buf, "%02d : %02d", sec, mSec);
	DrawManager::GetInstnace()->PutText(buf, 100, 675, 300, 775);
	sprintf(buf, "%d", m_score);
	DrawManager::GetInstnace()->PutText(buf, 100, 30, 300, 60);

	m_button.Draw();

	if (m_gameState == READY || m_gameState == GAMEOVER)
	{
		m_pReadyEndBitMap->Draw(0, 250);
	}


	return true;
}

void AirplaneGameScene::Release()
{

}

AirplaneGameScene::AirplaneGameScene()
{
}


AirplaneGameScene::~AirplaneGameScene()
{
}
