#ifndef INPUTMANAGERH
#define INPUTMANAGERH
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <vector>


class InputManager {
public:
	static std::vector<int> p_keys_pressed;
	static std::vector<int> p_keys_heldDown;
	static std::vector<int> p_keys_released;

	static std::vector<int> p_mouse_pressed;
	static std::vector<int> p_mouse_heldDown;
	static std::vector<int> p_mouse_released;

	static glm::vec2 mousePosition;
	static bool window_focused;
	static bool contains(const std::vector<int>& vec, int key);
	static size_t getArrayLocationOfKey(const std::vector<int>& vec, int key);

public:

	InputManager(); // Needs to be called ONCE in the application
	virtual ~InputManager();

	static bool isKeyPressed(int key);
	static bool isKeyHeldDown(int key);
	static bool isKeyReleased(int key);

	static bool isMousePressed(int key);
	static bool isMouseHeldDown(int key);
	static bool isMouseReleased(int key);

	void clean();
	

};


#endif
