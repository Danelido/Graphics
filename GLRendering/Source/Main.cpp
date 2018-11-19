#include <iostream>
#include "Core/Application.h"

#ifdef _WIN32
	#ifdef _DEBUG
		#define MEM_FLG 1
	#else
		#define MEM_FLG 0;
	#endif
#else
	#define MEM_FLG 0;
#endif

int main()
{

#if MEM_FLG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Application app;
	
	if (app.initialize("OpenGL Real-Time Rendering", 1280, 720))
		app.run();
	else
		system("pause");

	return 0;
}
