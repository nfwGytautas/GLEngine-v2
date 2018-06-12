#include "Display.h"
#include "..\..\Engine.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include <sstream>
#include <ctime>

#include "..\FrameworkAssert.h"

static const unsigned int SystemTimerResolution = 1000;

//Definitions
GLFWwindow* Display::m_Window = nullptr;
const char* Display::m_Title = nullptr;

unsigned int Display::m_Width = 100;
unsigned int Display::m_Height = 100;

double Display::lastFrameTime = 0.0;
float Display::delta = 0.0f;

bool Display::created = false;

int Display::PressedKey = -1;
int Display::HeldKey = -1;

double Display::ScrollOffsetX = 0;
double Display::ScrollOffsetY = 0;

bool Display::Closed()
{
	return glfwWindowShouldClose(m_Window);
}

void Display::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Display::CreateDisplay(unsigned int width, unsigned int height, const char* title, bool fullscreen)
{
	if(!created)
	{
		try
		{
			//Sets private variables
			m_Width = width;
			m_Height = height;
			m_Title = title;

			//Initializes glfw
			if (!glfwInit())
			{			
				GLCall(glfwTerminate());			
				throw "Failed initializing glfw3";					
			}

			//Creates a window
			if (!fullscreen) m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			else m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, glfwGetPrimaryMonitor(), NULL);

			//Checks if a window is created successfully
			if (!m_Window)
			{
				throw "Failed to create window!";
			}

			//Makes the window context current obviously
			glfwMakeContextCurrent(m_Window);				

			//Callbacks
			SetUpCallbacks();

			//Check for glew initialization status
			if (glewInit() != GLEW_OK)
			{
				throw "Could not initialize GLEW!";
			}

			//Print version
			std::cout << "[Engine][Display] OpenGL version: " << glGetString(GL_VERSION) << std::endl;

			//Set the viewport
			GLCall(glViewport(0, 0, m_Width, m_Height));

			//Get variable for FPS counting
			lastFrameTime = GetCurrentTime();

			//Finaly set that the window is created
			created = true;

			std::cout << "[Engine][Display] Created successfully. \n";
			return;
		}
		catch (const char* exception)
		{
			std::cout << "[Engine][Display] Exception caught: " << exception << " Arguments: (" << width << "; " << height << "; " << title << "; " << fullscreen << ")" << "\n";
			return;
		}
	}
}

void Display::UpdateDisplay()
{
	if (created)
	{
		//Check errors
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "[Engine][Display] OpenGL error: " << error << "\n";
		}

		PressedKey = -1;

		//Poll events
		GLCall(glfwPollEvents());

		//Swap buffers
		GLCall(glfwSwapBuffers(m_Window));

		//Calculate FPS
		double currentFrameTime = GetCurrentTime();
		delta = float(currentFrameTime - lastFrameTime);
		lastFrameTime = currentFrameTime;		
	}
}
void Display::DestroyDisplay()
{
	//Destroy current display
	glfwDestroyWindow(m_Window);
	glfwTerminate();
	created = false;
}

void Display::SetCursorPosition(double xpos, double ypos)
{
	if (created)
	{
		GLCall(glfwSetCursorPos(m_Window, xpos, ypos));
	}
}
void Display::GetCursorPosition(double & xpos, double & ypos)
{
	if (created)
	{
		GLCall(glfwGetCursorPos(m_Window, &xpos, &ypos));
	}
}
void Display::CenterCursorPosition()
{
	if (created)
	{
		GLCall(glfwSetCursorPos(m_Window, m_Width/2, m_Height/2));
	}
}

void Display::SwitchVerticalSync(bool state)
{
	if (state = true) GLCall(glfwSwapInterval(1));
	else GLCall(glfwSwapInterval(0));
}

double Display::GetCurrentTime()
{
	//Get time in miliseconds
	return glfwGetTime();
}

void Display::SetUpCallbacks()
{
	//Callbacks go here
	GLCall(glfwSetKeyCallback(m_Window, KeyCallback));
	GLCall(glfwSetScrollCallback(m_Window, ScrollCallback));
}
void Display::KeyCallback(GLFWwindow * win, int key, int scancode, int action, int mods)
{
	try
	{
		if (action == GLFW_PRESS)
		{
			Display::PressedKey = key;
			Display::HeldKey = key;
		}
		else if (action == GLFW_RELEASE)
		{
			Display::HeldKey = -1;
		}
	}
	catch(...)
	{
		std::cout << "[Engine][Display] Exception caught." << "KeyCallback(unknown)" << "\n";
		return;
	}
}
void Display::ScrollCallback(GLFWwindow * win, double xoffset, double yoffset)
{
	try
	{
		Display::ScrollOffsetX = xoffset;
		Display::ScrollOffsetY = yoffset;
	}
	catch (...)
	{
		std::cout << "[Engine][Display] Exception caught." << "ScrollCallback(unknown)" << "\n";
		return;
	}
}