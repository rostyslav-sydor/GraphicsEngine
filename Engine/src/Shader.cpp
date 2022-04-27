#include <Shader.hpp>

Shader::Shader() : id{glCreateProgram()} {}

Shader::Shader(const char* vertexShader, const char* fragmentShader): Shader() {
	addShader(vertexShader, GL_VERTEX_SHADER);
	addShader(fragmentShader, GL_FRAGMENT_SHADER);
	linkProgram();
}

void Shader::compileShader(const char* vertexShader, const char* fragmentShader) {
	addShader(vertexShader, GL_VERTEX_SHADER);
	addShader(fragmentShader, GL_FRAGMENT_SHADER);
	linkProgram();
}
void Shader::linkProgram() {
	glLinkProgram(id);

	int success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << "Failed to link shader program." << std::endl;
		exit(1);
	}

	for (auto i : shaders) {
		glDeleteShader(i);
	}

	shaders.clear();
}

void Shader::addShader(const char* text, int type) {
	unsigned int shader = glCreateShader(type);
	int  success;
	char infoLog[512];
	glShaderSource(shader, 1, &text, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Error: failed to compile shader\n" << infoLog << std::endl;
	}
	glAttachShader(id, shader);
}

void Shader::setUniform(const char* name, const glm::vec3& vector) {
	unsigned int location = glGetUniformLocation(id, name);
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::setUniform(const char* name, const glm::mat4& matrix) {
	unsigned int location = glGetUniformLocation(id, name);
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
}

void Shader::setUniform(const char* name, int uniform) {
	unsigned int location = glGetUniformLocation(id, name);
	glUniform1i(location, uniform );
}

unsigned int const Shader::getId() { return id; }