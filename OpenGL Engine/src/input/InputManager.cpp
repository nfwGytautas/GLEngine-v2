#include "InputManager.h"
#include <iostream>
#include <GLFW\glfw3.h>
#include "..\graphics\display\Display.h"
#include "..\graphics\FrameworkAssert.h"
#include "..\Engine.h"

bool InputManager::Keyboard::m_pressedKeys[349] = { false };
double InputManager::Mouse::ScrollOffsetX = 0;
double InputManager::Mouse::ScrollOffsetY = 0;
GLFWwindow* InputManager::m_context = nullptr;

bool InputManager::Keyboard::isKeyDown(Key key)
{
	return m_pressedKeys[(int)key];
}

void InputManager::setCallBacks(GLFWwindow* context)
{
	m_context = context;
	GLCall(glfwSetKeyCallback(m_context, keyCallback));
	GLCall(glfwSetScrollCallback(m_context, scrollCallback));
}
void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	try
	{
		if (action == GLFW_PRESS)
		{
			Keyboard::m_pressedKeys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Keyboard::m_pressedKeys[key] = false;
		}
	}
	catch (...)
	{
		std::cout << "[Engine][InputManager] Exception caught." << "KeyCallback(unknown)" << "\n";
		return;
	}
}
void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	try
	{
		Mouse::ScrollOffsetX = xoffset;
		Mouse::ScrollOffsetY = yoffset;
	}
	catch (...)
	{
		std::cout << "[Engine][InputManager] Exception caught." << "ScrollCallback(unknown)" << "\n";
		return;
	}
}
std::vector<Key> InputManager::getKey()
{
	std::vector<Key> result;
	for (unsigned int i = 0; i < 349; i++)
	{
		if (Keyboard::m_pressedKeys[i] == true)
		{
			result.push_back((Key)i);
		}
	}
	return result;
}
void InputManager::update()
{
	GLCall(glfwPollEvents());
}

void InputManager::Mouse::setCursorPosition(double xpos, double ypos)
{
	GLCall(glfwSetCursorPos(m_context, xpos, ypos));
}
void InputManager::Mouse::getCursorPosition(double & xpos, double & ypos)
{
	GLCall(glfwGetCursorPos(m_context, &xpos, &ypos));
}
void InputManager::Mouse::centerCursorPosition()
{
	GLCall(glfwSetCursorPos(m_context, Display::getWidth() / 2, Display::getHeight() / 2));
}