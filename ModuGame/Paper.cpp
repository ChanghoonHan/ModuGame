#include "Paper.h"
#include "../HCHEngine/DrawManager.h"

void Paper::SetPos(int x, int y)
{
	m_fPos.fX = x;
	m_fPos.fY = y;
}

void Paper::Init(int x, int y)
{
	SetPos(x, y);

	m_WrongMoveTime = 0;

	m_direct = STOP;

	m_bIsDestroy = false;

	m_bIsWrong = false;

	m_paperType = (PAPERTYPE)(rand() % 4);

	switch (m_paperType)
	{
	case GREEN:
		m_pBitMap = DrawManager::GetInstnace()->GetBitMap("greenPaper.bmp");
		break;
	case RED:
		m_pBitMap = DrawManager::GetInstnace()->GetBitMap("redPaper.bmp");
		break;
	case YELLOW:
		m_pBitMap = DrawManager::GetInstnace()->GetBitMap("yellowPaper.bmp");
		break;
	case BLUE:
		m_pBitMap = DrawManager::GetInstnace()->GetBitMap("bluePaper.bmp");
		break;
	default:
		break;
	}
}

INPUTCORRECT Paper::OperatorInput()
{
	if (OperatorManager::GetInstance()->IsKeyDown(VK_LEFT))
	{
		if (m_paperType == BLUE)
		{
			m_direct = LEFT;
			return CORRECT;
		}
		m_bIsWrong = true;
		return WRONG;
	}

	if (OperatorManager::GetInstance()->IsKeyDown(VK_RIGHT))
	{
		if (m_paperType == RED)
		{
			m_direct = RIGHT;
			return CORRECT;
		}
		m_bIsWrong = true;
		return WRONG;
	}

	if (OperatorManager::GetInstance()->IsKeyDown(VK_DOWN))
	{
		if (m_paperType == YELLOW)
		{
			m_direct = BOTTOM;
			return CORRECT;
		}
		m_bIsWrong = true;
		return WRONG;
	}

	if (OperatorManager::GetInstance()->IsKeyDown(VK_UP))
	{
		if (m_paperType == GREEN)
		{
			m_direct = TOP;
			return CORRECT;
		}
		m_bIsWrong = true;
		return WRONG;
	}

	return NORMAL;
}

bool Paper::Update(float fElapsedTime)
{
	if (m_bIsDestroy)
	{
		return false;
	}

	switch (m_direct)
	{
	case STOP:
		if (m_bIsWrong)
		{
			m_WrongMoveTime += fElapsedTime;
			if (m_WrongMoveTime < 0.05)
			{
				m_fPos.fX = 160;
			}
			else if (m_WrongMoveTime < 0.1)
			{
				m_fPos.fX = 140;
			}
			else
			{
				m_fPos.fX = 150;
				m_WrongMoveTime = 0;
				m_bIsWrong = false;
			}
		}
		return false;
		break;
	case TOP:
		m_fPos.fY -= PAPERSPEED * fElapsedTime;
		if (m_fPos.fY < 160)
		{
			Destroy();
			return true;
		}
		break;
	case BOTTOM:
		m_fPos.fY += PAPERSPEED * fElapsedTime;
		if (m_fPos.fY > 480)
		{
			Destroy();
			return true;
		}
		break;
	case LEFT:
		m_fPos.fX -= PAPERSPEED * fElapsedTime;
		if (m_fPos.fX < 20)
		{
			Destroy();
			return true;
		}
		break;
	case RIGHT:
		m_fPos.fX += PAPERSPEED * fElapsedTime;
		if (m_fPos.fX > 290)
		{
			Destroy();
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

void Paper::Draw()
{
	if (m_bIsDestroy)
	{
		return;
	}

	m_pBitMap->Draw(m_fPos.fX, m_fPos.fY);
}

void Paper::Destroy()
{
	m_bIsDestroy = true;
}

Paper::Paper()
{
	m_bIsDestroy = false;
}


Paper::~Paper()
{
}
