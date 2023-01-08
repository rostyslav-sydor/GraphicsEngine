#include <Engine.hpp>
#include <../res/MateriaExamples.hpp>
#include <geometryPrimitives.hpp>

int main() {
	// Initialization
	Engine engine = Engine::Engine(1600, 900);
	engine.createWindow("Culling Demo");

	
	auto mat = std::make_shared<BasicLightColor>(glm::vec3(1.0f, 1.0f, 1.0f));

	auto dragonmesh = std::make_shared<Geometry>("res/dragon.ply");
	auto tr = std::make_shared<Transformation>();
	for (long long i = 0; i < 5; ++i) {
		for (long long j = 0; j < 5; ++j) {
			for (long long k = 0; k < 5; ++k) {
				auto tr = std::make_shared<Transformation>();
				tr->Scale(5, 5, 5);
				tr->Translate((i - 5) * 2.0f + 1.0f, (j - 5) * 2.0f + 1.0f, -k * 2.0f - 10.0f);
				GraphicObject dragon{ mat, dragonmesh, tr };
				engine.addObject(dragon);
			}
		}
	}
	
	// Main rendering loop
	//auto matcube = std::make_shared<BasicTexture>("res/crate.jpg");
	//Model cube{ "res/crate.blend", matcube };
	//cube.Scale(4, 4, 4);
	//cube.Translate(0, 0, 4);
	//engine.addObject(cube);



	engine.start();
	return 0;
}
