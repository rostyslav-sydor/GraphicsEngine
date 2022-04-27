#pragma once
#include <Mesh.hpp>
#include <Transformation.hpp>
#include <Camera.hpp>

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
	Model(std::string filename, Transformation transformation = {});
	Model(Mesh mesh, Transformation transformation = {});

	void Render() const;
	
	glm::mat4 getTransformation() const;
	
	void Translate(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float x, float y, float z);

	void setTranslation(float x, float y, float z);
	void setRotation(float angle, float x, float y, float z);
	void setScale(float x, float y, float z);

	void setParent(const Model* model);


	Transformation transformation;
private:
	void processNode(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 parentTransform);

	std::vector<Mesh> meshes;
	
	const Model* parent;
};