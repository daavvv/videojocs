#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 64
#define SCREEN_Y -96

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 7


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
	
	enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2((INIT_PLAYER_X_TILES+4) * map->getTileSize(), INIT_PLAYER_X_TILES* map->getTileSize()));
	enemy->setTileMap(map);
	
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	glm::ivec2 posicio_player = player->getPosition();
	enemy->update(deltaTime, posicio_player.x, posicio_player.y);
	map->update(deltaTime);



}


float Scene::getPlayerLife() {
	return player->getLife();
}

vector<Item> Scene::getPlayerBag()
{
	return player->getBag();
}


void Scene::render()
{

	//cout << projection[0][0] << "," << projection[1][1] << "," << projection[2][2] << endl;
	//cout << "Player position: " << player->getPosition().x/SCREEN_X << "," << player->getPosition().y/SCREEN_Y << endl;
	//cout << "Camera position: " << projection[0][0] << "," << projection[1][1] << endl;



	glm::mat4 modelview;
	texProgram.use();
	double left,right,bottom,top;
	int px, py;
	
	glm::ivec2 tileMapSize = map->getMapSize();
	int tileSize = map->getTileSize();
	int worldSize = tileSize*tileMapSize.x;

	//cout << "Map Size: " << tileMapSize.x*tileSize << "," << tileMapSize.y*tileSize << endl;
	

	px = player->getPosition().x; py = player->getPosition().y;
	left = px - (SCREEN_WIDTH/2.0)+64;
	top = py - (SCREEN_HEIGHT/2.0)-64;
	right = left + SCREEN_WIDTH;
	bottom = top + SCREEN_HEIGHT;

	projection = glm::ortho(left,right,bottom,top);

	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);



	//modelview = glm::mat4(1.0f);
	//modelview = glm::translate(modelview, glm::vec3(-400, -400.f,0));


	

	texProgram.setUniformMatrix4f("modelview", modelview);


	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	enemy->render();

}

void Scene::setBuildTile(int tileID)
{
	player->setBuildTile(tileID);
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



