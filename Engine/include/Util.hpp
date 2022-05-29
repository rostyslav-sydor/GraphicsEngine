#ifndef UTIL
#define UTIL
#include "assimp/matrix4x4.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

inline glm::mat4 MatAItoGLM(aiMatrix4x4 aimat) {
	float values[] = {aimat.a1, aimat.a2, aimat.a3, aimat.a4,
					  aimat.b1, aimat.b2, aimat.b3, aimat.b4,
					  aimat.c1, aimat.c2, aimat.c3, aimat.c4,
					  aimat.d1, aimat.d2, aimat.d3, aimat.d4};

	return glm::make_mat4(values);
}

inline void printVector(glm::vec3 vec) {
	std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;
}

inline void printVector(glm::vec4 vec) {
	std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << ' ' << vec.w << std::endl;
}

inline void printVector(std::string str, glm::vec3 vec) {
	std::cout << str << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;
}

inline void printVector(std::string str, glm::vec4 vec) {
	std::cout << str << vec.x << ' ' << vec.y << ' ' << vec.z << ' ' << vec.w << std::endl;
}
#endif