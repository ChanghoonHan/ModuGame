#include "SelectGameScene.h"
#include "../HCHEngine/DrawManager.h"

int SelectGameScene::CallBackGoPaper()
{
	GameManager::GetInstance()->LoadScene(2);
	return 0;
}

int SelectGameScene::CallBackGoAirplane()
{
	GameManager::GetInstance()->LoadScene(3);
	return 0;
}

void SelectGameScene::Init()
{
	m_pBitMap = DrawManager::GetInstnace()->GetBitMap("stageSelect.bmp");
	m_goPaperGameButton.Init("SelectGame1.bmp", "SelectGame2.bmp", 
		305, 268, 57, 68, bind(&SelectGameScene::CallBackGoPaper, this));
	m_goAirplaneGameButton.Init("SelectGame1.bmp", "SelectGame2.bmp", 
		305, 358, 57, 68, bind(&SelectGameScene::CallBackGoAirplane, this));

	OperatorManager::GetInstance()->KeyClear();
	OperatorManager::GetInstance()->RegisterKey(VK_LBUTTON);
}

void SelectGameScene::InputOperator(float fElapsedTime)
{

}

void SelectGameScene::Update(float fElapsedTime)
{
	m_goPaperGameButton.Update();
	m_goAirplaneGameButton.Update();
}

bool SelectGameScene::Draw()
{
	m_pBitMap->Draw(0, 0);
	m_goPaperGameButton.Draw();
	m_goAirplaneGameButton.Draw();
	return true;
}

void SelectGameScene::Release()
{

}

SelectGameScene::SelectGameScene()
{
}


SelectGameScene::~SelectGameScene()
{
}
