#include "default_entity.hpp"

DefaultEntity::DefaultEntity(glm::vec3 pos, const char* img_path): pos(pos){
	texture = Texture(GL_TEXTURE_2D, img_path);
}

DefaultEntity::DefaultEntity(){
}
