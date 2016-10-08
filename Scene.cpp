#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 64
#define SCREEN_Y -96

#define INIT_PLAYER_X_TILES 0
#define INIT_PLAYER_Y_TILES 14


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}



void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
}

void Scene::render()
{

	//cout << projection[0][0] << "," << projection[1][1] << "," << projection[2][2] << endl;
	//cout << "Player position: " << player->getPosition().x/SCREEN_X << "," << player->getPosition().y/SCREEN_Y << endl;
	//cout << "Camera position: " << projection[0][0] << "," << projection[1][1] << endl;


	glm::mat4 modelview;
	texProgram.use();
	float px,py,left,right,bottom,top;

	px = player->getPosition().x; py = player->getPosition().y;
	left = px - (SCREEN_WIDTH/2.0);
	top = py - (SCREEN_HEIGHT/2.0);
	right = left + SCREEN_WIDTH;
	bottom = top + SCREEN_HEIGHT;

	//projection = glm::ortho(left,right,bottom,top);


	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	//modelview = glm::translate(modelview, glm::vec3(-(player->getPosition().x/SCREEN_WIDTH), -(player->getPosition().y/SCREEN_HEIGHT), 0.f));

	texProgram.setUniformMatrix4f("modelview", modelview);



	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



