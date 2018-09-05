#pragma once
#include "../HCHEngine/Scene.h"
#include "../HCHEngine/BitMap.h"
#include "../HCHEngine/OperatorManager.h"
#include "../HCHEngine/Button.h"

class IntroScene :
	public Scene
{
	BitMap* m_pBitMap;
	Button m_button;

	int CallBack();

public:
	virtual void Init();
	virtual void InputOperator(float fElapsedTime);
	virtual void Update(float fElapsedTime);
	virtual bool Draw();
	virtual void Release();

	IntroScene();
	virtual ~IntroScene();
};

