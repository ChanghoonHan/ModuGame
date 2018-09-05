#include "IntroScene.h"
#include "../HCHEngine/DrawManager.h"

int IntroScene::CallBack()
{
	GameManager::GetInstance()->LoadScene(1);
	return 0;
}

void IntroScene::Init()
{
	m_pBitMap = DrawManager::GetInstnace()->GetBitMap("main.bmp");
	m_button.Init("START1.bmp", "START2.bmp", 87, 610, 226, 65, bind(&IntroScene::CallBack, this));
	OperatorManager::GetInstance()->KeyClear();
	OperatorManager::GetInstance()->RegisterKey(VK_LBUTTON);
}

void IntroScene::InputOperator(float fElapsedTime)
{

}

void IntroScene::Update(float fElapsedTime)
{
	m_button.Update();
}

bool IntroScene::Draw()
{
	m_pBitMap->Draw(0, 0);
	m_button.Draw();

	return true;
}

void IntroScene::Release()
{

}

IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}
