#include <Geometry.hpp>

Geometry::Geometry(const std::string& filename) {
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(filename, aiProcess_Triangulate);

	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
		std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		std::exit(1);
	}
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	auto mesh = scene->mMeshes[0];

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex v;

		auto vec = mesh->mVertices[i];
		v.pos = glm::vec3(vec.x, vec.y, vec.z);
		if (mesh->HasNormals()) {
			auto norm = mesh->mNormals[i];
			v.normal = glm::vec3(norm.x, norm.y, norm.z);
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
	numVertices = indices.size();
	setup(vertices, indices, glm::vec3(0));
}

Geometry::Geometry(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, glm::vec3 center): numVertices {static_cast<unsigned int>(indices.size())} {
	setup(vertices, indices, center);
}

void Geometry::setup(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, glm::vec3 center) {
	for (const auto& vertex : vertices) {
		auto dist = center + vertex.pos;
		maxX = std::max(maxX, dist.x);
		maxY = std::max(maxY, dist.y);
		maxZ = std::max(maxZ, dist.z);
		minX = std::min(minX, dist.x);
		minY = std::min(minY, dist.y);
		minZ = std::min(minZ, dist.z);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(2);
}

unsigned int Geometry::getVAO() const {
	return VAO;
}
