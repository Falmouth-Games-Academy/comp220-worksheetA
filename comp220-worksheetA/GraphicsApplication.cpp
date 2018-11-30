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

	TankModel = new MeshCollection();
	loadMeshFromFile("Tank1.FBX", TankModel);

	GrassModel = new MeshCollection();
	loadMeshFromFile("Grass.obj", GrassModel);

	// Culls the clockwise facing side of the triangles
	glEnable(GL_CULL_FACE);

	// load in the shaders
	shaderManager.LoadShaders("defShader", "vert.glsl", "frag.glsl");
	shaderManager.LoadShaders("texturedShader", "texturedVert.glsl", "texturedFrag.glsl");
	shaderManager.LoadShaders("VertexShader", "VertexAnimation.glsl", "texturedFrag.glsl");

	SDL_SetRelativeMouseMode(SDL_TRUE);

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
	GO3->SetMesh(TankModel);
	GO3->SetDiffuseTexture("Tank1DF.png");
	GO3->setShader("texturedShader");

	GameObject* GO4 = new GameObject;
	GO4->SetMesh(BunnyModel);
	GO4->setShader("defShader");
	GO4->SetScale(0.012f, 0.012f, 0.012f);

	GameObject* GO5 = new GameObject;
	GO5->SetMesh(GroundModel);
	GO5->setShader("defShader");

	GameObject* GO6 = new GameObject;
	GO6->SetMesh(GrassModel);
	GO6->SetDiffuseTexture("texturegrass.png");
	GO6->setShader("VertexShader");


	objs.push_back(GO5);
	objs.push_back(GO4);
	objs.push_back(GO2);
	objs.push_back(GO1);
	objs.push_back(GO3);
	objs.push_back(GO6);


	int count = 0;
	for (GameObject * obj : objs)
	{
		objs[1]->SetPosition(0.0f, 3.0f, 0);
		objs[2]->SetPosition(0.0f, 0.0f, 5);
		objs[3]->SetPosition(0.0f, 0.0f, 14);
		objs[4]->SetPosition(0.0f, 0.0f, -7);
		objs[5]->SetPosition(-8.0f, 0.0f, 0.0f);
	}
}

void GraphicsApplication::update()
{
	Game::update();

	objs[1]->SetRotation(0.0f, (0.3f * time.GetUpdatedTime()), 0.0f);
	//objs[2]->SetRotation(0.0f, (0.3f * tickTime), (0.3f * tickTime));

	// Go through each object and update them
	for (GameObject * obj : objs)
	{
		obj->Update(time.GetDeltaTime());
	}

}

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

