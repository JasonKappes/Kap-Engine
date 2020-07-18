#include "AzulCore.h"
#include "KapEngine.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "SceneManagerAttorney.h"
#include "SceneDemo.h"
#include "SouljaBoyTankThat.h"
#include "ModelManagerAttorney.h"
#include "ShaderManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "TimeManagerAttorney.h"
#include "ImageManagerAttorney.h"
#include "SpriteFontManagerAttorney.h"
#include "TimeManager.h"
#include "FreezeTime.h"
#include "NullScene.h"
#include "VisualizerAttorney.h"
#include "ScreenLogAttorney.h"
#include "JsonHandlerAttorney.h"
#include "RollbackHandlerAttorney.h"
#include "Raycast.h"
#include "CursorAttorney.h"
#include "TerrainLoaderAttorney.h"

KapEngine* KapEngine::m_ptrInstance = nullptr;

KapEngine::KapEngine() : m_currScene(nullptr), m_totalTime(0.0f), m_prevTime(0.0f), m_frameTime(0.0f) {}

void KapEngine::Game_Run()	
{	
	Instance().Game_Start();	
	Instance().run();
}

void KapEngine::Game_Start() {  Instance().Initialize(); }

void KapEngine::Game_End() 
{	
	Instance().User_Game_End();
	Instance().Terminate(); 
}

void KapEngine::Initialize()
{
	KapEngine::User_Game_Start();
}

void KapEngine::LoadContent()
{
	KapEngine::User_LoadAllResources();

	SceneManagerAttorney::Base::InitStartScene();
}

void KapEngine::Update()
{	
	TimeManagerAttorney::ProcessTime(this->GetTimeInSeconds());
	CursorAttorney::ProcessCursorMovement();
	SceneManagerAttorney::Base::Update();
}

void KapEngine::Draw()
{
	VisualizerAttorney::GameLoop::VisualizeAll();
	SceneManagerAttorney::Base::Draw();
	//UI render
	ScreenLogAttorney::Render();
}

void KapEngine::UnLoadContent()
{
	CursorAttorney::Delete();
	SceneManagerAttorney::Base::Delete();
	TimeManagerAttorney::Delete();
	ShaderManagerAttorney::Delete();
	ModelManagerAttorney::Delete();
	ImageManagerAttorney::Delete();
	SpriteFontManagerAttorney::Delete();
	TextureManagerAttorney::Delete();
	VisualizerAttorney::GameLoop::Delete();
	ScreenLogAttorney::Delete();
	JsonHandlerAttorney::Delete();
	RollbackHandlerAttorney::Delete();
	TerrainLoaderAttorney::Delete();
	DebugMsg::out("\n after sprite font manager");
}


