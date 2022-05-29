#include <GraphicObject.hpp>

GraphicObject::GraphicObject(const Material& material,
							 const Geometry& mesh,
							 const Transformation& transformation) :

							 material{ std::make_shared<Material>(material) },
							 mesh{ std::make_shared<Geometry>(mesh)},
							 transformation{ std::make_shared<Transformation>(transformation) } {}

GraphicObject::GraphicObject(std::shared_ptr<Material> material,
							 std::shared_ptr<Geometry> mesh, 
							 std::shared_ptr<Transformation> transformation):	
							 
							 material{material},
							 mesh{mesh},
							 transformation{transformation} {}

void GraphicObject::Render(Camera& camera) const {
	material->Apply();

	const glm::mat4 cam = camera.getProjection() * camera.getView() * transformation->getMatrix();
	
	material->shader.setUniform("camera", cam);
	material->shader.setUniform("model", transformation->getMatrix());
	material->shader.setUniform("viewPos", camera.getPosition());
	glBindVertexArray(mesh->getVAO());
	glDrawElements(GL_TRIANGLES, mesh->numVertices * 3, GL_UNSIGNED_INT, 0);
}

std::shared_ptr<Transformation> GraphicObject::getTransform() {
	return transformation;
}

glm::vec3 GraphicObject::getTranslation() const {
	return transformation->getTranslation();
}

std::array<glm::vec4, 8> GraphicObject::getBoundingBox() const {
	std::array<glm::vec4, 8> points;
	points[0] = glm::vec4(mesh->minX, mesh->minY, mesh->minZ, 1.0f);
	points[1] = glm::vec4(mesh->minX, mesh->minY, mesh->maxZ, 1.0f);
	points[2] = glm::vec4(mesh->minX, mesh->maxY, mesh->minZ, 1.0f);
	points[3] = glm::vec4(mesh->minX, mesh->maxY, mesh->maxZ, 1.0f);
	points[4] = glm::vec4(mesh->maxX, mesh->minY, mesh->minZ, 1.0f);
	points[5] = glm::vec4(mesh->maxX, mesh->minY, mesh->maxZ, 1.0f);
	points[6] = glm::vec4(mesh->maxX, mesh->maxY, mesh->minZ, 1.0f);
	points[7] = glm::vec4(mesh->maxX, mesh->maxY, mesh->maxZ, 1.0f);

	auto mat = transformation->getMatrix();
	for (auto& point : points) {
		point = mat * point;
	}

	return points;
}

std::array<float, 6> GraphicObject::getBoundingCoords() const {
	std::array<float, 6> coords;
	coords[0] = mesh->minX;
	coords[1] = mesh->minY;
	coords[2] = mesh->minZ;
	coords[3] = mesh->maxX;
	coords[4] = mesh->maxY;
	coords[5] = mesh->maxZ;
	return coords;
}