#include "InputManager.h"

#define MAX_KEYS_AT_ONCE 16
#define MAX_MOUSE_AT_ONCE 4

/* STATIC INITIALIZATION */
std::vector<int>	InputManager::p_keys_pressed(MAX_KEYS_AT_ONCE);
std::vector<int>	InputManager::p_keys_heldDown(MAX_KEYS_AT_ONCE);
std::vector<int>	InputManager::p_keys_released(MAX_KEYS_AT_ONCE);
std::vector<int>	InputManager::p_mouse_pressed(MAX_MOUSE_AT_ONCE);
std::vector<int>	InputManager::p_mouse_heldDown(MAX_MOUSE_AT_ONCE);
std::vector<int>	InputManager::p_mouse_released(MAX_MOUSE_AT_ONCE);

bool InputManager::window_focused = true;
glm::vec2 InputManager::mousePosition = glm::vec2(0.0f, 0.0f);

/* CALLBACKS DEC*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void window_focus_callback(GLFWwindow* window, int focused);

InputManager::InputManager()
{
	glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
	glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);
	glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_position_callback);
	glfwSetWindowFocusCallback(glfwGetCurrentContext(), window_focus_callback);
}

InputManager::~InputManager() 
{
	/*Empty*/
}


/* CALLBACKS DEF*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (!InputManager::contains(InputManager::p_keys_pressed,key) && !InputManager::contains(InputManager::p_keys_heldDown, key))
		{
			InputManager::p_keys_pressed.push_back(key);
			InputManager::p_keys_heldDown.push_back(key);
		}
	}
	else if (action == GLFW_REPEAT)
	{
		if (!InputManager::contains(InputManager::p_keys_heldDown, key))
		{
			InputManager::p_keys_heldDown.push_back(key);
		}
	}
	else if (action == GLFW_RELEASE)
	{
		size_t location = InputManager::getArrayLocationOfKey(InputManager::p_keys_heldDown, key);

		if (location != -1) {
			InputManager::p_keys_heldDown.erase(
				InputManager::p_keys_heldDown.begin() + location);
		}

		if (!InputManager::contains(InputManager::p_keys_released, key))
		{
			InputManager::p_keys_released.push_back(key);
		}
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (!InputManager::contains(InputManager::p_mouse_pressed,button) && !InputManager::contains(InputManager::p_mouse_heldDown, button))
		{
			InputManager::p_mouse_pressed.push_back(button);
		}
	}
	else if (action == GLFW_REPEAT)
	{
		if (!InputManager::contains(InputManager::p_mouse_heldDown, button))
		{
			InputManager::p_mouse_heldDown.push_back(button);
		}
	}
	else if (action == GLFW_RELEASE)
	{
		size_t  location = InputManager::getArrayLocationOfKey(InputManager::p_mouse_heldDown, button);
		
		if (location != -1) {
			InputManager::p_mouse_heldDown.erase(
				InputManager::p_mouse_heldDown.begin() + location);
		}

		if (!InputManager::contains(InputManager::p_mouse_released, button))
		{
			InputManager::p_mouse_released.push_back(button);
		}
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager::mousePosition.x = static_cast<float>(xpos);
	InputManager::mousePosition.y = static_cast<float>(ypos);
}

void window_focus_callback(GLFWwindow* window, int focused)
{
	InputManager::window_focused = focused;
}

/* HELPER FUNC */
bool InputManager::contains(const std::vector<int>& vec, int key)
{
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec.at(i) == key)
			return true;
	}
	return false;
}

size_t InputManager::getArrayLocationOfKey(const std::vector<int>& vec, int key)
{
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec.at(i) == key)
			return i;
	}
	return -1;
}

/* GETTETS */
bool InputManager::isKeyPressed(int key)
{
	return InputManager::contains(InputManager::p_keys_pressed, key);
}

bool InputManager::isKeyHeldDown(int key)
{
	return InputManager::contains(InputManager::p_keys_heldDown, key);
}

bool InputManager::isKeyReleased(int key)
{

	size_t  location = InputManager::getArrayLocationOfKey(InputManager::p_keys_released, key);

	if (location != -1) {
		InputManager::p_keys_released.erase(
			InputManager::p_keys_released.begin() + location);

		return true;
	}

	return false;
}

bool InputManager::isMousePressed(int key)
{
	return InputManager::contains(InputManager::p_mouse_pressed, key);
}

bool InputManager::isMouseHeldDown(int key)
{
	return InputManager::contains(InputManager::p_mouse_heldDown, key);
}

bool InputManager::isMouseReleased(int key)
{

	size_t  location = InputManager::getArrayLocationOfKey(InputManager::p_mouse_released, key);

	if (location != -1) {
		InputManager::p_mouse_released.erase(
			InputManager::p_mouse_released.begin() + location);

		return true;
	}

	return false;
}

void InputManager::clean()
{
	InputManager::p_keys_pressed.clear();
	InputManager::p_keys_released.clear();
	InputManager::p_mouse_pressed.clear();
	InputManager::p_mouse_released.clear();
}