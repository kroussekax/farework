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

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "stb_image.h"
#include "texture.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window, float dt);

float getDeltaTime(float& lastTime);

std::map<std::string, glm::vec3> positions;
glm::mat4 projection;

int main(){
	projection = glm::perspective(glm::radians(110.0f), 800.0f / 800.0f, 0.1f, 100.0f);

	Texture mcdirt(GL_TEXTURE_2D, "res/img/cool.png");

	// applying mattrices
	unsigned int modelLoc = glGetUniformLocation(shader.get_id(), "model");

	unsigned int projectionLoc = glGetUniformLocation(shader.get_id(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	positions = {
		{"joe", glm::vec3(0.0f, 0.0f, 0.0f)},
		{"enemy1", glm::vec3(1.0f, -2.0f, 0.0f)},
		{"enemy2", glm::vec3(-2.0f, -2.0f, 0.0f)},
	};

	float last_time = 0.0f;
	float delta = 0.0f;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& guiIO = ImGui::GetIO(); (void)guiIO;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	while(!glfwWindowShouldClose(window)){
		delta = getDeltaTime(last_time);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Input
		if(!guiIO.WantCaptureMouse)
			process_input(window, delta);

		shader.use();
		mcdirt.bind();
		VAO1.bind();
		for(auto &e : positions){
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, e.second);

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		//glDrawArrays(GL_TRIANGLES, 0, 36);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	VAO1.Delete();
	VBO1.Delete();

	glfwDestroyWindow(window);
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
