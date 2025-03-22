#pragma once

#include <glad/glad.h>

#include "stb_image.h"

class Texture{
private:
	unsigned int id;
public:
	void bind();
	void unbind();
	void Delete();

	Texture(GLenum texture_type, const char* img_path);
	Texture();
};
