#include "Enemy.h"

void Enemy::Instantiate(PointF airplanePos)
{
	m_bitMapIdx = 0;

	m_randDir = (INSTANTIATEDIR)(rand() % 3);

	m_bIsLive = true;

	switch (m_randDir)
	{
	case LEFT:
		m_fPos.fX = -m_bitMapSize;
		m_fPos.fY = rand() % 680;
		break;
	case TOP:
		m_fPos.fX = rand() % 380;
		m_fPos.fY = 100 - m_bitMapSize;
		break;
	case RIGHT:
		m_fPos.fX = 700;
		m_fPos.fY = rand() % 680;
		break;
	default:
		break;
	}

	m_collider.SetCircle(m_fPos.fX, m_fPos.fY, m_fPos.fX + m_bitMapSize, m_fPos.fY + m_bitMapSize);
	m_circlecollider.collider = m_collider;
	m_circlecollider.colliderOwner = this;
	m_fMoveDir.fX = (m_collider.m_center.fX - airplanePos.fX) * 
		(1 / sqrtf(pow(m_collider.m_center.fX - airplanePos.fX, 2) + pow(m_collider.m_center.fY - airplanePos.fY, 2)));
	m_fMoveDir.fY = (m_collider.m_center.fY - airplanePos.fY) *
		(1 / sqrtf(pow(m_collider.m_center.fX - airplanePos.fX, 2) + pow(m_collider.m_center.fY - airplanePos.fY, 2)));
}

void Enemy::Update(float fElapsedTime)
{
	m_fPos.fX += -m_fMoveDir.fX * fElapsedTime * m_fSpeed;
	m_fPos.fY += -m_fMoveDir.fY * fElapsedTime * m_fSpeed;
	m_collider.SetCircle(m_fPos.fX, m_fPos.fY, m_fPos.fX + m_bitMapSize, m_fPos.fY + m_bitMapSize);
	m_circlecollider.collider = m_collider;

	switch (m_randDir)
	{
	case LEFT:
		if (m_fPos.fX > 400 || m_fPos.fY < -m_bitMapSize || m_fPos.fY > 700)
		{
			m_bIsLive = false;
		}
		break;

	case TOP:
		if (m_fPos.fY > 700 || m_fPos.fX < -m_bitMapSize || m_fPos.fX > 400)
		{
			m_bIsLive = false;
		}
		break;

	case RIGHT:
		if (m_fPos.fY < -m_bitMapSize || m_fPos.fY > 700 || m_fPos.fX < -m_bitMapSize)
		{
			m_bIsLive = false;
		}
		break;
	default:
		break;
	}

	if (m_bIsLive)
	{
		CollisionManager::GetInstance()->SetCircleCollider(&m_circlecollider);
	}
}

void Enemy::Draw()
{
	if (!m_bIsLive)
	{
		return;
	}

	m_pBitMap[m_bitMapIdx]->Draw(m_fPos.fX, m_fPos.fY);
}

void Enemy::Destroy()
{
	m_bIsLive = false;
}

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
