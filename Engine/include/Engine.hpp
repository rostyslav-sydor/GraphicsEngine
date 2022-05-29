#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <glm/gtx/norm.hpp>

#include <Camera.hpp>
#include <Shader.hpp>
#include <Geometry.hpp>
#include <Texture.hpp>
#include <Model.hpp>

#include <vector>


class Engine {
public:
	Engine(int width, int height);
	void createWindow(const char* name);
	bool shouldClose();
	void start();
	void stop();
	void addObject(GraphicObject& object);
	void addObject(const Model& object);
	
private:
	GLFWwindow* window;
	int width;
	int height;
	Camera camera;
	float FPScap;
	bool frustumCulling, occlusionCulling;
	std::vector<GraphicObject> objects;
	std::vector<unsigned int> queries;
	std::shared_ptr<Shader> occlusionShader;

	void run();
	void render();
	bool isFrustumCulled(const std::vector<glm::vec4>& planes, const std::array<glm::vec4, 8>& points);
	void generateOcclusionShader();

	void processKeyboard(GLFWwindow* window, float deltaTime);
	void processMouse();
};