#pragma once

struct GLFWwindow;

class Display
{
public:
	//Checks if the window has been closed
	static bool closed();

	//Clears the screen
	static void clear();

	//Returns calculated delta
	static inline float getDelta() { return delta; }
	//Returns window width
	static inline unsigned int getWidth() { return m_Width; }
	//Returns window height
	static inline unsigned int getHeight() { return m_Height; }
	//Returns the context
	static inline GLFWwindow* getContext() { return m_Window; }

	//Creates a new display a new one can't be created until the current one is destroyed
	static void createDisplay(unsigned int width, unsigned int height, const char* title, bool fullscreen = false);
	//Updates the display
	static void updateDisplay();
	//Destroys the display
	static 	void destroyDisplay();

	//Toggles V-Sync
	static void switchVerticalSync(bool state);

private:
	static GLFWwindow* m_Window;
	static const char* m_Title;

	static unsigned int m_Width;
	static unsigned int m_Height;

	static double lastFrameTime;
	static float delta;

	static bool created;
private:
	static double getCurrentTime();
private:
	Display() {}
	~Display() {}
};
