#include <Engine.hpp>
#include <../res/MateriaExamples.hpp>

int main() {
	// Initialization
	Engine engine = Engine::Engine(1600, 900);
	engine.createWindow("Light Demo");
	// Drawing Triangles
	
	BasicLightTexture floormat{ "res/bunny.jpg", glm::vec3(0.1f), glm::vec3(0.6f), glm::vec3(1.0f), 256 };
	BasicLightColor mat{ glm::vec3{0.2f, 0.4f, 0.6f} };
	
	GraphicObject sphere{ floormat, "res/bunny.obj" };
	//sphere.Scale(0.005f, 0.005f, 0.005f);
	engine.addObject(sphere);

	// Main rendering loop

	engine.start();

	return 0;
}
