#pragma once

struct GLFWwindow;

class Display
{
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

	//Toggles V-Sync
	static void SwitchVerticalSync(bool state);

private:
	static GLFWwindow* m_Window;
	static const char* m_Title;

	static unsigned int m_Width;
	static unsigned int m_Height;

	static double lastFrameTime;
	static float delta;

	static bool created;
private:
	static double GetCurrentTime();
private:
	Display() {}
	~Display() {}
};
