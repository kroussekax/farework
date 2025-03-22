#pragma once

#include <glad/glad.h>

class EBO{
private:
	unsigned int id;
public:
	void bind();
	void unbind();
	void Delete();

	EBO(unsigned int* indices, GLsizeiptr size);
	EBO();
};
