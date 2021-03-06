#include <Engine.hpp>
#include <../res/MateriaExamples.hpp>

int main() {
	// Initialization
	Engine engine{1600, 900};
	engine.createWindow("Light Demo");

	// Drawing Triangles
	
	BasicLightTexture bunnymat{ "res/bunny.jpg", glm::vec3(0.1f), glm::vec3(0.4f), glm::vec3(0.5f), 128 };
	//BasicLightColor mat{ glm::vec3{0.2f, 0.4f, 0.6f} };
	
	GraphicObject bunny{ bunnymat, "res/bunny.obj" };
	engine.addObject(bunny);

	// Main rendering loop

	engine.start();

	return 0;
}
