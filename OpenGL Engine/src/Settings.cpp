#include "Settings.h"

unsigned int Settings::width = 1280;
unsigned int Settings::height = 720;
const char* Settings::title = "Test window";
bool Settings::fullscreen = false;

glm::vec3 Settings::skyColor = glm::vec3(0.529f, 0.807f, 0.980f);
float Settings::gravity = -50;
CCamera* Settings::camera = nullptr;
float Settings::cameraSensetivity = 0.05f;
std::vector<float> Settings::guiQuad = std::vector<float>{ -1, 1, -1, -1, 1, 1, 1, -1 };

float Settings::FoV = 70;
float Settings::nearRenderPlane = 0.1f;
float Settings::farRenderPlane = 1000.0f;