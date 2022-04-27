#include <Transformation.hpp>

glm::mat4 Transformation::getTransform() const {
	return translation * rotation * scale;
}

void Transformation::Translate(float x, float y, float z) {
	translation = glm::translate(translation, glm::vec3(x, y, z));
}

void Transformation::Rotate(float angle, float x, float y, float z) {
	rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(x, y, z));
}

void Transformation::Scale(float x, float y, float z) {
	scale = glm::scale(scale, glm::vec3(x, y, z));
}

void Transformation::setTranslation(float x, float y, float z) {
	translation = glm::translate(glm::mat4{ 1.0f }, glm::vec3(x, y, z));
}

void Transformation::setRotation(float angle, float x, float y, float z) {
	rotation = glm::rotate(glm::mat4{ 1.0f }, glm::radians(angle), glm::vec3(x, y, z));
}

void Transformation::setScale(float x, float y, float z) {
	this->scale = glm::scale(glm::mat4{ 1.0f }, glm::vec3(x, y, z));
}
