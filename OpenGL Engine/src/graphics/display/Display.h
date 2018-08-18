#pragma once

struct GLFWwindow;

class Display
{
public:
	//Checks if the window has been closed
	static bool closed();

	//Clears the screen
	static void clear();

	//Returns calculated delta in miliseconds
	static inline float getDelta() { return delta; }
	//Returns the context
	static inline GLFWwindow* getContext() { return m_Window; }

	//Creates a new display a new one can't be created until the current one is destroyed
	static bool createDisplay();
	//Updates the display
	static void updateDisplay();
	//Destroys the display
	static 	void destroyDisplay();

	//Toggles V-Sync
	static void switchVerticalSync(bool state);

private:
	static GLFWwindow* m_Window;

	static double lastFrameTime;
	static float delta;

	static bool created;
private:
	static double getCurrentTime();
private:
	Display() {}
	~Display() {}
};
