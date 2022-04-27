#include <Engine.hpp>
#include <../res/MateriaExamples.hpp>
#include <thread>

int main() {
	// Initialization
	Engine engine = Engine::Engine(1600, 900);
	engine.createWindow("Cube Demo");

	// Drawing Triangles
	BasicTexture mat{ "res/crate.jpg" };
	//BasicColor mat{ glm::vec3{0.0f, 1.0f, 0.0f} };

	Model cube{"res/crate.blend"};
	cube.transformation.setScale(0.5f, 0.5f, 0.5f);
	for (long long i = 0; i < 10; ++i) {
		for (long long j = 0; j < 10; ++j) {
			for (long long k = 0; k < 10; ++k) {
				GraphicObject obj = GraphicObject(mat, cube);
				obj.model.transformation.setTranslation((i - 5) * 2.0f + 1.0f, (j-5) * 2.0f + 1.0f, -k * 2.0f - 10.0f);
				engine.addObject(obj);
			}
		}
	}

	// Main rendering loop

engine.start();
	return 0;
}
