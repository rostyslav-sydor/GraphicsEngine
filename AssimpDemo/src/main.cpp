#include <Engine.hpp>
#include <../res/MateriaExamples.hpp>
#include <geometryPrimitives.hpp>

int main() {
	// Initialization
	Engine engine = Engine::Engine(1600, 900);
	engine.createWindow("Assimp Demo");
	

	BasicTexture bunnymat{ "res/bunny.jpg" };
	//BasicLightTexture bunnymat{ glm::vec3{0.5f, 0.8f, 0.0f} };
	Model bunny{ "res/bunny.obj" };
	bunny.Translate(0.0f, -0.02f, 0.0f);
	//bunny.Scale(2.0f, 2.0f, 2.0f);
	//bunny.Rotate(45.0f, 0.0f, 0.0f, 1.0f);
	GraphicObject ass{ bunnymat, bunny };
	engine.addObject(ass);

	BasicTexture tankmat{ "res/backpack.jpg" };
	//BasicLightColor mat{ glm::vec3{0.5f, 0.8f, 0.0f} };
	Model m_tank{ "res/backpack.obj" };
	m_tank.setScale(0.001f, 0.001f, 0.001f);
	m_tank.setTranslation(0.5f, 0.25f, 0);
	//m_tank.Rotate(-90.0f, 1.0f, 0.0f, 0.0f);
	GraphicObject tank{ tankmat, m_tank };
	engine.addObject(tank);
	//engine.setParent(0, 1);

	BasicTexture shashlyk{ "res/checkerboard.jpg"};
	Model plane{ geometryPrimitives::generatePlane(glm::vec3(-1, 0,-1),
												   glm::vec3( 1, 0,-1),
												   glm::vec3(-1, 0, 1),
												   glm::vec3( 1, 0, 1))};

	plane.setScale(5, 5, 5);
	plane.setTranslation(0, -0.02, 0);
	plane.setRotation(1, 1, 0, 0);

	GraphicObject shashlyk2(shashlyk, plane);
	engine.addObject(shashlyk2);

	// Main rendering loop
	engine.start();

	return 0;
}
