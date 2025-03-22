#pragma once

#include <glad/glad.h>

#include "VBO.hpp"

class VAO{
private:
	unsigned int id;
public:
	void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void bind();
	void unbind();
	void Delete();

	VAO();
};
