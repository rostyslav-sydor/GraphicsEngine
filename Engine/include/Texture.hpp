#pragma once
#include <stb_image.h>
#include <glad/glad.h>	

class Texture {
public:
	Texture() = delete;
	Texture(const char* filename);
	unsigned int getId();
private:
	int width, height, nrChannel;
	unsigned int id;
};