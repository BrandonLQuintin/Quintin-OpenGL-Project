#pragma once
#include "../shapes/shapes.h"
#include "../opengl/camera_variables.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void setShadowLocation(shape &shape, glm::vec3 targetPos, float groundY);
