#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

class Camera{
private:
	glm::vec3 camera_pos;
	glm::vec3* camera_target;

	GLuint viewLoc;
	glm::mat4 camera_view;
public:
	void update_GLUniform();
	void update_cam_target();

	Camera(Shader& shader, glm::vec3& target);
	Camera();
};
