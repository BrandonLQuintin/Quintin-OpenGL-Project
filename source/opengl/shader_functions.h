#pragma once

#include <shader_m.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

void useShader(Shader &shader, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec3 cameraPosition);
