#include "Controls.h"
#include "Input.h"
#include "Camera.h"

Controls::Controls()
{
}

Controls::~Controls()
{
}

void Controls::cameraControls(Input &input, Camera &camera, float deltaTime)
{
	float deltaCamSpeed = cameraMovSpeed * deltaTime;

	cameraMovementVec.x = 0.0f;
	cameraMovementVec.y = 0.0f;
	cameraMovementVec.z = 0.0f;

	if (input.isKeyHeld(SDL_SCANCODE_LSHIFT) == true)
	{
		deltaCamSpeed = (cameraMovSpeed * deltaTime) * cameraShiftIncreaseSpeed;
	}

	if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true || input.isKeyHeld(SDL_SCANCODE_A) == true)
	{
		cameraMovementVec.z -= deltaCamSpeed;
	}

	if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true || input.isKeyHeld(SDL_SCANCODE_D) == true)
	{
		cameraMovementVec.z += deltaCamSpeed;
	}

	if (input.isKeyHeld(SDL_SCANCODE_UP) == true || input.isKeyHeld(SDL_SCANCODE_W) == true)
	{
		cameraMovementVec.x += deltaCamSpeed;
	}

	if (input.isKeyHeld(SDL_SCANCODE_DOWN) == true || input.isKeyHeld(SDL_SCANCODE_S) == true)
	{
		cameraMovementVec.x -= deltaCamSpeed;
	}

	if (input.isKeyHeld(SDL_SCANCODE_LCTRL) == true)
	{
		cameraMovementVec.y -= deltaCamSpeed;
	}

	if (input.isKeyHeld(SDL_SCANCODE_SPACE) == true)
	{
		cameraMovementVec.y += deltaCamSpeed;
	}

	camera.Strafe(cameraMovementVec, 1.0f);
}