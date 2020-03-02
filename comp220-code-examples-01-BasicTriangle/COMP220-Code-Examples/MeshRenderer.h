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
	void Render(Camera * visibleFromCamera) override;
};