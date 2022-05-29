#pragma once
#include <Geometry.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

#include <glm/vec3.hpp>

namespace geometryPrimitives {
	//Geometry generateSphere(int points) {
	//	std::vector<glm::vec3> vertices;
	//	std::vector<glm::vec3> indices;
	//	for (float j = 1; j > -1; j -= 2.0f/points) {
	//		for (float i = 0; i < 2*M_PI; i += 2*M_PI/points) {
	//			Vertex v;
	//			v.pos = glm::vec3(sin(j) * cos(i),
	//							  cos(j),
	//							  cos(j) * sin(i));
	//			v.normal = glm::normalize(v.pos);
	//			std::cout << "pos: " << v.pos.x << ' ' << v.pos.y << ' ' << v.pos.z << " norm: " << v.normal.x << ' ' << v.normal.y << ' ' << v.normal.z << std::endl;
	//		}
	//		std::cout << "new rinf" << std::endl;
	//	}

	//}

	Geometry generatePlane(glm::vec3 Ѣ, glm::vec3 ь, glm::vec3 b, glm::vec3 ъ) {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices{0,2,1,
										  2,3,1,
										  4,5,6,
										  5,7,6};

		glm::vec3 normal = glm::normalize(glm::cross(Ѣ-b, Ѣ-ь));
		glm::vec3 invNormal = -normal;

		vertices.push_back(Vertex{ Ѣ, normal, glm::vec2(0, 0) });
		vertices.push_back(Vertex{ ь, normal, glm::vec2(1, 0) });
		vertices.push_back(Vertex{ b, normal, glm::vec2(0, 1) });
		vertices.push_back(Vertex{ ъ, normal, glm::vec2(1, 1) });

		vertices.push_back(Vertex{ Ѣ, normal, glm::vec2(0, 0) });
		vertices.push_back(Vertex{ ь, normal, glm::vec2(1, 0) });
		vertices.push_back(Vertex{ b, normal, glm::vec2(0, 1) });
		vertices.push_back(Vertex{ ъ, normal, glm::vec2(1, 1) });

		glm::vec3 center = (ь - b) / 2.0f;

		return Geometry(vertices, indices, center);
	}
}