#include "MeshSystem.h"

void MeshSystem::Init(Coordinator coord)
{
	for (int ent : sy_Entities)
	{
		MeshComponent mc_mesh = coord.GetComponent<MeshComponent>(ent);

		glGenVertexArrays(1, &mc_mesh.m_VAO);
		glBindVertexArray(mc_mesh.m_VAO);

		glGenBuffers(1, &mc_mesh.m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, mc_mesh.m_VBO);
		glGenBuffers(1, &mc_mesh.m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mc_mesh.m_EBO);
	}
}
void MeshSystem::Init(MeshComponent mc_mesh)
{
	glGenVertexArrays(1, &mc_mesh.m_VAO);
	glBindVertexArray(mc_mesh.m_VAO);

	glGenBuffers(1, &mc_mesh.m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, mc_mesh.m_VBO);
	glGenBuffers(1, &mc_mesh.m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mc_mesh.m_EBO);
}

void MeshSystem::CopyBufferData(MeshComponent mc_mesh, Vertex* pVerts, unsigned int numberOfVerts, unsigned int *pIndices, unsigned int numberOfIndices)
{

}

void MeshSystem::Render(Coordinator* coord)
{
	for (Entity ent : sy_Entities)
	{
		MeshCollectionComponent* meshCollection = coord->GetComponentPtr<MeshCollectionComponent>(ent);
		for (MeshComponent &mesh : meshCollection->mcc_meshCollection)
		{
			//CopyBufferData(mesh, mesh.m_verts.data(), mesh.m_verts.size(), mesh.m_indices.data(), mesh.m_indices.size());
			glBindBuffer(GL_ARRAY_BUFFER, mesh.m_EBO);
			//glBufferData(GL_ARRAY_BUFFER, numberOfVerts * sizeof(Vertex), pVerts, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(12 * sizeof(float)));
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(15 * sizeof(float)));
			glDrawElements(GL_TRIANGLES, mesh.m_numberOfIndices, GL_UNSIGNED_INT, (void*)0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(3);
			glDisableVertexAttribArray(4);
			glDisableVertexAttribArray(5);
		}
	}
}

void MeshSystem::Destroy(Coordinator coord)
{

}

Vertex MeshSystem::LoadMeshVertex(aiMesh* _mesh, int index)
{

		aiVector3D currentVert = _mesh->mVertices[index];
		aiColor4D currentColour = aiColor4D(1.0, 1.0, 1.0, 1.0);
		aiVector3D currentTextureCoords = aiVector3D(0.0f, 0.0f, 0.0f);
		aiVector3D currentNormals = aiVector3D(0.0f, 0.0f, 0.0f);
		aiVector3D currentTangents = aiVector3D(0.0f, 0.0f, 0.0f);
		aiVector3D currentBiTangents = aiVector3D(0.0f, 0.0f, 0.0f);

		if (_mesh->HasVertexColors(0))
			currentColour = _mesh->mColors[0][index];
		if (_mesh->HasTextureCoords(0))
			currentTextureCoords = _mesh->mTextureCoords[0][index];
		if (_mesh->HasNormals())
			currentNormals = _mesh->mNormals[index];
		if (_mesh->HasTangentsAndBitangents())
		{
			currentTangents = _mesh->mTangents[index];
			currentBiTangents = _mesh->mBitangents[index];
		}
		Vertex currentVertex;
		currentVertex.Init(
			currentVert.x, currentVert.y, currentVert.z,
			currentColour.r, currentColour.g, currentColour.b, currentColour.a,
			currentTextureCoords.x, currentTextureCoords.y,
			currentNormals.x, currentNormals.y, currentNormals.z,
			currentTangents.x, currentTangents.y, currentTangents.z,
			currentBiTangents.x, currentBiTangents.y, currentBiTangents.z
		);
		return currentVertex;
}

void MeshSystem::LoadMeshIndices(aiMesh* _mesh, std::vector<unsigned int> _ind)
{
	for (int f = 0; f < _mesh->mNumFaces; f++)
	{
		aiFace currentModelFace = _mesh->mFaces[f];
		_ind.push_back(currentModelFace.mIndices[0]);
		_ind.push_back(currentModelFace.mIndices[1]);
		_ind.push_back(currentModelFace.mIndices[2]);
	}
}

void MeshSystem::Update(Coordinator* coord)
{
	for (auto const& ent : sy_Entities)
	{
		MeshCollectionComponent* mcc = coord->GetComponentPtr<MeshCollectionComponent>(ent);
		Transform* transform = coord->GetComponentPtr<Transform>(ent);
		for (MeshComponent &mesh : mcc->mcc_meshCollection)
		{
			glm::mat4 translation = glm::translate(glm::vec3(transform->x, transform->y, transform->z));
			glm::mat4 rotation = glm::rotate(transform->qX, glm::vec3(1.0f, 0.0f, 0.0f))
				* glm::rotate(transform->qY, glm::vec3(0.0f, 1.0f, 0.0f))
				* glm::rotate(transform->qZ, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 scale = glm::scale(glm::vec3(transform->sX, transform->sY, transform->sZ));

			glm::mat4 model = translation * rotation * scale;

			const float* tranSource = (const float*)glm::value_ptr(translation);
			const float* rotSource = (const float*)glm::value_ptr(rotation);
			const float* scaleSource = (const float*)glm::value_ptr(scale);
			const float* modSource = (const float*)glm::value_ptr(model);

			for (int i = 0; i < 16; i++)
			{
				mesh.translationMatrix[i] = tranSource[i];
				mesh.rotationMatrix[i] = rotSource[i];
				mesh.scaleMatrix[i] = scaleSource[i];
				mesh.modelMatrix[i] = modSource[i];
			}
		}
	}
}

bool MeshSystem::LoadModelFromFile(const std::string& _filename, GLuint _VBO, GLuint _EBO, unsigned int& _verts, unsigned int& _indices)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(_filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords | aiProcess_CalcTangentSpace);
	if (!scene)
	{
		printf("Model Loading Error - %s\n", importer.GetErrorString());
		return false;
	}

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		for (int v = 0; v < scene->mMeshes[i]->mNumVertices; v++)
		{
			vertices.push_back(LoadMeshVertex(scene->mMeshes[i], v));
			LoadMeshIndices(scene->mMeshes[i], indices);
		}
	}

	_verts = vertices.size();
	_indices = indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _verts * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	return true;
}

std::vector<MeshComponent> MeshSystem::LoadMeshCollectionFromFile(const std::string& filename)
{
	std::vector<Vertex> verts;
	std::vector<unsigned int> ind;
	std::vector<MeshComponent> meshCollection;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords | aiProcess_CalcTangentSpace);

	if (!scene)
	{
		printf("Model Loading Error - %s\n", importer.GetErrorString());
		return meshCollection;
	}

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* currentMesh = scene->mMeshes[i];
		MeshComponent* mc_mesh = new MeshComponent();
		//mc_mesh->Init(0, 0, 0, 0, 0);
		Init(*mc_mesh);
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			for (int v = 0; v < scene->mMeshes[i]->mNumVertices; v++)
			{
				verts.push_back(LoadMeshVertex(scene->mMeshes[i], v));
			}
			for (int f = 0; f < scene->mMeshes[i]->mNumFaces; f++)
			{
				aiFace currentModelFace = scene->mMeshes[i]->mFaces[f];
				ind.push_back(currentModelFace.mIndices[0]);
				ind.push_back(currentModelFace.mIndices[1]);
				ind.push_back(currentModelFace.mIndices[2]);
			}
		}
		//LoadMeshIndices(scene->mMeshes[i], ind);
		mc_mesh->m_numberOfIndices = ind.size();
		mc_mesh->m_numberOfVerts = verts.size();
		mc_mesh->m_verts = verts;
		mc_mesh->m_indices = ind;

		verts.clear();
		ind.clear();

		glGenVertexArrays(1, &mc_mesh->m_VAO);
		glBindVertexArray(mc_mesh->m_VAO);

		glGenBuffers(1, &mc_mesh->m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, mc_mesh->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, mc_mesh->m_verts.size() * sizeof(Vertex), mc_mesh->m_verts.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &mc_mesh->m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mc_mesh->m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mc_mesh->m_indices.size() * sizeof(unsigned int), mc_mesh->m_indices.data(), GL_STATIC_DRAW);
		meshCollection.push_back(*mc_mesh);
	}
	return meshCollection;
}

