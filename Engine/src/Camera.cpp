#include <Camera.hpp>

Camera::Camera() :	position{ glm::vec3{ -0.5f, 0.5f, 0.5f } },
					front{ glm::vec3{0.0f, 0.0f, -1.0f} },
					up{ glm::vec3{0.0f, 1.0f, 0.0f} },
					right{ glm::vec3{1.0f, 0.0f, 0.0f} },
					projection{ glm::perspective(glm::radians(60.0f), 1600.0f/900.0f, 0.1f, 100.0f) } {}

void Camera::changePosition(glm::vec3 vector) {
	position += vector;
	view = glm::lookAt(position, position + front, up);
}

const glm::mat4& Camera::getView() {
	return view;
}

const glm::mat4& Camera::getProjection() {
	return projection;
}

glm::vec3& Camera::getPosition() {
	return position;
}

glm::vec3& Camera::getFront() {
	return front;
}

glm::vec3& Camera::getUp() {
	return up;
}

glm::vec3& Camera::getRight() {
	return right;
}

void Camera::setFront(glm::vec3 front) {
	this->front = front;
	view = glm::lookAt(position, position + front, up);
}

void Camera::setRight(glm::vec3 right) {
	this->right = right;
}