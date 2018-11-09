#include "Model.h"

bool loadModelFromFile(const std::string& filename, GLuint VBO, GLuint EBO, unsigned int& numberOfVertices, unsigned int& numberOfIndices)
{
	Assimp::Importer importer;

	// Load in a model
	const aiScene* scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipUVs);

	// Check if the model has loaded
	if (scene == nullptr)
	{
		printf("Error loading model %s", importer.GetErrorString());
		return false;
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int n = 0; n < scene->mNumMeshes; n++)
	{
		const aiMesh* currentAIMesh = scene->mMeshes[n];
		for (unsigned int v = 0; v < currentAIMesh->mNumVertices; v++)
		{
			const aiVector3D currentAIPosition = currentAIMesh->mVertices[v];

			Vertex ourVertex;
			ourVertex.x = currentAIPosition.x;
			ourVertex.y = currentAIPosition.y;
			ourVertex.z = currentAIPosition.z;

			ourVertex.r = 1.0f;
			ourVertex.g = 1.0f;
			ourVertex.b = 1.0f;
			ourVertex.a = 1.0f;

			ourVertex.tu = 0;
			ourVertex.tv = 0;

			if (currentAIMesh->HasTextureCoords(0))
			{
				const aiVector3D currentTextureCoords = currentAIMesh->mTextureCoords[0][v];
				ourVertex.tu = currentTextureCoords.x;
				ourVertex.tv = currentTextureCoords.y;
			}
			if (currentAIMesh->HasVertexColors(0))
			{
				const aiColor4D currentColor = currentAIMesh->mColors[0][v];
				ourVertex.r = currentColor.r;
				ourVertex.g = currentColor.g;
				ourVertex.b = currentColor.b;
				ourVertex.a = currentColor.a;
			}

			vertices.push_back(ourVertex);
		}

		for (unsigned int f = 0; f < currentAIMesh->mNumFaces; f++)
		{
			const aiFace currentFace = currentAIMesh->mFaces[f];
			
			indices.push_back(currentFace.mIndices[0]);
			indices.push_back(currentFace.mIndices[1]);
			indices.push_back(currentFace.mIndices[2]);
		}
	}

	numberOfVertices = vertices.size();
	numberOfIndices = indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	return true;
}

bool loadMeshesFromFile(const std::string & filename, std::vector<Mesh*>& meshes)
{
	Assimp::Importer importer;

	// Load in a model
	const aiScene* scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipUVs);

	// Check if the model has loaded
	if (scene == nullptr)
	{
		printf("Error loading model %s", importer.GetErrorString());
		return false;
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int n = 0; n < scene->mNumMeshes; n++)
	{
		const aiMesh* currentAIMesh = scene->mMeshes[n];

		Mesh* ourCurrentMesh = new Mesh();
		ourCurrentMesh->Init();
		
		for (unsigned int v = 0; v < currentAIMesh->mNumVertices; v++)
		{
			const aiVector3D currentAIPosition = currentAIMesh->mVertices[v];

			Vertex ourVertex;
			ourVertex.x = currentAIPosition.x;
			ourVertex.y = currentAIPosition.y;
			ourVertex.z = currentAIPosition.z;

			ourVertex.r = 1.0f;
			ourVertex.g = 1.0f;
			ourVertex.b = 1.0f;
			ourVertex.a = 1.0f;

			ourVertex.tu = 0;
			ourVertex.tv = 0;

			if (currentAIMesh->HasTextureCoords(0))
			{
				const aiVector3D currentTextureCoords = currentAIMesh->mTextureCoords[0][v];
				ourVertex.tu = currentTextureCoords.x;
				ourVertex.tv = currentTextureCoords.y;
			}
			if (currentAIMesh->HasVertexColors(0))
			{
				const aiColor4D currentColor = currentAIMesh->mColors[0][v];
				ourVertex.r = currentColor.r;
				ourVertex.g = currentColor.g;
				ourVertex.b = currentColor.b;
				ourVertex.a = currentColor.a;
			}

			vertices.push_back(ourVertex);
		}

		for (unsigned int f = 0; f < currentAIMesh->mNumFaces; f++)
		{
			const aiFace currentFace = currentAIMesh->mFaces[f];

			indices.push_back(currentFace.mIndices[0]);
			indices.push_back(currentFace.mIndices[1]);
			indices.push_back(currentFace.mIndices[2]);
		}

		ourCurrentMesh->CopyMeshData(vertices, indices);
		meshes.push_back(ourCurrentMesh);	

		vertices.clear();
		indices.clear();
	}

	return true;
}
