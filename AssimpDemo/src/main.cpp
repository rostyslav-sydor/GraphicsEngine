#include <Engine.hpp>
#include <../res/MateriaExamples.hpp>
#include <geometryPrimitives.hpp>

int main() {
	// Initialization
	Engine engine = Engine::Engine(1600, 900);
	engine.createWindow("Assimp Demo");

	BasicLightTexture bunnymat{ "res/dragon.jpeg" };
	Model m_bunny{ "res/dragon.ply", std::make_shared<BasicLightTexture>(bunnymat)};
	//m_bunny.Translate(0.0f, -0.02f, 0.0f);
	//m_bunny.Scale(0.01f, 0.01f, 0.01f);
	m_bunny.Scale(2, 2, 2);
	//m_bunny.Rotate(90.0f, -1, 0, 0);
	engine.addObject(m_bunny);

	BasicLightTexture backpackmat{ "res/backpack.jpg" };
	Model m_backpack{ "res/backpack.fbx", std::make_shared<BasicLightTexture>(backpackmat) };
	m_backpack.setScale(0.002f, 0.002f, 0.002f);
	m_backpack.setTranslation(0.5f, 0.7f, 0);

	//engine.addObject(m_backpack);

	//BasicTexture checkerboardmat{ "res/checkerboard.jpg"};
	//auto plane = std::make_shared<Geometry>(geometryPrimitives::generatePlane(	glm::vec3(-1, 0,-1),
	//																			glm::vec3( 1, 0,-1),
	//																			glm::vec3(-1, 0, 1),
	//																			glm::vec3( 1, 0, 1)));
	
	//auto trans = std::make_shared<Transformation>();
	//GraphicObject m_plane{std::make_shared<BasicTexture>(checkerboardmat), plane, trans};
	//trans->Scale(5, 5, 5);
	//trans->setTranslation(0, -0.02, 0);
	//trans->setRotation(1, 1, 0, 0);
	//engine.addObject(m_plane);

	// Main rendering loop
	engine.start();

	return 0;
}
