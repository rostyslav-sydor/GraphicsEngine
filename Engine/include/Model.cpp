#include <Model.hpp>

Model::Model(std::string filename, std::shared_ptr<Material> material) {
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(filename, aiProcess_GenNormals | aiProcess_Triangulate);

	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
		std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		std::exit(1);
	}
	transformation = std::make_shared<Transformation>();
	processNode(scene->mRootNode, scene, {}, transformation, material);
}

void Model::Translate(float x, float y, float z) { (*transformation).Translate(x, y, z); }
void Model::Rotate(float angle, float x, float y, float z) { (*transformation).Rotate(angle, x, y, z); }
void Model::Scale(float x, float y, float z) { (*transformation).Scale(x, y, z); }

void Model::setTranslation(float x, float y, float z) { (*transformation).setTranslation(x, y, z); }
void Model::setRotation(float angle, float x, float y, float z) { (*transformation).setRotation(angle, x, y, z); }
void Model::setScale(float x, float y, float z) { (*transformation).setScale(x, y, z); }

void Model::processNode(aiNode* node, const aiScene* scene, const aiMatrix4x4& aiParentTransform, std::shared_ptr<Transformation> parentTransform, std::shared_ptr<Material> material) {
	
	auto aiTransform = aiParentTransform * node->mTransformation;
	auto thisTransform = std::make_shared<Transformation>();
	thisTransform->setParent(parentTransform);
		
	
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene, aiTransform, thisTransform, material));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, aiTransform, thisTransform, material);
	}
}

GraphicObject Model::processMesh(	aiMesh* mesh,
									const aiScene* scene,
									const aiMatrix4x4& aiParentTransform,
									std::shared_ptr<Transformation> parentTransform,
									std::shared_ptr<Material> material) {

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex v;
		aiVector3D transformedVec = aiParentTransform * mesh->mVertices[i];
		//aiVector3D transformedVec = mesh->mVertices[i];
		v.pos = glm::vec3(transformedVec.x, transformedVec.y, transformedVec.z);
		if (mesh->HasNormals()) {
			aiVector3D transformedNorm = aiParentTransform * mesh->mNormals[i];
			v.normal = glm::normalize(glm::vec3(transformedNorm.x, transformedNorm.y, transformedNorm.z));
		}
		else
			v.normal = glm::vec3(0);

		if (mesh->mTextureCoords[0])
			v.texture = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		else
			v.texture = glm::vec2(0);

		vertices.emplace_back(v);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}

	auto center = glm::vec3{ aiParentTransform.a4, aiParentTransform.b4, aiParentTransform.c4 };

	auto newMesh =  std::make_shared<Geometry>(vertices, indices, center);

	auto thisTransform = std::make_shared<Transformation>();
	thisTransform->setParent(parentTransform);
	std::cout << vertices.size() << std::endl;
	return GraphicObject{material, newMesh, thisTransform};
}
