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

	//Load Mesh
	dinoModel = new MeshCollection();
	loadMeshFromFile("TomModel.FBX", dinoModel);

	teaPotModel = new MeshCollection();
	loadMeshFromFile("teaPotModel.FBX", teaPotModel);

	BunnyModel = new MeshCollection();
	loadMeshFromFile("stanfordBunny.FBX", BunnyModel);

	GroundModel = new MeshCollection();
	loadMeshFromFile("Ground.FBX", GroundModel);

	TreeModel = new MeshCollection();
	loadMeshFromFile("FBXmodels\\Tree1.FBX", TreeModel);

	GrassModel = new MeshCollection();
	loadMeshFromFile("FBXmodels\\Grass1.FBX", GrassModel);

	FlowersModel = new MeshCollection();
	loadMeshFromFile("FBXmodels\\Flower1.FBX", FlowersModel);

	// needs to stay disabled for the grass to work
	// Culls the clockwise facing side of the triangles
	//glEnable(GL_CULL_FACE);

	// load in the shaders
	shaderManager.LoadShaders("defShader", "vert.glsl", "frag.glsl");
	shaderManager.LoadShaders("texturedShader", "texturedVert.glsl", "texturedFrag.glsl");
	shaderManager.LoadShaders("VertexShader", "VertexAnimation.glsl", "texturedFrag.glsl");

	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	// Create each seperate new GameObject
	GameObject* GO1 = new GameObject;
	GO1->SetMesh(teaPotModel);
	GO1->setShader("defShader");
	GO1->SetScale(0.2f, 0.2f, 0.2f);

	GameObject* GO2 = new GameObject;
	GO2->SetMesh(dinoModel);
	GO2->SetDiffuseTexture("tomTexture.png");
	GO2->setShader("texturedShader");
	GO2->SetRotation(0.0f, 0.0f, 3.14f);

	GameObject* GO3 = new GameObject;
	GO3->SetMesh(TreeModel);
	GO3->SetDiffuseTexture("FBXmodels\\Textures\\TreeTexture.tga");
	GO3->SetDiffuseTexture("FBXmodels\\Textures\\Birch_leaves.tga");
	GO3->setShader("VertexShader");

	GameObject* GO4 = new GameObject;
	GO4->SetMesh(BunnyModel);
	GO4->setShader("defShader");
	GO4->SetScale(0.012f, 0.012f, 0.012f);

	GameObject* GO5 = new GameObject;
	GO5->SetMesh(GroundModel);
	GO5->setShader("defShader");

	GameObject* GO6 = new GameObject;
	GO6->SetMesh(GrassModel);
	GO6->SetDiffuseTexture("FBXmodels\\Textures\\Plant.tga");
	GO6->setShader("VertexShader");

	GameObject* GO7 = new GameObject;
	GO7->SetMesh(FlowersModel);
	GO7->SetDiffuseTexture("FBXmodels\\Textures\\Plant.tga");
	GO7->setShader("VertexShader");

	// Add all the GameObjects to a list
	objs.push_back(GO5);
	objs.push_back(GO4);
	objs.push_back(GO2);
	objs.push_back(GO1);
	objs.push_back(GO3);
	objs.push_back(GO6);
	objs.push_back(GO7);

	// Set the position for each GameObject in the list
	int count = 0;
	for (GameObject * obj : objs)
	{
		objs[1]->SetPosition(0.0f, 3.0f, 0);
		objs[2]->SetPosition(0.0f, 0.0f, 5);
		objs[3]->SetPosition(0.0f, 0.0f, 14);
		objs[4]->SetPosition(0.0f, 0.0f, -7.0f);
		objs[5]->SetPosition(-8.0f, 0.0f, 0.0f);
		objs[6]->SetPosition(-8.0f, 0.0f, 1.0f);
	}
}

// Updating process for each object in the scene
void GraphicsApplication::update()
{
	Game::update();

	objs[1]->SetRotation(0.0f, (0.3f * time.GetUpdatedTime()), 0.0f);

	// Go through each object in the scene and update them
	for (GameObject * obj : objs)
	{
		obj->Update(time.GetDeltaTime());
	}

}

// Rendering process for each object in the scene
void GraphicsApplication::render()
{
	Game::startRender();

	for (GameObject * obj : objs)
	{
		Shader * currentShader = shaderManager.GetShader(obj->getShader());

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

		alphaTime += 0.2 * time.GetDeltaTime();
		glUniform1f(currentShader->getUniformLocation("currentTime"), alphaTime);
		glUniform1f(currentShader->getUniformLocation("deltaTime"), deltaTimeLocation);

		obj->Render();
	}

	Game::endRender();
}

