#pragma once
#include "../HCHEngine/Circle.h"
#include "../HCHEngine/BitMap.h"
#include "../HCHEngine/Point.h"
#include "../HCHEngine/CollisionManager.h"
#include <random>

class Enemy
{
protected:
	enum INSTANTIATEDIR
	{
		LEFT,
		TOP,
		RIGHT,
	};

	INSTANTIATEDIR m_randDir;
	CircleCollider m_circlecollider;
	bool m_bIsLive;

	float m_fSpeed;
	int m_bitMapSize;
	int m_bitMapIdx;

	vector<BitMap*> m_pBitMap;
	Circle m_collider;
	PointF m_fPos;
	PointF m_fMoveDir;

public:
	virtual void Instantiate(PointF airplanePos);
	virtual void Update(float fElapsedTime);
	
	virtual void Draw();

	void Destroy();

	Enemy();
	~Enemy();
};

