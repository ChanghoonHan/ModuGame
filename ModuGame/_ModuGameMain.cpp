#include "../HCHEngine/GameEngineMain.h"
#include "../HCHEngine/GameManager.h"
#include "../HCHEngine/Scene.h"

#include "IntroScene.h"
#include "SelectGameScene.h"
#include "PaperGameScene.h"
#include "AirplaneGameScene.h"

using namespace HCHEngine;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(744);

	GameManager::GetInstance()->RegisterScene(new IntroScene);//차례대로 SceneIndex 0부터..
	GameManager::GetInstance()->RegisterScene(new SelectGameScene);
	GameManager::GetInstance()->RegisterScene(new PaperGameScene);
	GameManager::GetInstance()->RegisterScene(new AirplaneGameScene);

	GameEngineMain engine("ModuGame", 400, 700);

	return engine.StartEngine(hInstance);
}