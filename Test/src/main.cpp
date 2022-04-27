#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <Engine.hpp>

#include <iostream>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main() {
	stbi_set_flip_vertically_on_load(true);

	// Initialization
	int width = 1600;
	int height = 900;
	Engine engine = Engine::Engine(width, height);
	engine.createWindow("Hello");

	glClearColor(0.2f, 0.5f, 0.5f, 1.0f);

	// Shaders

	Shader shader{};
	shader.addShader(vertexShaderSource, GL_VERTEX_SHADER);
	shader.addShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	shader.linkProgram();

	// Creating texture

	Texture texture{ "res\\container.jpg" };

	// Drawing Triangles

	std::vector<Vertex> vertices1 = {
		Vertex(glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(0.0f,  1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f, 0.5f), glm::vec2(1.0f,  1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f,  0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f,  0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,-0.5f), glm::vec2(0.0f,  1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,-0.5f), glm::vec2(1.0f,  1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f,-0.5f), glm::vec2(0.0f,  0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f,-0.5f), glm::vec2(1.0f,  0.0f)),
	};

	std::vector<glm::uvec3> indices1 = {
		glm::uvec3(0, 1, 2),
		glm::uvec3(1, 2, 3),
		glm::uvec3(4, 5, 6),
		glm::uvec3(5, 6, 7),
		glm::uvec3(0, 2, 4),
		glm::uvec3(2, 4, 6),
		glm::uvec3(1, 3, 5),
		glm::uvec3(3, 5, 7),
		glm::uvec3(2, 3, 6),
		glm::uvec3(3, 6, 7),
		glm::uvec3(0, 1, 4),
		glm::uvec3(1, 4, 5)
	};

	Mesh mesh{ vertices1, indices1 };
	Material material{ shader, texture };
	for (int i = 0; i < 7; ++i) {
		engine.addObject(GraphicObject{ material, mesh });
	}


	// Main rendering loop

	engine.start();

	return 0;
}