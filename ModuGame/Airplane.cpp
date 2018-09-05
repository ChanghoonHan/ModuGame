#include "Airplane.h"

void Airplane::Instantiate()
{
	if (m_state != DIE)
	{
		return;
	}

	m_pAirplaneBitMap[0] = DrawManager::GetInstnace()->GetBitMap("airplane1.bmp");
	m_pAirplaneBitMap[1] = DrawManager::GetInstnace()->GetBitMap("airplane2.bmp");
	m_pExplodeBitMap[0] = DrawManager::GetInstnace()->GetBitMap("explode1.bmp");
	m_pExplodeBitMap[1] = DrawManager::GetInstnace()->GetBitMap("explode2.bmp");
	m_pExplodeBitMap[2] = DrawManager::GetInstnace()->GetBitMap("explode3.bmp");
	m_pExplodeBitMap[3] = DrawManager::GetInstnace()->GetBitMap("explode4.bmp");
	m_explodeBitMapIdx = 0;
	m_fDrawPos.fX = 200 - 65 / 2;
	m_fDrawPos.fY = 450;
	m_fCenterPos.fX = m_fDrawPos.fX + 65 / 2;
	m_fCenterPos.fY = m_fDrawPos.fY + 73 / 2;
	m_circlecollider.type = "airplane";
	m_collider.SetCircle(m_fDrawPos.fX, m_fDrawPos.fY, m_fDrawPos.fX + 65, m_fDrawPos.fY + 73);
	m_circlecollider.collider = m_collider;
	m_fBitMapChangeTime = 0;
	m_bAirplaneBitMapIdx = false;
	m_state = INSTANTIATE;
}

void Airplane::InputOperator()
{
	if (m_state != LIVE && m_state != INSTANTIATE)
	{
		return;
	}

	m_fDrawPos.fX = OperatorManager::GetInstance()->GetMousePos()->iX;
	m_fDrawPos.fY = OperatorManager::GetInstance()->GetMousePos()->iY;

	if (m_fDrawPos.fX > 400 - 65/2)
	{
		m_fDrawPos.fX = 400 - 65;
	}
	else if (m_fDrawPos.fX < 73 / 2)
	{
		m_fDrawPos.fX = 0;
	}
	else
	{
		m_fDrawPos.fX -= (65 / 2);
	}

	if (m_fDrawPos.fY > 660 - 65 / 2)
	{
		m_fDrawPos.fY = 660 - 73;
	}
	else if (m_fDrawPos.fY < 95 + 73 / 2)
	{
		m_fDrawPos.fY = 95;
	}
	else
	{
		m_fDrawPos.fY -= (73 / 2);
	}
	
	m_fCenterPos.fX = m_fDrawPos.fX + 65 / 2;
	m_fCenterPos.fY = m_fDrawPos.fY + 73 / 2;
	m_collider.SetCircle(m_fDrawPos.fX + 16, m_fDrawPos.fY - 17, m_fDrawPos.fX + 65 - 16, m_fDrawPos.fY + 73 - 23);
	m_circlecollider.collider = m_collider;
}

void Airplane::Update(float fElapsedTime)
{
	if (m_state == INSTANTIATE)
	{
		m_fBitMapChangeTime += fElapsedTime;
		if (m_fBitMapChangeTime > 1)
		{
			m_state = LIVE;
			m_fBitMapChangeTime = 0;
		}

		return;
	}

	if (m_state == EXPLODE)
	{
		m_fBitMapChangeTime += fElapsedTime;
		if (m_fBitMapChangeTime > 0.1)
		{
			m_fBitMapChangeTime = 0;
			m_explodeBitMapIdx++;
		}
		
		if(m_explodeBitMapIdx == 4)
		{
			m_state = DIE;
		}

		return;
	}

	if (m_state == DIE)
	{
		return;
	}

	m_fBitMapChangeTime += fElapsedTime;
	if (m_fBitMapChangeTime > 0.05)
	{
		m_fBitMapChangeTime = 0;
		m_bAirplaneBitMapIdx = !m_bAirplaneBitMapIdx;
	}

	if (m_state == LIVE)
	{
		CollisionManager::GetInstance()->SetCircleCollider(&m_circlecollider);
	}
}

void Airplane::Destroy()
{
	if (m_state != LIVE)
	{
		return;
	}
	m_state = EXPLODE;
	m_fBitMapChangeTime = 0;
}

void Airplane::Kill()
{
	m_state = DIE;
}

void Airplane::Draw()
{
	if (m_state == DIE)
	{
		return;
	}

	if (m_state == EXPLODE)
	{
		m_pExplodeBitMap[m_explodeBitMapIdx]->Draw(m_collider.m_center.fX - 50, m_collider.m_center.fY - 50);
		return;
	}

	m_pAirplaneBitMap[m_bAirplaneBitMapIdx]->Draw(m_fDrawPos.fX, m_fDrawPos.fY);
}

PointF& Airplane::GetPlaneCenterPos()
{
	return m_fCenterPos;
}

Airplane::Airplane()
{
	m_state = DIE;
}


Airplane::~Airplane()
{
}
