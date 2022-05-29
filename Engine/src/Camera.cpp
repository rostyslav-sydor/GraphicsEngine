#include <Camera.hpp>
#include <iostream>

Camera::Camera(float fov, float aspect, float nearPlane, float farPlane):
					fov{ fov }, aspect{ aspect }, nearPlane{ nearPlane }, farPlane{farPlane},
					position{ glm::vec3{ 0.0f, 0.0f, 2.0f } },
					front{ glm::vec3{0.0f, 0.0f, -1.0f} },
					up{ glm::vec3{0.0f, 1.0f, 0.0f} },
					right{ glm::vec3{1.0f, 0.0f, 0.0f} },
					projection{ glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane) } {}

void Camera::changePosition(glm::vec3 vector) {
	position += vector;
	view = glm::lookAt(position, position + front, up);
}

const glm::mat4& Camera::getView() { return view; }

const glm::mat4& Camera::getProjection() { return projection; }

glm::vec3& Camera::getPosition() { return position; }

glm::vec3& Camera::getFront() {	return front; }

glm::vec3& Camera::getUp() { return up; }

glm::vec3& Camera::getRight() {	return right; }

float Camera::getFOV() { return fov; }

float Camera::getAspect() { return aspect; }

float Camera::getNearPlane() { return nearPlane; }

float Camera::getFarPlane() { return farPlane; }

void Camera::setFront(glm::vec3 front) {
	this->front = front;
	view = glm::lookAt(position, position + front, up);
}

void Camera::setRight(glm::vec3 right) {
	this->right = right;
}

void Camera::setFOV(float fov) {
	this->fov = fov;
}

std::vector<glm::vec4> Camera::getFrustumPlanes(){
	std::vector<glm::vec4> planes;

	auto mat = glm::transpose(projection * view);

	planes.emplace_back(mat[3] + mat[0]); // left
	planes.emplace_back(mat[3] - mat[0]); // right
	planes.emplace_back(mat[3] + mat[1]); // down
	planes.emplace_back(mat[3] - mat[1]); // up
	planes.emplace_back(mat[3] + mat[2]); // near
	planes.emplace_back(mat[3] - mat[2]); // far
	
	// normalize planes equations
	for (auto& plane : planes) {
		plane /= glm::sqrt(plane.x * plane.x + plane.y * plane.y + plane.z * plane.z);;
	}

	return planes;
}
