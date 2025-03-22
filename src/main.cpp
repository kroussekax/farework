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

#include "shader.hpp"

#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include "texture.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window, float dt);

float getDeltaTime(float& lastTime);

std::map<std::string, glm::vec3> positions;
glm::mat4 projection;

int main(){

	glfwInit();

	// *REMEMER THESE*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Vyyxka", NULL, NULL);
	if(window == NULL){ std::cout<< "Failed creating window. " <<std::endl; glfwTerminate(); return -1; }

	// *MAKE USE OF VARIABLE "window"*
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	float vertices[] = {
		// positions         // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // top left
	};

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glEnable(GL_DEPTH_TEST);
	Shader shader("res/shaders/vertexshaders.glsl", "res/shaders/fragmentshaders.glsl");

	VAO VAO1;
	VAO1.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// unbind all to prevent accidentally modifying them
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	bool updateCam = true;

	projection = glm::perspective(glm::radians(110.0f), 800.0f / 800.0f, 0.1f, 100.0f);

	Texture mcdirt(GL_TEXTURE_2D, "res/img/cool.png");

	// applying mattrices
	unsigned int modelLoc = glGetUniformLocation(shader.get_id(), "model");

	//
	unsigned int viewLoc = glGetUniformLocation(shader.get_id(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	unsigned int projectionLoc = glGetUniformLocation(shader.get_id(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	positions = {
		{"joe", glm::vec3(0.0f, 0.0f, 0.0f)},
		{"enemy1", glm::vec3(1.0f, -2.0f, 0.0f)},
		{"enemy2", glm::vec3(-2.0f, -2.0f, 0.0f)},
	};

	float last_time = 0.0f;
	float delta = 0.0f;

	int frameCount = 0;

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

		cameraTarget = positions["joe"];
		if(cameraTarget != cameraPos){
			cameraTarget = positions["joe"];

			// Use distance check to avoid precision issues
			if (glm::distance(cameraPos, cameraTarget) > 0.001f){
				float lerpFactor = 0.1f; // Adjust for smoothness
				cameraPos = glm::mix(cameraPos, cameraTarget, lerpFactor);
			}

			// Corrected view matrix calculation
			view = glm::lookAt(
				glm::vec3(cameraPos.x, cameraPos.y, 3.0f), // Camera position
				glm::vec3(cameraPos.x, cameraPos.y, 0.0f), // Look at target
				glm::vec3(0.0f, 1.0f, 0.0f) // Up direction
			);

			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		}

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

		ImGui::Begin("Camera Stuff");
		{
			ImGui::Text("%s", std::format("camera X: {}", cameraPos.x).c_str());
			ImGui::Text("%s", std::format("camera Y: {}", cameraPos.y).c_str());
			ImGui::Text("%s", std::format("camera Z: {}", cameraPos.z).c_str());
		}
		ImGui::End();

		ImGui::Begin("View Matrx");
		{
			auto viewPos = glm::vec3(view[3]);
			ImGui::Text("%s", std::format("View X: {}", viewPos.x).c_str());
			ImGui::Text("%s", std::format("View Y: {}", viewPos.y).c_str());
			ImGui::Text("%s", std::format("View Z: {}", viewPos.z).c_str());
		}
		ImGui::End();

		ImGui::Begin("App Info");
		{
			float fps = 1.0f / delta;
			ImGui::Text("%s", std::format("FPS: {}", fps).c_str());
		}
		ImGui::End();

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
