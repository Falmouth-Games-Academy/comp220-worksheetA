#include "Model.h"

bool loadModelFromFile(const std::string& filename, GLuint VBO, GLuint EBO, unsigned int& numberOfVertices, unsigned int& numberOfIndices)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Assimp::Importer importer;

	// Load in a model
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords | aiProcess_CalcTangentSpace);

	// Check if the model has loaded
	if (scene == nullptr)
	{
		printf("Error loading model %s", importer.GetErrorString());
		return false;
	}

	for (int n = 0; n < scene->mNumMeshes; n++)
	{
		aiMesh* currentMesh = scene->mMeshes[n];

		for (unsigned int v = 0; v < currentMesh->mNumVertices; v++)
		{
			aiVector3D currentModelVertex = currentMesh->mVertices[v];
			aiColor4D currentModelColour = aiColor4D(1.0, 1.0, 1.0, 1.0);
			aiVector3D currentTextureCoordinates = aiVector3D(0.0f, 0.0f, 0.0f);
			aiVector3D currentNormals = aiVector3D(0.0f, 0.0f, 0.0f);

			if (currentMesh->HasVertexColors(0))
			{
				currentModelColour = currentMesh->mColors[0][v];
			}

			if (currentMesh->HasTextureCoords(0))
			{
				currentTextureCoordinates = currentMesh->mTextureCoords[0][v];
			}

			if (currentMesh->HasNormals())
			{
				currentNormals = currentMesh->mNormals[v];
			}

			Vertex currentVertex = { 
				currentModelVertex.x, currentModelVertex.y, currentModelVertex.z,
				currentModelColour.r, currentModelColour.g, currentModelColour.b, currentModelColour.a,
				currentTextureCoordinates.x, currentTextureCoordinates.y,
				currentNormals.x, currentNormals.y, currentNormals.z 
			};

			vertices.push_back(currentVertex);
		}

		for (int f = 0; f < currentMesh->mNumFaces; f++)
		{
			aiFace currentModelFace = currentMesh->mFaces[f];
			indices.push_back(currentModelFace.mIndices[0]);
			indices.push_back(currentModelFace.mIndices[1]);
			indices.push_back(currentModelFace.mIndices[2]);
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

bool loadMeshesFromFile(const std::string& filename, MeshCollection * meshes)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Assimp::Importer importer;

	// Load in a model
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords | aiProcess_CalcTangentSpace);

	// Check if the model has loaded
	if (scene == nullptr)
	{
		printf("Error loading model %s", importer.GetErrorString());
		return false;
	}

	for (unsigned int n = 0; n < scene->mNumMeshes; n++)
	{
		aiMesh* currentMesh = scene->mMeshes[n];

		Mesh *pMesh = new Mesh();
		pMesh->Init();
		
		for (int v = 0; v < currentMesh->mNumVertices; v++)
		{
			aiVector3D currentModelVertex = currentMesh->mVertices[v];
			aiColor4D currentModelColour = aiColor4D(1.0, 1.0, 1.0, 1.0);
			aiVector3D currentTextureCoordinates = aiVector3D(0.0f, 0.0f, 0.0f);
			aiVector3D currentNormals = aiVector3D(0.0f, 0.0f, 0.0f);

			if (currentMesh->HasVertexColors(0))
			{
				currentModelColour = currentMesh->mColors[0][v];
			}

			if (currentMesh->HasTextureCoords(0))
			{
				currentTextureCoordinates = currentMesh->mTextureCoords[0][v];
			}

			if (currentMesh->HasNormals())
			{
				currentNormals = currentMesh->mNormals[v];
			}

			Vertex currentVertex = { currentModelVertex.x,currentModelVertex.y,currentModelVertex.z,
				currentModelColour.r,currentModelColour.g,currentModelColour.b,currentModelColour.a,
				currentTextureCoordinates.x,currentTextureCoordinates.y,
				currentNormals.x, currentNormals.y, currentNormals.z
			};

			vertices.push_back(currentVertex);
		}

		for (int f = 0; f < currentMesh->mNumFaces; f++)
		{
			aiFace currentModelFace = currentMesh->mFaces[f];
			indices.push_back(currentModelFace.mIndices[0]);
			indices.push_back(currentModelFace.mIndices[1]);
			indices.push_back(currentModelFace.mIndices[2]);
		}

		pMesh->CopyBufferData(vertices.data(), vertices.size(), indices.data(), indices.size());

		meshes->addMesh(pMesh);
		vertices.clear();
		indices.clear();
	}

	return true;
}
