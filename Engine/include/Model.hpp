#pragma once

#include <GraphicObject.hpp>
#include <Util.hpp>

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model {
public:
	Model(std::string filename, std::shared_ptr<Material> material);
	
	void Translate(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float x, float y, float z);

	void setTranslation(float x, float y, float z);
	void setRotation(float angle, float x, float y, float z);
	void setScale(float x, float y, float z);

	std::vector<GraphicObject> meshes;
private:
	void processNode(aiNode* node, 
					 const aiScene* scene,
					 const aiMatrix4x4& aiParentTransform,
					 std::shared_ptr<Transformation> parentTransform,
					 std::shared_ptr<Material> material);

	GraphicObject processMesh(	aiMesh* mesh,
								const aiScene* scene,
								const aiMatrix4x4& aiParentTransform,
								std::shared_ptr<Transformation> parentTransform,
								std::shared_ptr<Material> material);
	
	std::shared_ptr<Transformation> transformation;
};