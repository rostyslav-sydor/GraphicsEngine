#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <memory>

class Transformation {
public:
	Transformation(glm::mat4 translation, glm::mat4 rotation, glm::mat4 scale);
	Transformation(const glm::mat4& mat);
	Transformation() = default;

	glm::mat4 getMatrix() const;

	void Translate(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float x, float y, float z);

	void setTranslation(float x, float y, float z);
	void setRotation(float angle, float x, float y, float z);
	void setScale(float x, float y, float z);

	void setParent(std::shared_ptr<Transformation> parent);

	glm::vec3 getScale();
	glm::vec3 getTranslation() const ;

private:
	glm::mat4 translation{ 1.0f };
	glm::mat4 rotation{ 1.0f };
	glm::mat4 scale{ 1.0f };

	std::shared_ptr<Transformation> parent{nullptr};
};