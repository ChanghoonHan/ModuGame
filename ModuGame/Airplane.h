#pragma once
#include "../HCHEngine/BitMap.h"
#include "../HCHEngine/CollisionManager.h"

enum AIRPLANESTATE
{
	INSTANTIATE,
	LIVE,
	EXPLODE,
	DIE,
};

class Airplane
{
	BitMap* m_pAirplaneBitMap[2];
	BitMap* m_pExplodeBitMap[4];
	PointF m_fDrawPos;
	PointF m_fCenterPos;
	CircleCollider m_circlecollider;

	Circle m_collider;
	int m_explodeBitMapIdx;
	float m_fBitMapChangeTime;
	bool m_bAirplaneBitMapIdx;
	AIRPLANESTATE m_state;

public:
	void Instantiate();
	void InputOperator();
	void Update(float fElapsedTime);
	void Draw();
	void Destroy();
	void Kill();
	PointF& GetPlaneCenterPos();

	Airplane();
	~Airplane();
};

