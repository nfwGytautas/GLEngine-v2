#include "InputManager.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\..\graphics\display\Display.h"
#include "..\..\graphics\GraphicsAssert.h"
#include "..\..\Settings.h"

bool InputManager::Keyboard::m_pressedKeys[349] = { false };
bool InputManager::Mouse::m_pressedKeys[12] = { false };
double InputManager::Mouse::m_scrollOffsetX = 0;
double InputManager::Mouse::m_scrollOffsetY = 0;
double InputManager::Mouse::m_lastX = 0;
double InputManager::Mouse::m_lastY = 0;
float InputManager::Mouse::m_xoffset = 0;
float InputManager::Mouse::m_yoffset = 0;
double InputManager::Mouse::m_scrollChangeY = 0;
double InputManager::Mouse::m_scrollChangeX = 0;
std::vector<Key> InputManager::Keyboard::m_keyUp;
std::vector<MouseKey> InputManager::Mouse::m_keyUp;
bool InputManager::Mouse::m_moved = false;
bool InputManager::Mouse::m_scrolled = false;
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
		if (key < 0 || key >= 349)
		{
			return;
		}
		if (action == GLFW_PRESS)
		{
			Keyboard::m_pressedKeys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Keyboard::m_pressedKeys[key] = false;
			Keyboard::m_keyUp.push_back((Key)key);
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
			Mouse::m_keyUp.push_back((MouseKey)button);
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
std::vector<Key> InputManager::getKeyDown()
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
std::vector<Key>& InputManager::getKeyUp()
{
	return Keyboard::m_keyUp;
}
std::vector<MouseKey> InputManager::getMKeyDown()
{
	std::vector<MouseKey> result;
	for (unsigned int i = 0; i < 12; i++)
	{
		if (Mouse::m_pressedKeys[i] == true)
		{
			result.push_back((MouseKey)i);
		}
	}
	return result;
}
std::vector<MouseKey>& InputManager::getMKeyUp()
{
	return Mouse::m_keyUp;
}
void InputManager::update()
{
	Keyboard::m_keyUp.clear();
	Mouse::m_keyUp.clear();
	Mouse::m_xoffset = 0;
	Mouse::m_yoffset = 0;
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

float InputManager::Mouse::getScrollAmountX()
{
	m_scrollChangeX = m_scrollOffsetX;
	m_scrollOffsetX = 0;
	return (float)m_scrollChangeX;
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
	GLCall(glfwSetCursorPos(m_context, Settings::width / 2, Settings::height / 2));
}