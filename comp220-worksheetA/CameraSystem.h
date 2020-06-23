#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "System.h"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Coordinator.h"
#include "Transform.h"
#include "CameraComponent.h"


class CameraSystem : public System
{
public:
	void SetView(CameraComponent cam);
	void SetProjection(CameraComponent cam, float fov, float aspectWidth, float aspectHeight, float nearClip, float farClip);
	void SetProjection(CameraComponent cam);
	void SendCameraData(std::unique_ptr<Coordinator>& coord, GLint _view, GLint _projection);
	void UpdateCameraPosition(std::unique_ptr<Coordinator>& coord);

private:

protected:

};