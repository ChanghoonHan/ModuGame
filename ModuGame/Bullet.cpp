#include "Bullet.h"

void Bullet::Instantiate(PointF airplanePos)
{
	if (m_bIsLive)
	{
		return;
	}

	m_fSpeed = 100;
	
	m_bitMapSize = 20;

	m_circlecollider.type = "bullet";

	m_pBitMap.clear();
	m_pBitMap.push_back(DrawManager::GetInstnace()->GetBitMap("bullet.bmp"));

	Enemy::Instantiate(airplanePos);
}

void Bullet::Update(float fElapsedTime)
{
	if (!m_bIsLive)
	{
		return;
	}

	Enemy::Update(fElapsedTime);
}

Bullet::Bullet()
{
	m_bIsLive = false;
}


Bullet::~Bullet()
{
}
