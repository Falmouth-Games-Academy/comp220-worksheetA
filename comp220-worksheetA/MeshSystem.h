#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL_opengl.h>

#include "Coordinator.h"
#include "Transform.h"
#include "System.h"
#include "Vertex.h"
#include "MeshComponent.h"
#include "MeshCollectionComponent.h"

class MeshSystem : public System
{
public:
	void Init(Coordinator coord);
	void Init(MeshComponent mc_mesh);
	void CopyBufferData(MeshComponent mc_mesh, Vertex *pVerts, unsigned int numberOfVerts, unsigned int *pIndicies, unsigned int numberOfIndices);
	void Render(std::unique_ptr<Coordinator> &coord);
	void Destroy(Coordinator coord);
	void Update(std::unique_ptr<Coordinator> &coord);
	bool LoadModelFromFile(const std::string& filename, GLuint _VBO, GLuint _EBO, unsigned int& _vertCount, unsigned int& indecesCount);
	std::vector<MeshComponent> LoadMeshCollectionFromFile(const std::string& filename);
	Vertex LoadMeshVertex(aiMesh* _mesh, int index);
	void LoadMeshIndices(aiMesh* _mesh, std::vector<unsigned int> _ind);

private:

protected:

};