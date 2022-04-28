#include <Model.hpp>

Model::Model(std::string filename, Transformation transformation) : transformation{ transformation }, parent{ nullptr } {
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(filename, aiProcess_Triangulate);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		std::exit(1);
	}
	aiMatrix4x4 identity{};
	processNode(scene->mRootNode, scene, identity);
}

Model::Model(Mesh mesh, Transformation transformtaion) : transformation{ transformation }, parent{ nullptr } { meshes.emplace_back(mesh); }

void Model::Render() const {
	for (auto const& m : meshes) {
		glBindVertexArray(m.getVAO());
		glDrawElements(GL_TRIANGLES, m.numVertices * 3, GL_UNSIGNED_INT, 0);
	}
}

void Model::setParent(const Model* model) {
	parent = model;
}

glm::mat4 Model::getTransformation() const {
	if (parent) std::cout << parent->transformation.translation[3][0] << std::endl;
	return parent ? parent->getTransformation() * transformation.getTransform() : transformation.getTransform();
}

void Model::Translate(float x, float y, float z) { transformation.Translate(x, y, z); }
void Model::Rotate(float angle, float x, float y, float z) { transformation.Rotate(angle, x, y, z); }
void Model::Scale(float x, float y, float z) { transformation.Scale(x, y, z); }

void Model::setTranslation(float x, float y, float z) { transformation.setTranslation(x, y, z); }
void Model::setRotation(float angle, float x, float y, float z) { transformation.setRotation(angle, x, y, z); }
void Model::setScale(float x, float y, float z) { transformation.setScale(x, y, z); }

void Model::processNode(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform) {
	aiMatrix4x4 thisTransform = parentTransform * node->mTransformation;
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene, thisTransform));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, thisTransform);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 parentTransform) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex v;
		aiVector3D transformedVec = parentTransform * mesh->mVertices[i];
		v.pos = glm::vec3(transformedVec.x, transformedVec.y, transformedVec.z);
		if (mesh->HasNormals()) {
			aiVector3D transformedNorm = parentTransform * mesh->mNormals[i];
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

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}
	return Mesh(vertices, indices);
}
