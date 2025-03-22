#include "default_entity.hpp"

DefaultEntity::DefaultEntity(const char* img_path){
	texture = Texture(GL_TEXTURE_2D, img_path);
}
