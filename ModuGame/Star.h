#pragma once
#include "Enemy.h"
class Star :
	public Enemy
{
public:
	virtual void Instantiate(PointF airplanePos);
	virtual void Update(float fElapsedTime);
	virtual void DrawStar(int score);

	Star();
	virtual ~Star();
};

