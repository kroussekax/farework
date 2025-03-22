#pragma once

#include <glad/glad.h>

class VBO{
private:
	unsigned int id;
public:
	void bind();
	void unbind();
	void Delete();

	VBO(float* vertices, GLsizeiptr size);
	VBO();
};
