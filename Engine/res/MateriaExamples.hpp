#pragma once
#include <Material.hpp>

class BasicTexture : public Material{
public:
	BasicTexture(const char* textureFile) : Material{}, texture{ Texture{textureFile} } {
		this->shader = Shader{ simpleTextureVertexShaderSource, simpleTextureFragmentShaderSource };
	}
	
	BasicTexture(Texture texture) : Material{}, texture{ texture } {
		this->shader = Shader{ simpleTextureVertexShaderSource, simpleTextureFragmentShaderSource };
	}

	void Apply() override {
		glUseProgram(shader.getId());
		glBindTexture(GL_TEXTURE_2D, texture.getId());
	}

private:
	Texture texture;

	const char* simpleTextureVertexShaderSource = R"r(
			#version 330 core
			layout (location = 0) in vec3 ipos;
			layout (location = 2) in vec2 itexture;
			out vec2 tex;
			uniform mat4 camera;
			void main(){
				gl_Position = camera * vec4(ipos, 1.0);
				tex = itexture;
			}
		)r";

	const char* simpleTextureFragmentShaderSource = R"r(
			#version 330 core
			out vec4 FragColor;
			in vec2 tex;
			uniform sampler2D texSampler;
			void main(){
				FragColor = texture(texSampler,tex);
			}
		)r";
};

class BasicLightTexture : public Material {
public:
	BasicLightTexture(const char* textureFile, glm::vec3 ambient = glm::vec3(0.1f), glm::vec3 diffuse = glm::vec3(0.6f), glm::vec3 specular = glm::vec3(0.3f), int shininess = 64) : Material{ambient, diffuse, specular, shininess}, texture{ Texture{textureFile} } {
		this->shader = Shader{ simpleTextureVertexShaderSource, simpleTextureFragmentShaderSource };
	}

	BasicLightTexture(Texture texture) : Material{}, texture{ texture } {
		this->shader = Shader{ simpleTextureVertexShaderSource, simpleTextureFragmentShaderSource };
	}

	void Apply() override {
		glUseProgram(shader.getId());
		glBindTexture(GL_TEXTURE_2D, texture.getId());
		static glm::vec3 lightPos{ 1.0f, 0.1f, 0.0f };
		//lightPos.x = 1 * sin(glfwGetTime());
		//lightPos.z = 1 * cos(glfwGetTime());
		shader.setUniform("lightPos", lightPos);
		shader.setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setUniform("mat.ambient", ambient);
		shader.setUniform("mat.diffuse", diffuse);
		shader.setUniform("mat.specular", specular);
		shader.setUniform("mat.shininess", shininess);
	}

private:
	Texture texture;

	const char* simpleTextureVertexShaderSource = R"r(
			#version 330 core
			layout (location = 0) in vec3 ipos;
			layout (location = 1) in vec3 inormal;
			layout (location = 2) in vec2 itexture;
			out vec3 normal, fragPos;
			out vec2 tex;
			uniform mat4 camera, model;
			void main(){
				gl_Position = camera * vec4(ipos, 1.0);
				fragPos = vec3(model * vec4(ipos, 1.0));
				normal = vec3(model * vec4(inormal, 1.0));
				tex = itexture;
			}
		)r";

	const char* simpleTextureFragmentShaderSource = R"r(
			#version 330 core
			struct Material {
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				int shininess;
			};
			out vec4 FragColor;
			in vec3 normal, fragPos;
			in vec2 tex;
			uniform Material mat;
			uniform sampler2D texSampler;
			uniform vec3 lightPos, viewPos, lightColor;
			void main(){
				vec3 ambient = lightColor * mat.ambient;
				
				vec3 norm = normalize(normal);
				vec3 lightDirection = normalize(lightPos - fragPos);
				vec3 diffuse = lightColor * max(dot(lightDirection, norm), 0.0) * mat.diffuse;

				vec3 viewDir = normalize(viewPos - fragPos);
				vec3 reflectDir = reflect(-lightDirection, norm);
				float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
				vec3 specular = lightColor * spec * mat.specular;

				FragColor = texture(texSampler,tex) * vec4((ambient + diffuse + specular), 1.0);
			}
		)r";
};

class BasicLightColor : public Material {
public:
	BasicLightColor(glm::vec3 color) : Material{}, color{ color } {
		this->shader = Shader{ simpleTextureVertexShaderSource, simpleTextureFragmentShaderSource };
	}

	void Apply() override {
		glUseProgram(shader.getId());
		shader.setUniform("col", color);
		static glm::vec3 lightPos{ 1.0f, 0.5f, 0.0f };
		/*lightPos.x = 2 * sin(glfwGetTime()/2);
		lightPos.z = 2 * cos(glfwGetTime()/2);*/
		shader.setUniform("lightPos", lightPos);
	}

	void changeColor(glm::vec3 color){
		this->color = color;
	}

private:
	glm::vec3 color;

	const char* simpleTextureVertexShaderSource = R"r(
			#version 330 core
			layout (location = 0) in vec3 ipos;
			layout (location = 1) in vec3 inormal;
			out vec3 normal, fragPos;
			uniform mat4 camera, model;
			void main(){
				gl_Position = camera * vec4(ipos, 1.0);
				fragPos = vec3(model * vec4(ipos, 1.0));
				normal = vec3(model * vec4(inormal, 1.0));
			}
		)r";

	const char* simpleTextureFragmentShaderSource = R"r(
			#version 330 core
			out vec4 FragColor;
			in vec3 normal, fragPos;
			uniform vec3 col;
			uniform vec3 lightPos, viewPos;
			void main(){
				float specularStrength = 0.5f;
				vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
				vec3 ambient = lightColor * 0.1f;

				vec3 norm = normalize(normal);
				vec3 lightDirection = normalize(lightPos - fragPos);
				vec3 diffuse = lightColor * max(dot(lightDirection, norm), 0.0);
				vec3 viewDir = normalize(viewPos - fragPos);
				vec3 halfwayDir = normalize(lightDirection + viewDir);
				float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 32);
				vec3 specular = specularStrength * spec * lightColor;
				
				vec3 result = (ambient + diffuse + specular) * col;
				FragColor = vec4(result, 1.0);
			}
		)r";
};