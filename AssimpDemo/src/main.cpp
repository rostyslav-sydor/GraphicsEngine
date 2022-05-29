#include <Engine.hpp>
#include <../res/MateriaExamples.hpp>
#include <geometryPrimitives.hpp>

int main() {
	// Initialization
	Engine engine = Engine::Engine(1600, 900);
	engine.createWindow("Assimp Demo");

	BasicTexture bunnymat{ "res/bunny.jpg" };
	//Model m_sphere{ "res/sphere.obj", std::make_shared<BasicTexture>(bunnymat)};
	//m_sphere.setScale(0.001, 0.001, 0.001);
	//engine.addObject(m_sphere);
	////BasicLightTexture bunnymat{ glm::vec3{0.5f, 0.8f, 0.0f} };
	Model m_bunny{ "res/bunny.obj", std::make_shared<BasicTexture>(bunnymat)};
	m_bunny.Translate(0.0f, -0.02f, 0.0f);
	//m_bunny.Scale(1.0f, 4.0f, 2.0f);
	m_bunny.Rotate(45.0f, 0.0f, 0.0f, 1.0f);
	engine.addObject(m_bunny);

	BasicTexture backpackmat{ "res/backpack.jpg" };
	Model m_backpack{ "res/backpack.fbx", std::make_shared<BasicTexture>(backpackmat) };
	m_backpack.setScale(0.002f, 0.002f, 0.002f);
	m_backpack.setTranslation(0.5f, 0.7f, 0);

	engine.addObject(m_backpack);

	BasicTexture checkerboardmat{ "res/checkerboard.jpg"};
	auto plane = std::make_shared<Geometry>(geometryPrimitives::generatePlane(	glm::vec3(-1, 0,-1),
																				glm::vec3( 1, 0,-1),
																				glm::vec3(-1, 0, 1),
																				glm::vec3( 1, 0, 1)));
	
	std::cout << plane->maxX << ' ' << plane->maxY << ' ' << plane->maxZ << std::endl;
	auto trans = std::make_shared<Transformation>();
	GraphicObject m_plane{std::make_shared<BasicTexture>(checkerboardmat), plane, trans};
	trans->Scale(5, 5, 5);
	trans->setTranslation(0, -0.02, 0);
	trans->setRotation(1, 1, 0, 0);
	engine.addObject(m_plane);

	// Main rendering loop
	engine.start();

	return 0;
}
