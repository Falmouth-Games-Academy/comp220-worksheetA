#include "model.h"
//#include<string>





bool loadModelFromFile(const std::string& filename, GLuint VBO, GLuint EBO, unsigned int& numberOfVerts, unsigned int& numberOfIndices)
{
	
	Assimp::Importer importer;//need to import mesh

	const aiScene* scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Fast|aiProcess_FlipUVs); 

	if (scene == nullptr)
	{
		printf("Error loading model %s",importer.GetErrorString());
		return false; 
	}

	std::vector<Vertex> vertices; 

	std::vector<unsigned int> indices; 

	for (unsigned int m = 0; m < scene->mNumMeshes; m++)
	{
		const aiMesh* currentAIMesh = scene->mMeshes[m];

		for (unsigned int v = 0; v < currentAIMesh->mNumVertices; v++)
		{
			const aiVector3D currentAiPosition = currentAIMesh->mVertices[v];
			
			Vertex ourVertex;
			ourVertex.x = currentAiPosition.x;
			ourVertex.y = currentAiPosition.y;
			ourVertex.z = currentAiPosition.z;

			ourVertex.r = 1.0f; ourVertex.g = 1.0f; ourVertex.b = 1.0f; ourVertex.a = 1.0f;

			ourVertex.tu = 0.0f; 
			ourVertex.tv = 0.0f;

			if (currentAIMesh->HasTextureCoords(0))
			{
				const aiVector3D currenttextureCoords= currentAIMesh->mTextureCoords[0][v];
				ourVertex.tu = currenttextureCoords.x;
				ourVertex.tv = currenttextureCoords.y;
			}
			// could duplicate this call for colors or other elements, but not today!!!


			vertices.push_back(ourVertex);
		}

		

		for (unsigned int f = 0; f < currentAIMesh->mNumFaces; f++)
		{
			const aiFace currentFace = currentAIMesh->mFaces[f];

			indices.push_back(currentFace.mIndices[0]);
			indices.push_back(currentFace.mIndices[1]);
			indices.push_back(currentFace.mIndices[2]);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, numberOfVerts *sizeof(Vertex),vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);


		}
		numberOfVerts = vertices.size();
		numberOfIndices = indices.size();

	}
	return true; 
};




