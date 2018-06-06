#pragma once

struct GLFWwindow;

class Display
{
private:
	static GLFWwindow* m_Window;
	static const char* m_Title;

	static unsigned int m_Width;
	static unsigned int m_Height;

	static double lastFrameTime;
	static float delta;

	static bool created;

public:
	static int PressedKey;
	static int HeldKey;
		
	static double ScrollOffsetX;
	static double ScrollOffsetY;
private:
	static double GetCurrentTime();
	static void SetUpCallbacks();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
	Display() {}
	~Display() {}

public:
	//Checks if the window has been closed
	static bool Closed();

	//Clears the screen
	static void Clear();

	//Returns calculated delta
	static inline float GetDelta() { return delta; }
	//Returns window width
	static inline unsigned int GetWidth() { return m_Width; }
	//Returns window height
	static inline unsigned int GetHeight() { return m_Height; }
	//Returns the context
	static inline GLFWwindow* GetContext() { return m_Window; }

	//Creates a new display a new one can't be created until the current one is destroyed
	static void CreateDisplay(unsigned int width, unsigned int height, const char* title, bool fullscreen = false);
	//Updates the display
	static void UpdateDisplay();
	//Destroys the display
	static 	void DestroyDisplay();

	//Sets mouse cursor position
	static void SetCursorPosition(double xpos, double ypos);
	//Gets mouse cursor position
	static 	void GetCursorPosition(double& xpos, double& ypos);
	//Centers mouse cursor on the screen
	static void CenterCursorPosition();

	//Toggles V-Sync
	static void SwitchVerticalSync(bool state);
};
