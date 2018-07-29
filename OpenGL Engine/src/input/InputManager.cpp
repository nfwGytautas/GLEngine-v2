#include "InputManager.h"
#include <iostream>
#include <GLFW\glfw3.h>
#include "..\graphics\display\Display.h"
#include "..\graphics\FrameworkAssert.h"
#include "..\Engine.h"

bool InputManager::Keyboard::m_pressedKeys[349] = { false };
bool InputManager::Mouse::m_pressedKeys[12] = { false };
double InputManager::Mouse::m_scrollOffsetX = 0;
double InputManager::Mouse::m_scrollOffsetY = 0;
double InputManager::Mouse::m_lastX = 0;
double InputManager::Mouse::m_lastY = 0;
float InputManager::Mouse::m_xoffset = 0;
float InputManager::Mouse::m_yoffset = 0;
double InputManager::Mouse::m_scrollChangeY = 0;
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
	GLCall(glfwSetMouseButtonCallback(m_context, mouseClickCallback));
	GLCall(glfwSetCursorPosCallback(m_context, mouseMoveCallback));
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
		Mouse::m_scrollOffsetX = xoffset;
		Mouse::m_scrollOffsetY = yoffset;
	}
	catch (...)
	{
		std::cout << "[Engine][InputManager] Exception caught." << "ScrollCallback(unknown)" << "\n";
		return;
	}
}
void InputManager::mouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	try
	{
		if (action == GLFW_PRESS)
		{
			Mouse::m_pressedKeys[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Mouse::m_pressedKeys[button] = false;
		}
	}
	catch (...)
	{
		std::cout << "[Engine][InputManager] Exception caught." << "MouseClickCallback(unknown)" << "\n";
		return;
	}
}
void InputManager::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	try
	{
		Mouse::m_xoffset = (float) (xpos - Mouse::m_lastX);
		Mouse::m_yoffset = (float) (ypos - Mouse::m_lastY);
		Mouse::m_lastX = xpos;
		Mouse::m_lastY = ypos;
	}
	catch (...)
	{
		std::cout << "[Engine][InputManager] Exception caught." << "MouseMoveCallback(unknown)" << "\n";
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

bool InputManager::Mouse::isMouseKeyDown(MouseKey key)
{
	return m_pressedKeys[(int)key];
}

float InputManager::Mouse::getScrollAmountY()
{
	m_scrollChangeY = m_scrollOffsetY;
	m_scrollOffsetY = 0;
	return (float) m_scrollChangeY;
}

float InputManager::Mouse::getXOffset()
{
	return m_xoffset;
}
float InputManager::Mouse::getYOffset()
{
	return m_yoffset;
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