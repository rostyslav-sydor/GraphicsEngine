#include <Engine.hpp>

#include <iostream>
#include <stdexcept>

Engine::Engine(int width, int height) : width{ width }, height{ height }, window{ NULL }, FPScap{ 60 }, camera{ 60, 16.0 / 9, 0.1, 100 } {}

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
	generateOcclusionShader();
	glClearColor(0.2f, 0.4f, 0.4f, 1.0f);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
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
	queries.resize(objects.size(), 0);
	glGenQueries(objects.size(), queries.data());

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
				auto camPos = camera.getPosition();
				std::sort(objects.begin(), objects.end(), [&camPos](const GraphicObject& x, const GraphicObject& y) {
					return glm::l2Norm(x.getTranslation() - camPos) < glm::l2Norm(y.getTranslation() - camPos);
					});
				std::cout << "FPS: " << fpsCount << std::endl;
				std::cout <<  " frustum: " << frustumCulling << "; occlusion: " << occlusionCulling << std::endl;

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
	
	int drawn = 0;
	auto planes = camera.getFrustumPlanes();
	auto mat = camera.getProjection() * camera.getView();
	
	

	for (int i = 0; i < objects.size(); ++i) {
		if (frustumCulling && isFrustumCulled(planes, objects[i].getBoundingBox()))
			continue;
		int res;
		
		if (occlusionCulling) {
			glGetQueryObjectiv(queries[i], GL_QUERY_RESULT, &res);
			if (res) ++drawn;
			glBeginQuery(GL_ANY_SAMPLES_PASSED, queries[i]);
			glColorMask(0, 0, 0, 0);
			glDepthMask(0);
			//Draw bounding box here
			glUseProgram(occlusionShader->getId());
			auto bcoords = objects[i].getBoundingCoords();
			occlusionShader->setUniform("minc", glm::vec3(bcoords[0], bcoords[1], bcoords[2]));
			occlusionShader->setUniform("maxc", glm::vec3(bcoords[3], bcoords[4], bcoords[5]));
			occlusionShader->setUniform("transform", mat * objects[i].getTransform()->getMatrix());
			glDrawArrays(GL_POINTS, 0, 1);
			glEndQuery(GL_ANY_SAMPLES_PASSED);

			glColorMask(1, 1, 1, 1);
			glDepthMask(1);

			glBeginConditionalRender(queries[i], GL_QUERY_WAIT);
			objects[i].Render(camera);
			glEndConditionalRender();
		}
		else {
			objects[i].Render(camera);
			++drawn;
		}
		


	}
	//std::cout << "Objects not drawn: " << objects.size() - drawn << " frustum: " << frustumCulling << "; occlusion: " << occlusionCulling << std::endl;
	
	glfwSwapBuffers(window);
}

bool Engine::isFrustumCulled(const std::vector<glm::vec4>& planes, const std::array<glm::vec4, 8>& points) {	
	for (const auto& plane : planes) {
		int pass = 0;
		for (const auto& point : points) {
			if (glm::dot(plane, point) < 0) pass++;
		}
		if (pass == 8) return true;
	}
	return false;
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
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		frustumCulling = !frustumCulling;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		occlusionCulling = !occlusionCulling;
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

void Engine::addObject(const Model& model) {
	for(auto& obj: model.meshes)
		objects.push_back(obj);
}

void Engine::generateOcclusionShader() {
	const char* vertexShaderSource = R"r(
		#version 330 core
		void main(){
			gl_Position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	)r";

	const char* geometryShaderSource = R"r(
		#version 330 core
		layout (points) in;
		layout (triangle_strip, max_vertices = 17) out;
		uniform vec3 minc, maxc;
		uniform mat4 transform;

		vec4 coords[17] = vec4[17](
						vec4(minc.x, minc.y, minc.z, 1),
						vec4(minc.x, minc.y, maxc.z, 1),
						vec4(minc.x, maxc.y, minc.z, 1),
						vec4(minc.x, maxc.y, maxc.z, 1),
						vec4(maxc.x, maxc.y, minc.z, 1),
						vec4(maxc.x, maxc.y, maxc.z, 1),
						vec4(maxc.x, minc.y, minc.z, 1),
						vec4(maxc.x, minc.y, maxc.z, 1),
						vec4(minc.x, minc.y, minc.z, 1),
						vec4(minc.x, minc.y, maxc.z, 1),
						vec4(maxc.x, minc.y, maxc.z, 1),
						vec4(minc.x, maxc.y, maxc.z, 1),
						vec4(maxc.x, maxc.y, maxc.z, 1),
						vec4(minc.x, maxc.y, minc.z, 1),
						vec4(maxc.x, maxc.y, minc.z, 1),
						vec4(minc.x, minc.y, minc.z, 1),
						vec4(maxc.x, minc.y, minc.z, 1)
						);

		void main(){
			for(int i = 0; i < 17; ++i){
				gl_Position = transform * coords[i];
				EmitVertex();
			}
			EndPrimitive();
		}
	)r";

	const char* fragmentShaderSource = R"r(
			#version 330 core
			out vec4 FragColor;
			void main(){
				FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			}
		)r";
	occlusionShader = std::make_shared<Shader>( vertexShaderSource, geometryShaderSource, fragmentShaderSource );
}