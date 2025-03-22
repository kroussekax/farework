#include <iostream>
#include <string>
#include <format>
#include <map>
#include <cstdio>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window, float dt);

float getDeltaTime(float& lastTime);

std::map<std::string, glm::vec3> positions;
glm::mat4 projection;

int main(){
	Engine engine = Engine("Vyyxka", 800, 800);
	engine.run();

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
	std::cout<<"Window Resized: "<<width<<", "<<height<<std::endl;
}

void process_input(GLFWwindow* window, float dt){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);

	float camera_speed = 2.5f * dt;

	if(glfwGetKey(window, GLFW_KEY_W))
		positions["joe"].y += camera_speed;
	if(glfwGetKey(window, GLFW_KEY_A))
		positions["joe"].x -= camera_speed;
	if(glfwGetKey(window, GLFW_KEY_S))
		positions["joe"].y -= camera_speed;
	if(glfwGetKey(window, GLFW_KEY_D))
		positions["joe"].x += camera_speed;

}

float getDeltaTime(float& lastTime) {
	// Get current time
	float currentTime = static_cast<float>(glfwGetTime());

	// Calculate delta time
	float deltaTime = currentTime - lastTime;

	// Update last time to current time
	lastTime = currentTime;

	return deltaTime;
}
