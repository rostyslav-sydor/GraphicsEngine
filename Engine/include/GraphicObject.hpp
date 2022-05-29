#pragma once

#include <array>

#include <Material.hpp>
#include <Geometry.hpp>
#include <Transformation.hpp>
#include <Camera.hpp>
#include <../res/MateriaExamples.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GraphicObject {
public:
	GraphicObject(const Material& material, const Geometry& mesh, const Transformation& transformation);
	GraphicObject(std::shared_ptr<Material> material, std::shared_ptr<Geometry> mesh, std::shared_ptr<Transformation> transformation);

	void Render(Camera& camera) const;

	std::shared_ptr<Transformation> getTransform();
	glm::vec3 getTranslation() const ;

	std::array<glm::vec4, 8> getBoundingBox() const;
	std::array<float, 6> getBoundingCoords() const;

	float getBoundingRadius() const;

	unsigned int getVAO() const { return mesh->getVAO(); }
	
private:
	std::shared_ptr<Material> material;
	std::shared_ptr<Geometry> mesh;
	std::shared_ptr<Transformation> transformation;
};