#include <GraphicObject.hpp>

GraphicObject::GraphicObject(Material& material, Model model) : material{ material }, model{ model } {}

GraphicObject::GraphicObject(Material& material, const char* filename) : material{ material }, model{ filename } {}

void GraphicObject::Render(Camera& camera) const {
	material.Apply();

	glm::mat4 a = model.getTransformation();
	const glm::mat4 cam = camera.getProjection() * camera.getView() * model.getTransformation();
	
	material.shader.setUniform("camera", cam);
	material.shader.setUniform("model", model.getTransformation());
	material.shader.setUniform("viewPos", camera.getPosition());

	model.Render();
}