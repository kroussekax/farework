#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

#include "shader.hpp"
#include "camera.hpp"
#include "default_entity.hpp"

class Engine{
private:
	GLFWwindow* window;

	struct{
		float *vertices;
		GLuint *indices;

		VAO vao;
		VBO vbo;
		EBO ebo;

		Shader shader;
	}Graphics;

	glm::mat4 projection;

	struct{
		Camera camera;
		std::vector<DefaultEntity> entities;
	}GameObjects;


	std::vector<void (*)(Engine)> startup_functions;
	std::vector<void (*)(Engine)> update_functions;

	void init_graphics();
	void init_matrixes();

public:

	GLFWwindow* getWindow(){ return window; }

	void add_startup_function(void (*func)(Engine)) { startup_functions.push_back(func); };
	void add_update_function(void (*func)(Engine)){ update_functions.push_back(func); }
	void run();

	Engine(const char* window_name, int initWidth, int initHeight, const char* assetPreFix = "");

	Engine();
};

// Calllback Functions
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
