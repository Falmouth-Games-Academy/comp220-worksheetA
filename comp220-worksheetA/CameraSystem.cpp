#include "CameraSystem.h"

void CameraSystem::SetView(CameraComponent* cam)
{
	glm::vec3 pos = glm::vec3(cam->x, cam->y, cam->z);
	glm::vec3 look = glm::vec3(cam->lookX, cam->lookY, cam->lookZ);
	glm::vec3 camUp = glm::vec3(cam->upX, cam->upY, cam->upZ);
	glm::mat4 view = glm::lookAt(pos, look, camUp);
	const float* source = (const float*)glm::value_ptr(view);
	for (int i = 0; i < 16; i++)
	{
		cam->view[i] = source[i];
	}
}

void CameraSystem::SetProjection(CameraComponent* cam, float fov, float aspectWidth, float aspectHeight, float nearClip, float farClip)
{
	glm::mat4 projection = glm::perspective(glm::radians(fov), aspectWidth / aspectHeight, nearClip, farClip);
	const float* source = (const float*)glm::value_ptr(projection);
	for (int i = 0; i < 16; i++)
	{
		cam->projection[i] = source[i];
	}
}

void CameraSystem::SetProjection(CameraComponent* cam)
{
	glm::mat4 projection = glm::perspective(glm::radians(cam->fov), cam->aspectWidth / cam->aspectHeight, cam->nearClip, cam->farClip);
	const float* source = (const float*)glm::value_ptr(projection);
	for (int i = 0; i < 16; i++)
	{
		cam->projection[i] = source[i];
	}
}

void CameraSystem::SendCameraData(Coordinator* coord, GLint _view, GLint _projection)
{
	for (Entity ent : sy_Entities)
	{
		CameraComponent& cam = coord->GetComponent<CameraComponent>(ent);
		glm::mat4 view = glm::make_mat4(cam.view);
		glm::mat4 projection = glm::make_mat4(cam.projection);

		//glUniformMatrix4fv(_view, 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(_projection, 1, GL_FALSE, glm::value_ptr(projection));
	}
}

void CameraSystem::UpdateCameraPosition(Coordinator* coord)
{
	for (Entity ent : sy_Entities)
	{
		CameraComponent* cam = coord->GetComponentPtr<CameraComponent>(ent);
		Transform* transform = coord->GetComponentPtr<Transform>(ent);
		cam->x += transform->x;
		cam->y += transform->y;
		cam->z += transform->z;
		SetView(cam);
		SetProjection(cam);
	}
}