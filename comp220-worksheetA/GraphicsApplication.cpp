#include "GraphicsApplication.h"


GraphicsApplication::GraphicsApplication()
{
}

GraphicsApplication::~GraphicsApplication()
{
}

void GraphicsApplication::init()
{
	Game::init();
	
	// -------- INIT GAMEOBJECTS AND SHADERS ------- //

	//Load Meshs
	skyboxModel = new MeshCollection();
	loadMeshFromFile("Skybox\\box.FBX", skyboxModel);

	dinoModel = new MeshCollection();
	loadMeshFromFile("TomModel.FBX", dinoModel);

	teaPotModel = new MeshCollection();
	loadMeshFromFile("teaPotModel.FBX", teaPotModel);

	BunnyModel = new MeshCollection();
	loadMeshFromFile("stanfordBunny.FBX", BunnyModel);

	GroundModel = new MeshCollection();
	loadMeshFromFile("FBXmodels\\Ground2.FBX", GroundModel);

	TreeModel = new MeshCollection();
	loadMeshFromFile("FBXmodels\\Tree1.FBX", TreeModel);

	GrassModel = new MeshCollection();
	loadMeshFromFile("FBXmodels\\Grass1.FBX", GrassModel);

	FlowersModel = new MeshCollection();
	loadMeshFromFile("FBXmodels\\Flower1.FBX", FlowersModel);

	FlowersModel2 = new MeshCollection();
	loadMeshFromFile("FBXmodels\\Flower2.FBX", FlowersModel2);

	MushroomModel = new MeshCollection();
	loadMeshFromFile("FBXmodels\\Mushroom1.FBX", MushroomModel);

	// load in the shaders
	shaderManager.LoadShaders("skyboxShader", "vertSkybox.glsl", "fragSkybox.glsl");
	shaderManager.LoadShaders("defShader", "vert.glsl", "frag.glsl");
	shaderManager.LoadShaders("texturedShader", "texturedVert.glsl", "texturedFrag.glsl");
	shaderManager.LoadShaders("VertexShader", "VertexAnimation.glsl", "texturedFrag.glsl");
	shaderManager.LoadShaders("leafVertexShader", "leafVertexAnimation.glsl", "texturedFrag.glsl");
	shaderManager.LoadShaders("GroundShader", "groundVert.glsl", "groundFrag.glsl");
	
	// Setting certain shaders to not cull, this allows leaves and folliage to be rendered correctly
	shaderManager.GetShader("leafVertexShader")->setCulling(false);
	shaderManager.GetShader("VertexShader")->setCulling(false);
	shaderManager.GetShader("skyboxShader")->setCulling(false);

	//SDL mouse mode setting
	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	// INIT SKYBOX
	skybox->Init();
	skybox->SetMesh(skyboxModel);
	skybox->setShader("skyboxShader");
	skybox->SetScale(40.0f, 40.0f, 40.0f);
	skybox->SetPosition(0.0f, -5.0f, 0.0f);

	// Create each seperate new GameObject
	GameObject* GO1 = new GameObject;
	GO1->CreateGameObject("TeaPot", glm::vec3(0.0f, 0.0f, 14.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f), teaPotModel);

	GameObject* GO2 = new GameObject;
	GO2->SetMesh(dinoModel);
	GO2->SetDiffuseTexture("tomTexture.png");
	GO2->setShader("texturedShader");
	GO2->SetRotation(0.0f, 0.0f, 3.14f);

	GameObject* GO4 = new GameObject;
	GO4->CreateGameObject("BunnyRabbit", glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.012f, 0.012f, 0.012f), glm::vec3(0.0f, 0.0f, 0.0f), BunnyModel);

	GameObject* GO5 = new GameObject;
	GO5->CreateGameObject("Ground", glm::vec3(-30.0f, 0.0f, -30.0f), glm::vec3(1.0f), glm::vec3(-1.5708f, 0.0f, 0.0f), GroundModel, "GroundShader", "FBXmodels\\Textures\\ground_grass.tga");

	GameObject* GO6 = new GameObject;
	GO6->CreateGameObject("Grass", glm::vec3(-8.0f, 0.0f, 1.0f), glm::vec3(1.0f), glm::vec3(0), GrassModel, "VertexShader", "FBXmodels\\Textures\\Plant.tga");

	GameObject* GO7 = new GameObject;
	GO7->CreateGameObject("Flowers", glm::vec3(-8.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0), FlowersModel, "VertexShader", "FBXmodels\\Textures\\Plant.tga");

	GameObject* GO8 = new GameObject;
	GO8->CreateGameObject("Flowers2", glm::vec3(-8.0f, 0.0f, 3.0f), glm::vec3(1.0f), glm::vec3(0), FlowersModel2, "VertexShader", "FBXmodels\\Textures\\Plant.tga");

	// Add all the GameObjects to a list
	objs.push_back(GO5);
	//objs.push_back(GO4);
	objs.push_back(GO2);
	//objs.push_back(GO1);
	//objs.push_back(GO3);
	objs.push_back(GO6);
	objs.push_back(GO7);
	objs.push_back(GO8);


	objs.push_back(skybox);


	int amount = 30;
	for (int i = 0; i < amount; i++)
	{
		GameObject* GO9 = new GameObject;
		GO9->CreateGameObject("Grass", glm::vec3(-8.0f, 0.0f, 1.0f), glm::vec3(1.0f), glm::vec3(0), GrassModel, "VertexShader", "FBXmodels\\Textures\\Plant.tga");
		GameObject* GO10 = new GameObject;
		GO10->CreateGameObject("Flowers", glm::vec3(-8.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0), FlowersModel, "VertexShader", "FBXmodels\\Textures\\Plant.tga");
		GameObject* GO11 = new GameObject;
		GO11->CreateGameObject("Flowers2", glm::vec3(-8.0f, 0.0f, 3.0f), glm::vec3(1.0f), glm::vec3(0), FlowersModel2, "VertexShader", "FBXmodels\\Textures\\Plant.tga");

		objs.push_back(GO9);
		objs.push_back(GO10);
		objs.push_back(GO11);
	}

	for (int i = 0; i < 10; i++)
	{
		GameObject* GO3 = new GameObject;
		GO3->SetMesh(TreeModel);
		GO3->setName("TreeModel");
		GO3->SetDiffuseTextures("FBXmodels\\Textures\\Birch_leaves.tga");
		GO3->SetDiffuseTextures("FBXmodels\\Textures\\TreeTexture.tga");
		GO3->setShader("leafVertexShader");
		objs.push_back(GO3);

		GameObject* GO12 = new GameObject;
		GO12->CreateGameObject("Mushroom", glm::vec3(-8.0f, 0.0f, 3.0f), glm::vec3(1.0f), glm::vec3(0), MushroomModel, "texturedShader", "FBXmodels\\Textures\\Plant.tga");
		objs.push_back(GO12);
	}

	// Set the position for each GameObject in the list
	int count = 0;
	for (GameObject * obj : objs)
	{
		if (obj->getName() == "Grass" || obj->getName() == "Flowers" || obj->getName() == "Flowers2")
		{
			obj->SetPosition(RandomFloat(-15.0f, 15.0f), 0.0f, RandomFloat(-15.0f, 15.0f));
			obj->SetRotation(0.0f, RandomFloat(0.0f, 6.2f), 0.0f);
		}

		if (obj->getName() == "TreeModel" || obj->getName() == "Mushroom")
		{
			obj->SetPosition(RandomFloat(-15.0f, 15.0f), 0.0f, RandomFloat(-15.0f, 15.0f));
			obj->SetRotation(0.0f, RandomFloat(0.0f, 6.2f), 0.0f);
		}

		objs[2]->SetPosition(0.0f, 0.0f, 5);
		//objs[4]->SetPosition(0.0f, 0.0f, -7.0f);
	}

}

// Updating process for each object in the scene
void GraphicsApplication::update()
{
	Game::update();

	//objs[1]->SetRotation(0.0f, (0.3f * time.GetUpdatedTime()), 0.0f);

	// Go through each object in the scene and update them
	for (GameObject * obj : objs)
	{
		obj->Update(time.GetDeltaTime());
	}

	alphaTime += 0.8 * time.GetDeltaTime();

}

// Rendering process for each object in the scene
void GraphicsApplication::render()
{
	Game::startRender();

	for (GameObject * obj : objs)
	{
		Shader * currentShader = shaderManager.GetShader(obj->getShader());

		useShader(currentShader, obj);

		if (obj->getName() == "TreeModel")
		{
			MeshCollection * m = obj->GetMeshes();
			glUniform1f(currentShader->getUniformLocation("windForce"), treeWindForce);
			obj->SetActiveTexture(1);
			m->RenderIndex(1);

			//USE SHADER PROGRAM Bark
			currentShader = shaderManager.GetShader("texturedShader");
			useShader(currentShader, obj);
			obj->SetActiveTexture(0);
			m->RenderIndex(0);
		}
		else
			obj->Render();
	}

	Game::endRender();
}


void GraphicsApplication::useShader(Shader * currentShader, GameObject * obj)
{
	if (currentShader->isCullingEnabled())
	{
		glEnable(GL_CULL_FACE);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	//glEnable(currentShader->getCullMode());
	//glCullFace(GL_FRONT);

	glUseProgram(currentShader->getProgramID());

	// send the uniforms across
	glUniformMatrix4fv(currentShader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(obj->GetModelTransformation()));
	glUniformMatrix4fv(currentShader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
	glUniformMatrix4fv(currentShader->getUniformLocation("projMatrix"), 1, GL_FALSE, glm::value_ptr(camera.Projection));

	glUniform3fv(currentShader->getUniformLocation("cameraPosition"), 1, glm::value_ptr(camera.pos));
	glUniform4fv(currentShader->getUniformLocation("ambientLightColour"), 1, glm::value_ptr(ambientLightColour));
	glUniform4fv(currentShader->getUniformLocation("diffuseLightColour"), 1, glm::value_ptr(diffuseLightColour));
	glUniform4fv(currentShader->getUniformLocation("specularLightColour"), 1, glm::value_ptr(specularLightColour));

	GLint ambientLocation = currentShader->getUniformLocation("ambientMaterialColour");
	glUniform4fv(currentShader->getUniformLocation("ambientMaterialColour"), 1, glm::value_ptr(ambientMaterialColour));
	glUniform4fv(currentShader->getUniformLocation("diffuseMaterialColour"), 1, glm::value_ptr(diffuseMaterialColour));
	glUniform4fv(currentShader->getUniformLocation("specularMaterialColour"), 1, glm::value_ptr(specularMaterialColour));
	glUniform1f(currentShader->getUniformLocation("specularMaterialPower"), specularMaterialPower);

	glUniform3fv(currentShader->getUniformLocation("lightDirection"), 1, glm::value_ptr(lightDirection));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj->GetDiffuseTexture());

	glUniform1f(currentShader->getUniformLocation("currentTime"), alphaTime);
	glUniform1f(currentShader->getUniformLocation("deltaTime"), deltaTimeLocation);

	glUniform1f(currentShader->getUniformLocation("windForce"), windForce);
}
