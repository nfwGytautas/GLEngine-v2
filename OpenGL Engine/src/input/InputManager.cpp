#include "InputManager.h"
#include "..\graphics\display\Display.h"

#include "..\graphics\FrameworkAssert.h"
#include <GLFW\glfw3.h>

#include <iostream>

bool InputManager::Keyboard::IsKeyDown(Key key)
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

void InputManager::SetCallBacks(GLFWwindow* context)
{
	m_context = context;
	GLCall(glfwSetKeyCallback(m_context, KeyCallback));
	GLCall(glfwSetScrollCallback(m_context, ScrollCallback));
}
void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
void InputManager::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
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
void InputManager::Update()
{
	Keyboard::m_pressedKey = -1;
	GLCall(glfwPollEvents());
}

void InputManager::Mouse::SetCursorPosition(double xpos, double ypos)
{
	GLCall(glfwSetCursorPos(m_context, xpos, ypos));
}
void InputManager::Mouse::GetCursorPosition(double & xpos, double & ypos)
{
	GLCall(glfwGetCursorPos(m_context, &xpos, &ypos));
}
void InputManager::Mouse::CenterCursorPosition()
{
	GLCall(glfwSetCursorPos(m_context, Display::GetWidth() / 2, Display::GetHeight() / 2));
}

int InputManager::Keyboard::m_pressedKey = -1;
int InputManager::Keyboard::m_heldKey = -1;

double InputManager::Mouse::ScrollOffsetX = 0;
double InputManager::Mouse::ScrollOffsetY = 0;

GLFWwindow* InputManager::m_context = nullptr;


