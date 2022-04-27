#include <Material.hpp>

Material::Material() : shader{}, ambient{ glm::vec3(0.1f) }, diffuse{ glm::vec3(1.0f) }, specular{ glm::vec3(1.0f) }, shininess{ 1 } {}
Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, int shininess) : shader{},
																					ambient{ ambient },
																					diffuse{ diffuse },
																					specular{ specular },
																					shininess{ shininess } {}
Material::Material(const Shader& shader) : shader{ shader }, ambient{ glm::vec3(0.1f) }, diffuse{ glm::vec3(1.0f)}, specular{ glm::vec3(1.0f) }, shininess{ 1 }  {}

void Material::Apply() { glUseProgram(shader.getId()); };