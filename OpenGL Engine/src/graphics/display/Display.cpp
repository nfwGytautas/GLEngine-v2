#include "Display.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\GraphicsAssert.h"
#include "..\..\data manager\input\InputManager.h"
#include "..\..\utility\Time.h"
#include "..\..\Settings.h"

//Definitions
GLFWwindow* Display::m_Window = nullptr;

double Display::lastFrameTime = 0.0;
float Display::delta = 0.0f;

bool Display::created = false;

bool Display::closed()
{
	return glfwWindowShouldClose(m_Window);
}
void Display::clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

bool Display::createDisplay()
{
	if(!created)
	{		
		//Creates a window
		if (!Settings::fullscreen) m_Window = glfwCreateWindow(Settings::width, Settings::height, Settings::title, NULL, NULL);
		else m_Window = glfwCreateWindow(Settings::width, Settings::height, Settings::title, glfwGetPrimaryMonitor(), NULL);

		//Checks if a window is created successfully
		if (!m_Window)
		{
			return false;
		}

		//Makes the window context current
		glfwMakeContextCurrent(m_Window);				

		//Callbacks
		InputManager::setCallBacks(m_Window);				

		//Set the viewport
		GLCall(glViewport(0, 0, Settings::width, Settings::height));

		//Get variable for FPS counting
		lastFrameTime = getCurrentTime();

		//Finaly set that the window is created
		created = true;

		return true;
	}
	return false;
}
void Display::updateDisplay()
{
	if (created)
	{
		//Check errors
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "[Engine][Display] OpenGL error: " << error << "\n";
		}		

		//Swap buffers
		GLCall(glfwSwapBuffers(m_Window));

		//Calculate delta
		double currentFrameTime = getCurrentTime();
		delta = float((currentFrameTime - lastFrameTime) / 1000);
		Time::deltaTime = delta;
		lastFrameTime = currentFrameTime;		
	}
}
void Display::destroyDisplay()
{
	//Destroy current display
	glfwDestroyWindow(m_Window);
	glfwTerminate();
	created = false;
}

void Display::switchVerticalSync(bool state)
{
	if (state = true) GLCall(glfwSwapInterval(1));
	else GLCall(glfwSwapInterval(0));
}

double Display::getCurrentTime()
{
	//Get time in seconds
	return glfwGetTime() * 1000;
}