#pragma once

#include "Base.h"
#include "IComponentVisual.h"
#include "Mesh.h"
#include "Material.h"

class MeshRenderer : public IComponentVisual
{
public:
	// List of all materials present on the mesh
	std::vector<Material> materials;
	// Mesh containing all vertices, normals, uvs etc.
	Mesh* mesh;
	void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition = glm::vec3(0)) override;
};