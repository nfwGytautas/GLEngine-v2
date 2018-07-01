#include "InputManager.h"
#include "..\graphics\display\Display.h"

#include "..\graphics\FrameworkAssert.h"
#include <GLFW\glfw3.h>

#include <iostream>

bool InputManager::Keyboard::isKeyDown(Key key)
{
	int keyCode = (int)key;
	if (keyCode == m_pressedKey || keyCode == m_heldKey)
	{
		return true;
	}
	else
	{
		return false;
	}
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
			Keyboard::m_pressedKey = key;
			Keyboard::m_heldKey = key;
		}
		else if (action == GLFW_RELEASE)
		{
			Keyboard::m_heldKey = -1;
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
void InputManager::update()
{
	Keyboard::m_pressedKey = -1;
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

int InputManager::Keyboard::m_pressedKey = -1;
int InputManager::Keyboard::m_heldKey = -1;

double InputManager::Mouse::ScrollOffsetX = 0;
double InputManager::Mouse::ScrollOffsetY = 0;

GLFWwindow* InputManager::m_context = nullptr;


