#include "KapEngine.h"

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{        
	srand((unsigned int)time(NULL));

	KapEngine::Game_Run();
	KapEngine::Game_End();

	return 0;                                       
}
