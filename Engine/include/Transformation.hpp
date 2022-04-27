#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Transformation {
public:
	glm::mat4 getTransform() const;

	void Translate(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float x, float y, float z);

	void setTranslation(float x, float y, float z);
	void setRotation(float angle, float x, float y, float z);
	void setScale(float x, float y, float z);

	glm::mat4 translation{ 1.0f };
private:
	
	glm::mat4 rotation{ 1.0f };
	glm::mat4 scale{ 1.0f };
};