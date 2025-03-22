#include <iostream>

#include "engine.hpp"

void Engine::init_graphics(){
	Graphics.vertices =  new float[]{
		// positions         // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // top left
	};
	Graphics.indices = new GLuint[]{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glEnable(GL_DEPTH_TEST);
	Shader shader("res/shaders/vertexshaders.glsl", "res/shaders/fragmentshaders.glsl");

	VAO VAO1;
	VAO1.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(Graphics.vertices, sizeof(Graphics.vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(Graphics.indices, sizeof(Graphics.indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// unbind all to prevent accidentally modifying them
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();
}

void Engine::init_matrixes(){
	GameObjects.camera = Camera(Graphics.shader, GameObjects.entities[0]);
}

Engine::Engine(const char* window_name, int initWidth, int initHeight, const char* assetPreFix){
	// Init GLFW
	glfwInit();

	// *REMEMER THESE*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, window_name, NULL, NULL);
	if(window == NULL){ std::cout<< "Failed creating window. " <<std::endl;
		glfwTerminate();
	}

	// *MAKE USE OF VARIABLE "window"*
	glfwMakeContextCurrent(window);

	// Load Glad
	gladLoadGL();
	glViewport(0, 0, initWidth, initHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Init Functions
	init_graphics();
	init_matrixes();

	// StartUp Functions
}

Engine::Engine(){
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
	// TODO : Make a printstatement if the engine is build on debug mode
}
