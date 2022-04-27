#pragma once

#include <Shader.hpp>
#include <Texture.hpp>

class Material {
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, int shininess);
	Material(const Shader& shader);
	virtual void Apply();

	Shader shader;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	int shininess;

protected:
	Material();
};