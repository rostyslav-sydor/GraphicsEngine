#pragma once
#include <vector>
#include <string>
#include <iostream>

#include <Vertex.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Geometry {
public:

	Geometry(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, glm::vec3 center);
	Geometry(const std::string& filename);

	unsigned int getVAO() const;

	unsigned int numVertices{ 0 };

	float maxX = 0, maxY = 0, maxZ = 0;
	float minX = 0, minY = 0, minZ = 0;
private:
	unsigned int VAO, VBO, IBO;
	void setup(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, glm::vec3 center);
};
