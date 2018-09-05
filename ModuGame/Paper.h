#pragma once
#include "../HCHEngine/BitMap.h"

#define PAPERSPEED 1500

enum PAPERTYPE
{
	GREEN,
	RED,
	YELLOW,
	BLUE,
};

enum PAPERMOVEDIR
{
	STOP,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

enum INPUTCORRECT
{
	WRONG,
	CORRECT,
	NORMAL
};

class Paper
{
	PAPERMOVEDIR m_direct;
	PAPERTYPE m_paperType;
	BitMap* m_pBitMap;
	bool m_bIsWrong;
	float m_WrongMoveTime;
	bool m_bIsDestroy;
	PointF m_fPos;

public:
	void SetPos(int x, int y);
	void Init(int x, int y);
	INPUTCORRECT OperatorInput();
	bool Update(float fElapsedTime);
	void Draw();
	void Destroy();

	Paper();
	~Paper();
};

