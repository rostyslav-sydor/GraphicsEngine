#include <Engine.hpp>

#include <iostream>
#include <stdexcept>

Engine::Engine(int width, int height) : width{ width }, height{ height }, window{ NULL }, FPScap{ 1000 } {}

static void aboba(GLFWwindow* window, double x, double y) {}

void Engine::createWindow(const char* name) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (window == NULL) {
		glfwTerminate();
		throw std::runtime_error("Error creating GLFW window");
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glClearColor(0.2f, 0.4f, 0.4f, 0.0f);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	stbi_set_flip_vertically_on_load(true);
}

void Engine::start() {
	run();
}

bool Engine::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Engine::run() {
	// TODO normal time counter
	// TODO normal movement system
	double deltaTime{ 0.0f }, lastTime{ 0.0f }, lastRenderTime{ 0.0f }, renderTime{ 0.0f }, fpsTime{ 0.0f };
	int fpsCount{ 0 };
	float frequency = 1 / FPScap;

	while (!glfwWindowShouldClose(window)) {
		renderTime = glfwGetTime() - lastRenderTime;

		deltaTime = glfwGetTime() - lastTime;

		processKeyboard(window, deltaTime * 30);
		
		processMouse();

		lastTime = glfwGetTime();

		if(renderTime > frequency){
			render();
			if (glfwGetTime() - fpsTime > 1.0f) {
				std::cout << "FPS: " << fpsCount << std::endl;
				fpsCount = 0;
				fpsTime = glfwGetTime();
			}
			++fpsCount;
			lastRenderTime = glfwGetTime();
		}
		glfwPollEvents();
	}

	stop();
}

void Engine::render() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//objects[0].model.setTranslation(3*sin(glfwGetTime()), 0, 0);
	for (auto const& object: objects) {
		object.Render(camera);
	}
	//std::cout << glGetError() << std::endl;
	glfwSwapBuffers(window);
}

void Engine::processKeyboard(GLFWwindow* window, float deltaTime) {
	float cameraSpeed{deltaTime * 0.05f};
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.changePosition(cameraSpeed * camera.getFront());
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.changePosition(-cameraSpeed * camera.getFront());
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.changePosition(-cameraSpeed * camera.getRight());
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.changePosition(cameraSpeed * camera.getRight());
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.changePosition(cameraSpeed * camera.getUp());
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.changePosition(-cameraSpeed * camera.getUp());
}

void Engine::processMouse() {
	static double x{ 0 }, y{ 0 }, lastX{ 0 }, lastY{ 0 };
	static double yaw{ -glm::radians( -90.0f) }, pitch{ 0 };
	static bool isFirst{ true };
	glfwGetCursorPos(window, &x, &y);

	if (isFirst) {
		isFirst = false;
		lastX = x;
		lastY = y;
	}

	double offsetX{ x - lastX };
	double offsetY{ lastY - y };

	if (!offsetX && !offsetY) {
		return;
	}

	lastX = x;
	lastY = y;

	float sensitivity{ 0.25f };

	offsetX *= sensitivity;
	offsetY *= sensitivity;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	camera.setFront(glm::normalize(newFront));
	camera.setRight(glm::normalize(glm::cross(camera.getFront(), camera.getUp())));
}


void Engine::stop() {
	glfwTerminate();
}

void Engine::addObject(GraphicObject& object) {
	objects.push_back(object);
}

void Engine::setParent(int child, int parent) {
	if (child != parent && child < objects.size() && parent < objects.size())
		objects[child].model.setParent(&objects[parent].model);
}