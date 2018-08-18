#pragma once
#include <vector>
#include "InputKeys.h"

struct GLFWwindow;
class UpdateSystem;

class InputManager
{
public:
	class Keyboard
	{
	public:
		static bool isKeyDown(Key key);
	private:
		static bool m_pressedKeys[349];
		static std::vector<Key> m_keyUp;
		friend class InputManager;
	};
	class Mouse
	{
	public:
		static bool isMouseKeyDown(MouseKey key);
		static float getScrollAmountY();
		static float getScrollAmountX();
		static float getXOffset();
		static float getYOffset();

		static void setCursorPosition(double xpos, double ypos);
		static void getCursorPosition(double& xpos, double& ypos);
		static void centerCursorPosition();

	private:
		static double m_scrollOffsetX;
		static double m_scrollOffsetY;
		static double m_scrollChangeY;
		static double m_scrollChangeX;

		static double m_moveAmount;
		static double m_lastX;
		static double m_lastY;
		static float m_xoffset;
		static float m_yoffset;

		static bool m_pressedKeys[12];
		static std::vector<MouseKey> m_keyUp;

		static bool m_moved;
		static bool m_scrolled;

		friend class InputManager;
	};

public:
	static void setCallBacks(GLFWwindow* context);

	static void update();
private:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);

	static GLFWwindow* m_context;

	static std::vector<Key> getKeyDown();
	static std::vector<Key>& getKeyUp();
	static std::vector<MouseKey> getMKeyDown();
	static std::vector<MouseKey>& getMKeyUp();

	friend UpdateSystem;
};