#include "Settings.h"

glm::vec3 Settings::skyColor = glm::vec3(0.529f, 0.807f, 0.980f);
float Settings::gravity = -50;
CCamera* Settings::camera = nullptr;
float Settings::cameraSensetivity = 0.05f;