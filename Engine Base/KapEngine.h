#ifndef _KapEngine
#define _KapEngine

/// <summary>
/// 
/// </summary>

#include "AzulCore.h"

class SceneDemo;

class KapEngine : public Engine
{
	friend class KapEngineAttorney;

public: // ----> USER METHODS

	/// <summary>
	/// Sets the width and height of the game window being displayed
	/// </summary> 
	/// \ingroup GameSetup
	static void SetWindowWidthHeight(const int t_width, const int t_height) { Instance().setWidthHeight(t_width, t_height); }
	
	/// <summary>
	/// Sets the name of the game window being displayed
	/// </summary> 
	/// \ingroup GameSetup
	static void SetWindowName(const char* t_WindowName) { Instance().setWindowName(t_WindowName); }

	/// <summary>
	/// Sets the color of an empty scene
	/// </summary> 
	/// \ingroup GameSetup
	static void SetColor(float t_red, float t_green, float t_blue, float t_alpha) { Instance().SetClearColor(t_red, t_green, t_blue, t_alpha); }
		
	/// <summary>
	/// Allows the gamer to synchronize the frame rate of the game with the monitor refresh rate for better stability.
	/// </summary> 
	/// \ingroup GameSetup
	static void SetVsync(bool t_enable) { Instance().setVsync(t_enable); }

	/// <summary>
	/// Returns the game window height. It needs to be called through the engine.
	/// </summary> 
	/// \ingroup GameSetup  
	static int GetWindowHeight() { return Instance().getHeight(); }

	/// <summary>
	/// Returns the game window width. It needs to be called through the engine.
	/// </summary> 
	/// \ingroup GameSetup 
	static int GetWindowWidth() { return Instance().getWidth(); }

	/// <summary>
	/// Returns the x and y position of the mouse in the game window
	/// </summary> 
	/// \ingroup GameSetup 
	static void GetMousePosition(int& x, int& y) { Engine::getMousePosition(x, y); }

	/// <summary>
	/// Called through main (automatically) to run the game
	/// </summary> 
	/// \ingroup GameSetup 
	static void Game_Run();

	/// <summary>
	/// Called through main (automatically) to end the game
	/// </summary> 
	/// \ingroup GameSetup 
	static void Game_End();

private: // ----> USER METHODS (to override)

	/// <summary>
	/// Method to be overriden in the User's GameStart.cpp -> It needs to be overriden from the engine.
	/// 
	/// This function is called before the game runs. Needs to call SetWindowName, SetWidthHeight, and SetClearColor.
	/// </summary> 
	/// \ingroup GameSetup 
	virtual void User_Game_Start();

	/// <summary>
	/// Method to be overriden in the User's GameEnd.cpp -> It needs to be overriden from the engine.
	/// 
	/// This function is called on termination of the game.
	/// </summary> 
	/// \ingroup GameSetup 
	virtual void User_Game_End();

	/// <summary>
	/// Method to be overriden in the User's LoadAllResources.cpp -> It needs to be override from the engine.
	/// 
	/// This function needs to loads any used resources (models, textures, shaders) and set the starting scene to run.
	/// </summary> 
	/// \ingroup GameSetup 
	virtual void User_LoadAllResources();

private: // ----> Engine Methods
	KapEngine();
	KapEngine(const KapEngine&) = delete;
	KapEngine operator=(const KapEngine&) = delete;
	~KapEngine() = default;

	static float GetTime() { return Instance().GetTimeInSeconds(); }

	static void Game_Start();

	virtual void Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();
	
	void Terminate() { delete this->m_ptrInstance; }

	static KapEngine& Instance()	    // Access reference (all public methods will be static)
	{
		if (!m_ptrInstance)
			m_ptrInstance = new KapEngine;
		return *m_ptrInstance;
	};

private:
	static KapEngine* m_ptrInstance;
	SceneDemo* m_currScene;
	float m_totalTime;
	float m_prevTime;
	float m_frameTime;
};

#endif _KapEngine