#include "texture.hpp"

void Texture::bind(){
	glBindTexture(1, id);
}

void Texture::unbind(){
	glBindTexture(1, 0);
}

void Texture::Delete(){
	glDeleteTextures(1, &id);
}

Texture::Texture(GLenum texture_type, const char* img_path){
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(texture_type, id);

	glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int width, height, num_col;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(img_path, &width, &height, &num_col, 0);

	glTexImage2D(texture_type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(texture_type);

	stbi_image_free(bytes);
}
