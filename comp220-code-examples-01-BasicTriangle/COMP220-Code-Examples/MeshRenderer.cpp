#include "MeshRenderer.h"

void MeshRenderer::Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	if (materials.size() == 0)
	{
		printf("No material assigned to Mesh Renderer\n");
		return;
	}

	if (mesh == nullptr)
	{
		printf("No mesh assigned to Mesh Renderer\n");
		return;
	}

	if (owner == nullptr)
	{
		printf("No owner assigned to Mesh Renderer\n");
		return;
	}

	if (transform == nullptr)
	{
		printf("No Transform assigned to Mesh Renderer\n");
		return;
	}

	// Use material
	materials[0].Use(transform->GetTransformation(), viewMatrix, projectionMatrix);

	// Use mesh
	mesh->Use();
}
