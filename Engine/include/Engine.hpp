#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>

#include <Camera.hpp>
#include <GraphicObject.hpp>
#include <Shader.hpp>
#include <Mesh.hpp>
#include <Texture.hpp>


#include <vector>

class Engine {
public:
	Engine(int width, int height);
	void createWindow(const char* name);
	bool shouldClose();
	void start();
	void stop();
	void addObject(GraphicObject& object);
	void setParent(int child, int parent);

private:
	GLFWwindow* window;
	int width;
	int height;
	Camera camera;
	float FPScap;
	std::vector<GraphicObject> objects;

	void run();
	void render();
	void processKeyboard(GLFWwindow* window, float deltaTime);
	void processMouse();
};