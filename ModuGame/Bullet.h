#pragma once
#include "Enemy.h"


class Bullet :
	public Enemy
{

public:
	virtual void Instantiate(PointF airplanePos);
	virtual void Update(float fElapsedTime);

	Bullet();
	~Bullet();
};

