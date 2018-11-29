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
		const aiMesh* currentMesh = scene->mMeshes[m];

		// Loop through verticies within the current mesh
		for (unsigned int v = 0; v < currentMesh->mNumVertices; v++)
		{
			//const aiVector3D currentAIPosition = currentMesh->mVertices[v];

			aiVector3D currentModelVertex = currentMesh->mVertices[v];
			aiColor4D currentModelColour = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
			aiVector3D currentTextureCoordinates = aiVector3D(0.0f, 0.0f, 0.0f);
			aiVector3D currentNormals = aiVector3D(0.0f, 0.0f, 0.0f);

			// Set texture coords to 0, 0 if none otherwise use them
			if (currentMesh->HasTextureCoords(0))
			{
				// Current texture coords of vertex
				const aiVector3D currentTextureCoords = currentMesh->mTextureCoords[0][v];
			}
			// Set colour if one exists for the current vertex
			if (currentMesh->HasVertexColors(0))
			{
				// Current colour of vertex
				const aiColor4D currentColour = currentMesh->mColors[0][v];
			}
			if (currentMesh->HasNormals())
			{
				currentNormals = currentMesh->mNormals[v];
			}

			Vertex currentVertex = { 
				currentModelVertex.x, currentModelVertex.y, currentModelVertex.z,						// Vertex (xyz)
				currentModelColour.r, currentModelColour.g, currentModelColour.b, currentModelColour.a, // Colour (rgba)
				currentTextureCoordinates.x, currentTextureCoordinates.y,								// Texture (xy)
				currentNormals.x, currentNormals.y, currentNormals.z									// Normals (xyz)
			};

			// Add the ourVertex to vertices
			vertices.push_back(currentVertex);
		}

		// Loop through faces
		for (unsigned int f = 0; f < currentMesh->mNumFaces; f++)
		{
			const aiFace currentFace = currentMesh->mFaces[f];

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

bool loadMeshFromFile(const std::string & filename, MeshCollection * pMeshCollection)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords | aiProcess_CalcTangentSpace);

	if (!scene)
	{
		printf("Model Loading Error - %s\n", importer.GetErrorString());
		return false;
	}

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh *currentMesh = scene->mMeshes[i];
		Mesh *pMesh = new Mesh();
		pMesh->init();

		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh *currentMesh = scene->mMeshes[i];

			for (int v = 0; v < currentMesh->mNumVertices; v++)
			{
				aiVector3D currentModelVertex = currentMesh->mVertices[v];
				aiColor4D currentModelColour = aiColor4D(1.0, 1.0, 1.0, 1.0);
				aiVector3D currentTextureCoordinates = aiVector3D(0.0f, 0.0f, 0.0f);
				aiVector3D currentModelNormals = aiVector3D(0.0f, 0.0f, 0.0f);
				aiVector3D currentModelTangents = aiVector3D(0.0f, 0.0f, 0.0f);
				aiVector3D currentModelBitangents = aiVector3D(0.0f, 0.0f, 0.0f);

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
					currentModelNormals = currentMesh->mNormals[v];
				}
				if (currentMesh->HasTangentsAndBitangents())
				{
					currentModelTangents = currentMesh->mTangents[v];
					currentModelBitangents = currentMesh->mBitangents[v];
				}

				Vertex currentVertex = { 
					currentModelVertex.x,currentModelVertex.y,currentModelVertex.z,							// Position XYZ
					currentModelColour.r,currentModelColour.g,currentModelColour.b,currentModelColour.a,	// Colour RGBA
					currentTextureCoordinates.x,currentTextureCoordinates.y,								// Texture coordinates XY
					currentModelNormals.x,currentModelNormals.y,currentModelNormals.z,						// Normals XYZ
					currentModelTangents.x,currentModelTangents.y,currentModelTangents.z,					// Tangents XYZ
					currentModelBitangents.x,currentModelBitangents.y,currentModelBitangents.z				// BitTangents XYZ
				};

				vertices.push_back(currentVertex);
			}
		}

		for (int f = 0; f < currentMesh->mNumFaces; f++)
		{
			aiFace currentModelFace = currentMesh->mFaces[f];
			indices.push_back(currentModelFace.mIndices[0]);
			indices.push_back(currentModelFace.mIndices[1]);
			indices.push_back(currentModelFace.mIndices[2]);
		}

		pMesh->copyBufferData(vertices.data(), vertices.size(), indices.data(), indices.size());

		pMeshCollection->addMesh(pMesh);
		vertices.clear();
		indices.clear();
	}

	return true;
}
