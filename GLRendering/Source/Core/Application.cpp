#include "Application.h"
#include "../Scenes/Tryouts.h"
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include "Graphics/Resource/Resources.h"
#include "Graphics/Setup/MeshLoaderSingleton.h"
#include "Vendor/ImGui/imgui.h"
#include "Vendor/ImGui/imgui_impl_glfw.h"
#include "Vendor/ImGui/imgui_impl_opengl3.h"
Application::Application()
{
}

Application::~Application()
{
	delete this->p_inputManager;
	Resources::clearResources();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

bool Application::initialize(const char * appTitle, uint16_t appWidth, uint16_t appHeight)
{
	/*GLFW Procedure*/
	if (!glfwInit()) {
		printf("%s\n", "Failed to initialize GLFW");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

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

	/*Initialize Resource & MeshLoader class ( Singletons )*/
	Resources::Resources();
	MeshLoaderSingleton::Loader; 

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls


	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(p_window, true);
	ImGui_ImplOpenGL3_Init("#version 410 core");
	// Setup Style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsLight();
	//ImGui::StyleColorsClassic();

	/*Scene Creation*/
	this->p_scene = new Tryouts();
	
	// Vsync enabled
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
		this->p_lastFrame = this->p_currentFrame;
		
		this->p_scene = this->p_scene->update(static_cast<float>(p_deltaTime));
		if (this->p_scene == nullptr) 
		{
			glfwSetWindowShouldClose(this->p_window, -1);
		}


		/*Render Procedure*/
		//ImGUI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		this->p_scene = this->p_scene->renderImGui();
		ImGui::Render();
	
		if (this->p_scene == nullptr)
		{
			glfwSetWindowShouldClose(this->p_window, -1);
		}

		this->p_scene = this->p_scene->render();
		if (this->p_scene == nullptr) 
		{
			glfwSetWindowShouldClose(this->p_window, -1);
		}
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
