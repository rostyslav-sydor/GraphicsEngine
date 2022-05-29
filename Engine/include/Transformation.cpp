#include <Transformation.hpp>

Transformation::Transformation(glm::mat4 translation, glm::mat4 rotation, glm::mat4 scale) : translation{ translation }, rotation{ rotation }, scale{scale} {};

Transformation::Transformation(const glm::mat4& transformMat) {
	glm::vec3 scale;
	glm::quat rotate;
	glm::vec3 translate;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transformMat, scale, rotate, translate, skew, perspective);

	this->scale = glm::scale(glm::mat4{ 1.0f }, scale);
	this->rotation = glm::mat4_cast(rotate);
	this->translation = glm::translate(glm::mat4{ 1.0f }, translate);
}

glm::mat4 Transformation::getMatrix() const {
	glm::mat4 mat = translation * rotation * scale;
	if(parent)
		return parent->getMatrix() * mat;
	else
		return mat;
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
	scale = glm::scale(glm::mat4{ 1.0f }, glm::vec3(x, y, z));
}

void Transformation::setParent(std::shared_ptr<Transformation> parent) {
	this->parent = parent;
}

glm::vec3 Transformation::getScale() {
	if(parent)
		return parent->getMatrix() * glm::vec4(scale[0][0], scale[1][1], scale[2][2], 1.0f);
	else
		return glm::vec3(scale[0][0], scale[1][1], scale[2][2]);
}

glm::vec3 Transformation::getTranslation() const {
	if(parent)
		return parent->getMatrix() * glm::vec4(translation[3][0], translation[3][1], translation[3][2], 1.0f);
	else
		return glm::vec3(translation[3][0], translation[3][1], translation[3][2]);
}