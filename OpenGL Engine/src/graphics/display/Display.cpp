#include "Display.h"
#include "..\..\Engine.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "..\FrameworkAssert.h"

#include <iostream>

#include <sstream>
#include <ctime>

#include "..\..\input\InputManager.h"


static const unsigned int SystemTimerResolution = 1000;

//Definitions
GLFWwindow* Display::m_Window = nullptr;
const char* Display::m_Title = nullptr;

unsigned int Display::m_Width = 100;
unsigned int Display::m_Height = 100;

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

void Display::createDisplay(unsigned int width, unsigned int height, const char* title, bool fullscreen)
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
			InputManager::setCallBacks(m_Window);

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
			lastFrameTime = getCurrentTime();

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