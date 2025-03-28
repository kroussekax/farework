#include "VBO.hpp"

void VBO::bind(){
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete(){
	glDeleteBuffers(1, &id);
}

VBO::VBO(float* vertices, GLsizeiptr size){
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::VBO(){
}
