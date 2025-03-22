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

	Graphics.vao.bind();

	// Generates Vertex Buffer Object and links it to vertices
	Graphics.vbo = VBO(Graphics.vertices, sizeof(Graphics.vertices));
	// Generates Element Buffer Object and links it to indices
	Graphics.ebo = EBO(Graphics.indices, sizeof(Graphics.indices));

	// Links VBO attributes such as coordinates and colors to VAO
	Graphics.vao.linkAttrib(Graphics.vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	Graphics.vao.linkAttrib(Graphics.vbo, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// unbind all to prevent accidentally modifying them
	Graphics.vao.unbind();
	Graphics.vbo.unbind();
	Graphics.ebo.unbind();

	GameObjects.entities.push_back(DefaultEntity(glm::vec3(0.0f, 0.0f, 0.0f),"res/img/grass.png"));

	for(auto& e : GameObjects.entities){
		e.texture.bind();
	}
}

void Engine::init_matrixes(){
	GameObjects.camera = Camera(Graphics.shader, GameObjects.entities[0].pos);

	projection = glm::perspective(glm::radians(110.0f), 800.0f / 800.0f, 0.1f, 100.0f);

	// applying mattrices
	unsigned int modelLoc = glGetUniformLocation(Graphics.shader.get_id(), "model");

	unsigned int projectionLoc = glGetUniformLocation(Graphics.shader.get_id(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}

void Engine::run(){
	for(auto& func : startup_functions){
		func(*this);
	}
	std::cout<< "Startup Functions done initializing." << std::endl;

	for(auto& func : update_functions){
		func(*this);
	}

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
}

Engine::Engine(){
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
	// TODO : Make a printstatement if the engine is build on debug mode
}
