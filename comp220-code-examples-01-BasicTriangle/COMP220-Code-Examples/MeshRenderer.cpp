#include "MeshRenderer.h"

void MeshRenderer::Render()
{
	if (materials.size == 0)
	{
		printf("No material assigned to Mesh Renderer");
		return;
	}

	if (mesh == nullptr)
	{
		printf("No mesh assigned to Mesh Renderer");
		return;
	}

	if (transform == nullptr)
	{
		printf("No Transform assigned to Mesh Renderer");
		return;
	}


}
