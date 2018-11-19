#ifndef APPLICATIONH
#define APPLICATIONH
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Scenes/Scene.h"
#include "Input/InputManager.h"

class Application
{
private:
	GLFWwindow* p_window;
	uint16_t	p_windowWidth;
	uint16_t	p_windowHeight;
	char*		p_windowTitle;

	Scene*		p_scene;
	
	InputManager* p_inputManager;
	double calcFPS(double theTimeInterval, std::string theWindowTitle);
	// For delta
	double p_currentFrame;
	double p_deltaTime;
	double p_lastFrame;
public:

	Application();
	virtual ~Application();

	bool initialize(const char* appTitle, uint16_t appWidth, uint16_t appHeight);
	void run();


};


#endif
