#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

/* Creates a new game object and stores it in the objectList
takes file and texture locations, x,y,z positions, vec3 for scale, and vec3 for the axis to rotate around, and a rotation speed, set speed to 0 for no rotation*/
void ObjectManager::CreateObject(const std::string & fileLocation, const std::string & textureLocation, float posX, float posY, float posZ, glm::vec3 scale, glm::vec3 rotationAxis, float speed, Shader * shader)
{
	MeshCollection * Meshes = new MeshCollection();
	LoadMeshesFromFile(fileLocation, Meshes);

	textureID = LoadTextureFromFile(textureLocation);

	GameObject * GO = new GameObject();
	GO->SetPosition(posX, posY, posZ);
	GO->SetMesh(Meshes);
	GO->SetScale(scale);
	GO->SetRotationAxis(rotationAxis);
	GO->SetRotationSpeed(speed);
	GO->SetShader(shader);
	GO->SetdiffuseTexture(textureID);
	gameObjectList.push_back(GO);
}

/* Creates a new game object and stores it in the objectList
takes file and texture locations, x,y,z positions, vec3 for scale, and vec3 for the axis to rotate around, and a rotation speed, set speed to 0 for no rotation*/
void ObjectManager::CreateLightObject(const std::string & fileLocation, const std::string & textureLocation, float posX, float posY, float posZ, glm::vec3 scale, glm::vec3 rotationAxis, float speed, float scaleFactor, Shader * shader)
{
	MeshCollection * Meshes = new MeshCollection();
	LoadMeshesFromFile(fileLocation, Meshes);

	textureID = LoadTextureFromFile(textureLocation);

	GameObject * GO = new GameObject();
	GO->SetPosition(posX, posY, posZ);
	GO->SetMesh(Meshes);
	GO->SetScale(scale);
	GO->SetRotationAxis(rotationAxis);
	GO->SetRotationSpeed(speed);
	GO->SetScaleFactor(scaleFactor);
	GO->SetIsParticle(true);
	GO->SetWithPlayer(true);
	GO->SetShader(shader);
	GO->SetdiffuseTexture(textureID);
	lightObjectList.push_back(GO);
}

/* Creates a new game object and stores it in the objectList
takes file and texture locations, x,y,z positions, vec3 for scale, and vec3 for the axis to rotate around, and a rotation speed, set speed to 0 for no rotation*/
void ObjectManager::CreateParticleObject(const std::string & fileLocation, const std::string & textureLocation, float posX, float posY, float posZ, glm::vec3 scale, glm::vec3 rotationAxis, float speed, float scaleFactor, Shader * shader)
{
	MeshCollection * Meshes = new MeshCollection();
	LoadMeshesFromFile(fileLocation, Meshes);

	textureID = LoadTextureFromFile(textureLocation);

	GameObject * GO = new GameObject();
	GO->SetPosition(posX, posY, posZ);
	GO->SetMesh(Meshes);
	GO->SetScale(scale);
	GO->SetRotationAxis(rotationAxis);
	GO->SetRotationSpeed(speed);
	GO->SetScaleFactor(scaleFactor);
	GO->SetIsParticle(true);
	GO->SetWithPlayer(true);
	GO->SetShader(shader);
	GO->SetdiffuseTexture(textureID);
	particleObjectList.push_back(GO);
}


//Renders game objects from a given list 
void ObjectManager::DrawObjects(std::vector<GameObject*> list, glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition)
{
	for (GameObject * obj : list) {

		Shader * currentShader = obj->GetShader();
		currentShader->Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, obj->GetDiffuseTexture());

		glUniformMatrix4fv(currentShader->GetUniform("modelMatrix"), 1, GL_FALSE, glm::value_ptr(obj->GetModelTransformation()));
		glUniformMatrix4fv(currentShader->GetUniform("view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(currentShader->GetUniform("proj"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform1i(currentShader->GetUniform("diffuseTexture"), 0);
		// lighting
		glUniform4fv(currentShader->GetUniform("ambientMaterialColour"), 1, glm::value_ptr(lightValues.ambientMaterialColour));
		glUniform4fv(currentShader->GetUniform("diffuseMaterialColour"), 1, glm::value_ptr(lightValues.diffuseMaterialColour));
		glUniform4fv(currentShader->GetUniform("specularMaterialColour"), 1, glm::value_ptr(lightValues.specularMaterialColour));

		glUniform4fv(currentShader->GetUniform("ambientLightColour"), 1, glm::value_ptr(lightValues.ambientLightColour));
		glUniform4fv(currentShader->GetUniform("diffuseLightColour"), 1, glm::value_ptr(lightValues.diffuseLightColour));
		glUniform4fv(currentShader->GetUniform("specularLightColour"), 1, glm::value_ptr(lightValues.specularLightColour));

		glUniform3fv(currentShader->GetUniform("lightDirection"), 1, glm::value_ptr(lightValues.lightDirection));
		glUniform1f(currentShader->GetUniform("specularMaterialPower"), lightValues.specularMaterialPower);

		glUniform3fv(currentShader->GetUniform("cameraPosition"), 1, glm::value_ptr(cameraPosition));
		glUniform3fv(currentShader->GetUniform("pointLightPos"), 1, glm::value_ptr(lightObjectPos));

		obj->Render();
	}
}

void ObjectManager::LoadAllObjects(Shader* objectShader, Shader* lightShader)
{
	// generate planets
	CreateObject("Model/egypt.fbx", "Model/colour.png", 0.0f, 40.0f, -300.0f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -0.1f, objectShader);
	CreateObject("Model/forest.fbx", "Model/colour.png", 100.0f, -40.0f, -150.0f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.4f, 1.0f, 0.0f), 0.1f, objectShader);
	CreateObject("Model/ice.fbx", "Model/colour.png", -300.0f, -20.0f, -450.0f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.5f, 0.5f), 0.1f, objectShader);
	CreateObject("Model/iceGray.fbx", "Model/colour.png", 100.0f, -140.0f, -250.0f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 1.0f), -0.1f, objectShader);
	CreateObject("Model/orange.fbx", "Model/colour.png", 600.0f, 100.0f, -650.0f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), 0.1f, objectShader);
	CreateObject("Model/pine.fbx", "Model/colour.png", -500.0f, -200.0f, -450.0f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 0.0f), 0.1f, objectShader);


	// create light object
	CreateLightObject("Model/star.obj", "Model/light3.png", 10.0f, 10.0f, -20.0f, glm::vec3(0.085f, 0.085f, 0.085f), glm::vec3(1.0f, 1.0f, 0.0f), 1.5f, 0.0f, lightShader);
}

void ObjectManager::UpdateObjectList(std::vector<GameObject*> list, PlayerController player, bool light, float deltaTime)
{
	for (GameObject * obj : list)
	{
		if (light)
		{
			// trying to make the light stay with the camera
			glm::vec3 offset = glm::vec3(0.2f, -0.2f, 0.0f);
			glm::vec3 pos = player.camera.GetCameraFront();
			glm::vec3 playerPos = player.camera.GetCameraPos();
			// add the offset to the normalised vector for where we are looking
			pos = pos + offset;
			// increase the vector
			pos = pos * 10.f;
			currentLightPos = pos + playerPos;

			if (obj->GetWithPlayer())
			{
				// add player pos to vector
				lightObjectPos = currentLightPos;
			}
			else if (!obj->GetWithPlayer())
			{
				glm::vec3 currentDirection = obj->GetThrownDirection();
				currentDirection = currentDirection + obj->GetThrownNormal();
				obj->SetThrownDirection(currentDirection);
				lightObjectPos = currentDirection;
			}

			obj->SetPosition(lightObjectPos.x, lightObjectPos.y, lightObjectPos.z);
		}

		obj->Update(deltaTime);

	}
}