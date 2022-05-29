#include <Engine.hpp>
#include <../res/MateriaExamples.hpp>
#include <geometryPrimitives.hpp>

int main() {
	// Initialization
	Engine engine = Engine::Engine(1600, 900);
	engine.createWindow("Cube Demo");

	// Drawing Triangles
	BasicTexture mat{ "res/crate.jpg" };
	//BasicColor mat{ glm::vec3{0.0f, 1.0f, 0.0f} };

	//Geometry a = geometryPrimitives::generatePlane(	{-1,-1,-1},
	//												{ 1,-1,-1},
	//												{-1, 1,-1},
	//												{ 1, 1,-1});

	//Transformation transform{};
	//GraphicObject plane(mat, a, transform);
	//engine.addObject(plane);
	Model cube{"res/crate.blend", std::make_shared<BasicTexture>(mat)};
	cube.setScale(0.5f, 0.5f, 0.5f);
	cube.setTranslation(1.f, 1.f, -1.f);
	engine.addObject(cube);
	//cube.transformation.setScale(0.5f, 0.5f, 0.5f);
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
