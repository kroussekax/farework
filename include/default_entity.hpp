#pragma once

#include "texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class DefaultEntity{
public:
	Texture texture;
	glm::vec3 pos;

	DefaultEntity(glm::vec3 pos, const char* img_path);
	DefaultEntity();
};
