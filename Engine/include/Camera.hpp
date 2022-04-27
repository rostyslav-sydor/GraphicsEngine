#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera {
public:
	Camera();
	const glm::mat4& getView();
	const glm::mat4& getProjection();
	glm::vec3& getPosition();
	glm::vec3& getFront();
	glm::vec3& getUp();
	glm::vec3& getRight();

	void setFront(glm::vec3 front);
	void setRight(glm::vec3 right);

	void changePosition(glm::vec3 vector);

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 projection;
	glm::mat4 view{ 1.0f };
};