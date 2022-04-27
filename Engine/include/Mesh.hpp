#pragma once
#include <vector>

#include <Vertex.hpp>
#include <Shader.hpp>
#include <Camera.hpp>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh {
public:
	Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
	
	unsigned int getVAO() const;
	
	const unsigned int numVertices{ 0 };
		
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;
	
	void setup(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};