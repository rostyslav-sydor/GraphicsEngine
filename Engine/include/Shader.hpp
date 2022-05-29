#pragma once
#include <vector>
#include <glad/glad.h>
#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader();
	Shader(const char* vertexShader, const char* fragmentShader);
	Shader(const char* vertexShader, const char* geometryShader, const char* fragmentShader);

	void compileShader(const char* vertexShader, const char* fragmentShader);

	void addShader(const char* text, int type);
	void linkProgram();
	unsigned int const getId();
	void setUniform(const char* name, const glm::vec3& uniform);
	void setUniform(const char* name, const glm::mat4& uniform);
	void setUniform(const char* name, int uniform);
private:
	std::vector<unsigned int> shaders;
	unsigned int id;
};

