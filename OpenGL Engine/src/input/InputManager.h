#pragma once
#include "InputKeys.h"

struct GLFWwindow;

class InputManager
{
public:
	class Keyboard
	{
	public:
		static bool isKeyDown(Key key);
	private:
		static int m_pressedKey;
		static int m_heldKey;

		friend class InputManager;
	};
	class Mouse
	{
	public:
		static double ScrollOffsetX;
		static double ScrollOffsetY;

		static void setCursorPosition(double xpos, double ypos);
		static void getCursorPosition(double& xpos, double& ypos);
		static void centerCursorPosition();

	private:
		friend class InputManager;
	};

public:
	static void setCallBacks(GLFWwindow* context);

	static void update();
private:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	static GLFWwindow* m_context;
};

