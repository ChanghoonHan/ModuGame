#include "PaperGameScene.h"
#include "../HCHEngine/DrawManager.h"

int PaperGameScene::CallBack()
{
	GameManager::GetInstance()->LoadScene(1);
	return 0;
}

void PaperGameScene::Init()
{
	m_gameState = READY;
	m_fGameReadyTimer = 0;
	m_strFever = "";
	m_bSuperFeverBitMapChange = false;
	m_bSuperFever = false;
	m_fSuperFeverBitMapTime = 0;
	m_score = 0;
	m_fever = 0;
	m_feverLevel = 0;
	m_fFeverBarTime = 0;
	m_topPaperIndex = 0;
	m_fElapsedTimeForTimer = 0;
	m_fTimer = MAXTIME;

	m_button.Init("backButton1.bmp", "backButton2.bmp", 355, 5, 40, 40, bind(&PaperGameScene::CallBack, this));
	m_pBackGround = DrawManager::GetInstnace()->GetBitMap("paperGameBack.bmp");
	m_pTimerBar = DrawManager::GetInstnace()->GetBitMap("timerBar.bmp");
	m_pReadyEndBitMap = DrawManager::GetInstnace()->GetBitMap("ready.bmp");
	m_pFeverBar[0] = DrawManager::GetInstnace()->GetBitMap("feverBar1.bmp");
	m_pFeverBar[1] = DrawManager::GetInstnace()->GetBitMap("feverBar2.bmp");
	m_pFeverBar[2] = DrawManager::GetInstnace()->GetBitMap("feverBar3.bmp");

	m_paper[m_topPaperIndex].Init(m_paperPos[0].iX, m_paperPos[0].iY);
	m_paper[m_topPaperIndex + 1].Init(m_paperPos[1].iX, m_paperPos[1].iY);
	m_paper[m_topPaperIndex + 2].Init(m_paperPos[1].iX, m_paperPos[1].iY);
	m_paper[m_topPaperIndex + 2].Destroy();


	OperatorManager::GetInstance()->KeyClear();
	OperatorManager::GetInstance()->RegisterKey(VK_LEFT);
	OperatorManager::GetInstance()->RegisterKey(VK_RIGHT);
	OperatorManager::GetInstance()->RegisterKey(VK_UP);
	OperatorManager::GetInstance()->RegisterKey(VK_DOWN);
	OperatorManager::GetInstance()->RegisterKey(VK_LBUTTON);
}

void PaperGameScene::InputOperator(float fElapsedTime)
{
	if (m_gameState == READY || m_gameState == GAMEOVER)
	{
		return;
	}

	INPUTCORRECT ic = m_paper[m_topPaperIndex].OperatorInput();
	if (ic == CORRECT)
	{
		m_topPaperIndex++;
		m_topPaperIndex = m_topPaperIndex % 3;
		m_paper[m_topPaperIndex].SetPos(m_paperPos[0].iX, m_paperPos[0].iY);
		m_paper[(m_topPaperIndex+1) % 3].Init(m_paperPos[1].iX, m_paperPos[1].iY);
	}
	else if (ic == WRONG)
	{
		m_fever -= MINUSFEVER;
		if (m_fever < 0)
		{
			m_fever = 0;
		}
	}
}

void PaperGameScene::Update(float fElapsedTime)
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
			GameManager::GetInstance()->LoadScene(1);
		}

		return;
	}

	m_fTimer -= fElapsedTime;
	m_fFeverBarTime += fElapsedTime;
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
	case 3:
		m_strFever = "ULTRA FEVER";
		m_bSuperFever = true;
		break;
	default:
		break;
	}

	if (!m_bSuperFever)
	{
		if (m_fFeverBarTime > 0.1)
		{
			switch (m_feverLevel)
			{
			case 0:
				m_fever -= 10;
				break;
			case 1:
				m_fever -= 30;
				break;
			case 2:
				m_fever -= 50;
				break;
			case 3:
				m_bSuperFever = true;
				break;
			default:
				break;
			}

			if (m_fever < 0)
			{
				m_fever = 0;
			}

			m_fFeverBarTime = 0;
		}
	}
	else
	{
		m_fSuperFeverBitMapTime += fElapsedTime;
		if (m_fSuperFeverBitMapTime > 0.2)
		{
			m_bSuperFeverBitMapChange = !m_bSuperFeverBitMapChange;
			m_fSuperFeverBitMapTime = 0;
		}
		
		if (m_bSuperFeverBitMapChange)
		{
			m_pFeverBar[2] = DrawManager::GetInstnace()->GetBitMap("feverBar3_1.bmp");
		}
		else
		{
			m_pFeverBar[2] = DrawManager::GetInstnace()->GetBitMap("feverBar3.bmp");
		}

		if (m_fFeverBarTime > 5)
		{
			m_bSuperFeverBitMapChange = false;
			m_pFeverBar[2] = DrawManager::GetInstnace()->GetBitMap("feverBar3.bmp");
			m_fSuperFeverBitMapTime = 0;
			m_bSuperFever = false;
			m_fever = 0;
		}
	}
	

	if (m_fTimer < 0)
	{
		m_pReadyEndBitMap = DrawManager::GetInstnace()->GetBitMap("gameover.bmp");
		m_gameState = GAMEOVER;
		m_fTimer = 0;
	}

	for (size_t i = 0; i < 3; i++)
	{
		if (m_paper[i].Update(fElapsedTime))
		{
			m_fever += 600;

			switch (m_feverLevel)
			{
			case 0:
				m_score += 100;
				break;
			case 1:
				m_score += 1000;
				break;
			case 2:
				m_score += 2500;
				break;
			case 3:
				m_score += 10000;
				break;
			default:
				break;
			}
		}
	}

	m_button.Update();
}

bool PaperGameScene::Draw()
{
	m_pBackGround->Draw(0, 0);

	m_paper[(m_topPaperIndex + 1) % 3].Draw();
	m_paper[m_topPaperIndex].Draw();
	m_paper[(m_topPaperIndex + 2) % 3].Draw();

	
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

	if (m_fever > MAXFEVER && m_fever <= MAXFEVER*2)
	{
		barLenth = (((float)360 / MAXFEVER) * (m_fever - MAXFEVER));
		barRendLenth = (((float)300 / MAXFEVER) * (m_fever - MAXFEVER));
	}
	else if(m_fever <= MAXFEVER)
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

	if (m_fever > MAXFEVER*2 && m_fever <= MAXFEVER * 3)
	{
		barLenth = (((float)360 / MAXFEVER) * (m_fever - MAXFEVER*2));
		barRendLenth = (((float)300 / MAXFEVER) * (m_fever - MAXFEVER*2));
	}
	else if (m_fever <= MAXFEVER*2)
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

void PaperGameScene::Release()
{

}

PaperGameScene::PaperGameScene()
{
}


PaperGameScene::~PaperGameScene()
{
}
