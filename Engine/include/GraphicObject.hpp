#pragma once
#include <Material.hpp>
#include <Model.hpp>
#include <Camera.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GraphicObject {
public:
	GraphicObject(Material& material, Model model);
	GraphicObject(Material& material, const char* filename);

	void Render(Camera& camera) const;
	
	Material& material;
	Model model;

private:
};