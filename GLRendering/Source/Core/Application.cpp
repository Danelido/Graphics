#include "Application.h"
#include "../Scenes/Tryouts.h"
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

Application::Application()
{
}

Application::~Application()
{
	delete this->p_inputManager;
	glfwTerminate();
}

bool Application::initialize(const char * appTitle, uint16_t appWidth, uint16_t appHeight)
{
	/*GLFW Procedure*/
	if (!glfwInit()) {
		printf("%s\n", "Failed to initialize GLFW");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	this->p_window = glfwCreateWindow(appWidth, appHeight, appTitle, NULL, NULL);
	
	
	if (!this->p_window) {
		glfwTerminate();
		printf("%s\n", "Failed to create GLFW-Window");
		return false;
	}

	/*GLFW-OPENGL Procedure*/
	glfwMakeContextCurrent(this->p_window);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		glfwTerminate();
		printf("%s%d\n", "Failed to initialize GLEW. Error code: ", err);
		return false;
	}

	/*Create input manager*/
	this->p_inputManager = new InputManager();

	/*Scene Creation*/
	this->p_scene = new Tryouts();
	glfwSwapInterval(1);
	glfwSetInputMode(this->p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return true;
}

void Application::run()
{
	while (!glfwWindowShouldClose(this->p_window)){
		/*Quick exit*/
		if (InputManager::isKeyReleased(GLFW_KEY_ESCAPE)) 
		{
			glfwSetWindowShouldClose(this->p_window, -1);
		}

		/*Input Procedure*/
		this->p_scene = this->p_scene->handleEvent();
		if (this->p_scene == nullptr) 
		{
			glfwSetWindowShouldClose(this->p_window, -1);
		}

		/*Update*/
		/* Get the delta time */
		this->p_currentFrame = glfwGetTime();
		this->p_deltaTime = this->p_currentFrame - this->p_lastFrame;

		this->calcFPS(1.f, "OpenGL Real-Time Rendering ");
		this->p_lastFrame = this->p_currentFrame;
		
		this->p_scene = this->p_scene->update(p_deltaTime);
		if (this->p_scene == nullptr) 
		{
			glfwSetWindowShouldClose(this->p_window, -1);
		}

		/*Render Procedure*/
		this->p_scene = this->p_scene->render();
		if (this->p_scene == nullptr) 
		{
			glfwSetWindowShouldClose(this->p_window, -1);
		}

		// Swap
		glfwSwapBuffers(this->p_window);
	
		/*Clear input manager and poll events*/
		this->p_inputManager->clean();
		glfwPollEvents();
	}

	if (this->p_scene != nullptr)
	{
		delete this->p_scene;
	}

}

/* COPIED FROM INTERNET */
double Application::calcFPS(double theTimeInterval, std::string theWindowTitle)
{
	// Static values which only get initialised the first time the function runs
	static double t0Value = glfwGetTime();	 // Set the initial time to now
	static int    fpsFrameCount = 0;					// Set the initial FPS frame count to 0
	static double fps = 0.0;								// Set the initial FPS value to 0.0

	 // Get the current time in seconds since the program started (non-static, so executed every time)
	double currentTime = glfwGetTime();

	// Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
	// Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
	if (theTimeInterval < 0.1)
	{
		theTimeInterval = 0.1;
	}
	if (theTimeInterval > 10.0)
	{
		theTimeInterval = 10.0;
	}

	// Calculate and display the FPS every specified time interval
	if ((currentTime - t0Value) > theTimeInterval)
	{
		// Calculate the FPS as the number of frames divided by the interval in seconds
		fps = (double)fpsFrameCount / (currentTime - t0Value);

		// If the user specified a window title to append the FPS value to...
		if (theWindowTitle != "NONE")
		{
			// Convert the fps value into a string using an output stringstream
			std::ostringstream stream;
			stream << fps;
			std::string fpsString = stream.str();

			// Append the FPS value to the window title details
			theWindowTitle += " | FPS: " + fpsString;

			// Convert the new window title to a c_str and set it
			const char* pszConstString = theWindowTitle.c_str();
			glfwSetWindowTitle(glfwGetCurrentContext(), pszConstString);
		}
		else // If the user didn't specify a window to append the FPS to then output the FPS to the console
		{
			std::cout << "FPS: " << fps << std::endl;
		}

		// Reset the FPS frame counter and set the initial time to be now
		fpsFrameCount = 0;
		t0Value = glfwGetTime();
	}
	else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
	{
		fpsFrameCount++;
	}

	// Return the current FPS - doesn't have to be used if you don't want it!
	return fps;
}