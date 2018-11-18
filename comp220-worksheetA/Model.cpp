#include "Model.h"

bool loadModelFromFile(const std::string &filename, GLuint VBO, GLuint EBO, unsigned int & numberofVerts, unsigned int & numberofInfices)
{
	// Allows it it import files into its own scene format
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipUVs);

	// Check for error
	if (scene == nullptr)
	{
		printf("Error Loading model %s", importer.GetErrorString());
		return false;
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Loop throiugh meshes
	for (unsigned int m = 0; m < scene->mNumMeshes; m++)
	{
		// Const as not editing the mesh
		const aiMesh* currentAIMesh = scene->mMeshes[m];

		// Loop through verticies within the current mesh
		for (unsigned int v = 0; v < currentAIMesh->mNumVertices; v++)
		{
			const aiVector3D currentAIPosition = currentAIMesh->mVertices[v];
			
			// Can be done in one line, this is for clarity
			Vertex ourVertex;
			ourVertex.x = currentAIPosition.x;
			ourVertex.y = currentAIPosition.y;
			// Colour
			ourVertex.r = 1.0f; ourVertex.g = 1.0f; ourVertex.b = 1.0f; ourVertex.a = 1.0f;
			// Remove garbage values
			ourVertex.tu = 0.0f; ourVertex.tv = 0.0f;
			ourVertex.z = currentAIPosition.z;

			// Set texture coords to 0, 0 if none otherwise use them
			if (currentAIMesh->HasTextureCoords(0))
			{
				// Current texture coords of vertex
				const aiVector3D currentTextureCoords = currentAIMesh->mTextureCoords[0][v];
				// Set texture coords
				ourVertex.tu = currentTextureCoords.x;
				ourVertex.tv = currentTextureCoords.y;
			}
			// Set colour if one exists for the current vertex
			if (currentAIMesh->HasVertexColors(0))
			{
				// Current colour of vertex
				const aiColor4D currentColour = currentAIMesh->mColors[0][v];
				// Set colour
				ourVertex.r = currentColour.r;
				ourVertex.g = currentColour.g;
				ourVertex.b = currentColour.b;
				ourVertex.a = currentColour.a;
			}

			// Add the ourVertex to vertices
			vertices.push_back(ourVertex);
		}

		// Loop through faces
		for (unsigned int f = 0; f < currentAIMesh->mNumFaces; f++)
		{
			const aiFace currentFace = currentAIMesh->mFaces[f];

			// Add indices
			indices.push_back(currentFace.mIndices[0]);
			indices.push_back(currentFace.mIndices[1]);
			indices.push_back(currentFace.mIndices[2]);
		}
	}

	numberofVerts = vertices.size();
	numberofInfices = indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, numberofVerts * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberofInfices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	return true;
}

// Should refactor as it contains repeated code as function above
bool loadMeshesFromFile(const std::string & filename, std::vector<Mesh*>& meshes)
{
	// Allows it it import files into its own scene format
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipUVs);

	// Check for error
	if (scene == nullptr)
	{
		printf("Error Loading model %s", importer.GetErrorString());
		return false;
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Loop throiugh meshes
	for (unsigned int m = 0; m < scene->mNumMeshes; m++)
	{
		// Const as not editing the mesh
		const aiMesh* currentAIMesh = scene->mMeshes[m];

		// Create and initalise a mesh
		Mesh * ourCurrentMesh = new Mesh();
		ourCurrentMesh->init();

		// Loop through verticies within the current mesh
		for (unsigned int v = 0; v < currentAIMesh->mNumVertices; v++)
		{
			const aiVector3D currentAIPosition = currentAIMesh->mVertices[v];

			// Can be done in one line, this is for clarity
			Vertex ourVertex;
			ourVertex.x = currentAIPosition.x;
			ourVertex.y = currentAIPosition.y;
			// Colour
			ourVertex.r = 1.0f; ourVertex.g = 1.0f; ourVertex.b = 1.0f; ourVertex.a = 1.0f;
			// Remove garbage values
			ourVertex.tu = 0.0f; ourVertex.tv = 0.0f;
			ourVertex.z = currentAIPosition.z;

			// Set texture coords to 0, 0 if none otherwise use them
			if (currentAIMesh->HasTextureCoords(0))
			{
				// Current texture coords of vertex
				const aiVector3D currentTextureCoords = currentAIMesh->mTextureCoords[0][v];
				// Set texture coords
				ourVertex.tu = currentTextureCoords.x;
				ourVertex.tv = currentTextureCoords.y;
			}
			// Set colour if one exists for the current vertex
			if (currentAIMesh->HasVertexColors(0))
			{
				// Current colour of vertex
				const aiColor4D currentColour = currentAIMesh->mColors[0][v];
				// Set colour
				ourVertex.r = currentColour.r;
				ourVertex.g = currentColour.g;
				ourVertex.b = currentColour.b;
				ourVertex.a = currentColour.a;
			}

			// Add the ourVertex to vertices
			vertices.push_back(ourVertex);
		}

		// Loop through faces
		for (unsigned int f = 0; f < currentAIMesh->mNumFaces; f++)
		{
			const aiFace currentFace = currentAIMesh->mFaces[f];

			// Add indices
			indices.push_back(currentFace.mIndices[0]);
			indices.push_back(currentFace.mIndices[1]);
			indices.push_back(currentFace.mIndices[2]);
		}

		ourCurrentMesh->copyMeshData(vertices, indices);
		meshes.push_back(ourCurrentMesh);

		vertices.clear();
		indices.clear();
	}
	return true;
}
