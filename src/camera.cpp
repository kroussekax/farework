#include "camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/ext/quaternion_common.hpp>
#include "glm/geometric.hpp"

Camera::Camera(Shader& shader, glm::vec3& target){
	camera_view = glm::mat4(1.0f);
	camera_view = glm::translate(camera_view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::vec4 column = camera_view[3]; // Extract the 4th column (index 3) - Often the translation part
	camera_pos = glm::vec3(camera_view[3]); // Convert to vec3 (ignores w)

	camera_target = &target;

	viewLoc = glGetUniformLocation(shader.get_id(), "camera_view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_view));
}

void Camera::update_GLUniform(){
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_view));
}

void Camera::update_cam_target(){
	if(camera_pos != *camera_target){
		camera_pos = *camera_target;

		// Use distance check to avoid precision issues
		if (glm::distance(camera_pos, *camera_target) > 0.001f){
			float lerpFactor = 0.1f; // Adjust for smoothness
			camera_pos = glm::mix(camera_pos, *camera_target, lerpFactor);
		}

		// Corrected camera_view matrix calculation
		camera_view = glm::lookAt(
			glm::vec3(camera_pos.x, camera_pos.y, 3.0f), // Camera position
			glm::vec3(camera_pos.x, camera_pos.y, 0.0f), // Look at target
			glm::vec3(0.0f, 1.0f, 0.0f) // Up direction
		);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_view));
	}
}

Camera::Camera(){
}
