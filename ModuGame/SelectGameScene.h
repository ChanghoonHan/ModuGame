#pragma once
#include "../HCHEngine/Scene.h"
#include "../HCHEngine/BitMap.h"
#include "../HCHEngine/OperatorManager.h"
#include "../HCHEngine/Button.h"

class SelectGameScene :
	public Scene
{
	BitMap* m_pBitMap;
	Button m_goPaperGameButton;
	Button m_goAirplaneGameButton;

	int CallBackGoPaper();
	int CallBackGoAirplane();
public:
	virtual void Init();
	virtual void InputOperator(float fElapsedTime);
	virtual void Update(float fElapsedTime);
	virtual bool Draw();
	virtual void Release();

	SelectGameScene();
	virtual ~SelectGameScene();
};

