#include "MeshRenderer.h"

void MeshRenderer::Render(Camera* visibleFromCamera)
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

	if (!visibleFromCamera)
	{
		printf("No camera used to render Mesh Renderer\n");
		return;
	}

	// Use material
	materials[0].Use(transform->GetTransformation(), visibleFromCamera->GetViewMatrix(glm::vec3(0, 0, 10)), visibleFromCamera->GetProjectionMatrix());

	// Use mesh
	mesh->Use();
}
