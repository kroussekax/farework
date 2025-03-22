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

		VAO VAO;
		VBO VBO;
		EBO EBO;

		Shader shader;

	}Graphics;

	struct{
		Camera camera;
		std::vector<DefaultEntity> entities;
	}GameObjects;


	std::vector<void (*)(Engine)> startupFunction;
	std::vector<void (*)(Engine)> updateFunction;

	void init_graphics();
	void init_matrixes();

public:

	Engine(const char* window_name, int initWidth, int initHeight, const char* assetPreFix = "");

	Engine();
};

// Calllback Functions
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
