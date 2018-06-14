#pragma once
#include "InputKeys.h"

struct GLFWwindow;

class InputManager
{
public:
	class Keyboard
	{
	public:
		static bool IsKeyDown(Key key);
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

		static void SetCursorPosition(double xpos, double ypos);
		static void GetCursorPosition(double& xpos, double& ypos);
		static void CenterCursorPosition();

	private:
		friend class InputManager;
	};

public:
	static void SetCallBacks(GLFWwindow* context);

	static void Update();
private:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	static GLFWwindow* m_context;
};

