#include "Star.h"

void Star::Instantiate(PointF airplanePos)
{
	if (m_bIsLive)
	{
		return;
	}

	m_fSpeed = 100;

	m_bitMapSize = 50;

	m_circlecollider.type = "star";

	m_pBitMap.clear();
	m_pBitMap.push_back(DrawManager::GetInstnace()->GetBitMap("yellowstar.bmp"));
	m_pBitMap.push_back(DrawManager::GetInstnace()->GetBitMap("greenstar.bmp"));
	m_pBitMap.push_back(DrawManager::GetInstnace()->GetBitMap("puplestar.bmp"));

	Enemy::Instantiate(airplanePos);
}

void Star::Update(float fElapsedTime)
{
	if (!m_bIsLive)
	{
		return;
	}

	Enemy::Update(fElapsedTime);
}

void Star::DrawStar(int score)
{
	if (!m_bIsLive)
	{
		return;
	}

	if (score < 1000)
	{
		m_bitMapIdx = 0;
	}
	else if (score < 3000)
	{
		m_bitMapIdx = 1;
	}
	else
	{
		m_bitMapIdx = 2;
	}
	Enemy::Draw();
	char strScore[20];
	sprintf(strScore, "%d", score);
	DrawManager::GetInstnace()->PutText(strScore, m_fPos.fX + 5, m_fPos.fY + 20, m_fPos.fX + 50 - 5, m_fPos.fY + 40, DT_CENTER);
}


Star::Star()
{
}


Star::~Star()
{
}
