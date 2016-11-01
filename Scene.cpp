#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <GL/glut.h>



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
	contador = 0;
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	
	enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2((INIT_PLAYER_X_TILES+4) * map->getTileSize(), INIT_PLAYER_X_TILES* map->getTileSize()));
	enemy->setTileMap(map);
	
	/*boss = new Boss();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	boss->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 4) * map->getTileSize(), INIT_PLAYER_X_TILES* map->getTileSize()));
	boss->setTileMap(map);
	*/
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	glm::ivec2 posicio_player = player->getPosition();
	//map->update(deltaTime);


	if (enemy->get_life() > 0) {
		if (!ataca_enemic())	enemy->update(deltaTime, posicio_player.x, posicio_player.y);
		//boss->update(deltaTime, posicio_player.x, posicio_player.y);
	}
}

bool Scene::ataca_enemic() {
	//si esta al costat que ataqui
	int posy = (enemy->get_position().y);
	//cout << (player->getPosition().x > enemy->get_position().x) << ' ' << ((player->getPosition().x - map->getTileSize()) <= enemy->get_position().x) << endl;
	if (((player->getPosition().y >= enemy->get_position().y) and (player->getPosition().y - map->getTileSize()) <= enemy->get_position().y) or ((player->getPosition().y <= enemy->get_position().y) and (player->getPosition().y + map->getTileSize()) >= enemy->get_position().y)) {
		if ((player->getPosition().x > enemy->get_position().x) and (player->getPosition().x - map->getTileSize()) <= enemy->get_position().x) {
			//cout << "et matari babyy" << endl;
			++contador;
			if(int(contador)%50 == 0){
				player->setLife(player->getLife() - 0.5f);
				}
			/*if(map->collisionMoveDown(enemy->get_position(), glm::ivec2(32, 32), &posy))*/return true;
		}
		else if ((player->getPosition().x <= enemy->get_position().x) and (player->getPosition().x + map->getTileSize()) >= enemy->get_position().x) {
			//cout << "et matari babyy" << endl;
			++contador;
			if (int(contador)% 50 == 0)player->setLife(player->getLife() - 0.5f);
			/*if (map->collisionMoveDown(enemy->get_position(), glm::ivec2(32, 32), &posy))*/return true;
		}
		else {
			contador = 0;
		}
	}
	else {
		contador = 0;
	}
	return false;
}


float Scene::getPlayerLife() {
	return player->getLife();
}

int Scene::getGoldCoins()
{
	return player->getGoldCoins();
}

void Scene::setPlayerWeapon(string type)
{
	player->setWeapon(type);
}

void Scene::substractMaterialToPlayer(int ID, int amount)
{
	player->substractMaterialToPlayer(ID,amount);
}

vector<Item> Scene::getPlayerBag()
{
	return player->getBag();
}

vector<PersonalItem> Scene::getPlayerPersonalItems()
{
	return player->getPersonalItems();
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

	if (enemy->get_life() > 0) {
			enemy->render();
	}
	

	//boss->render();

}

void Scene::setBuildTile(int tileID)
{
	player->setBuildTile(tileID);
}

void Scene::addPersonalItemToPlayer(bool weapon, string type)
{
	player->addPersonalItem(weapon, type);
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

void Scene::mouse_clicked(int button, int x, int y) {
	int centrex = SCREEN_WIDTH / 2;
	int centrey = SCREEN_HEIGHT / 2;
	int puntx = x - centrex;
	int punty = y - centrey;
	if (button == GLUT_RIGHT_BUTTON) {
		if (abs(puntx) > abs(punty) and puntx <= 0) {
			if (((player->getPosition().y >= enemy->get_position().y) and (player->getPosition().y - map->getTileSize()) <= enemy->get_position().y) or ((player->getPosition().y <= enemy->get_position().y) and (player->getPosition().y + map->getTileSize()) >= enemy->get_position().y)) {
				if ((player->getPosition().x > enemy->get_position().x) and (player->getPosition().x - map->getTileSize()) <= enemy->get_position().x) {
					enemy->set_life( 1.f);
				}
			}
		}
		else if (abs(puntx) > abs(punty) and puntx > 0) {
			if (((player->getPosition().y >= enemy->get_position().y) and (player->getPosition().y - map->getTileSize()) <= enemy->get_position().y) or ((player->getPosition().y <= enemy->get_position().y) and (player->getPosition().y + map->getTileSize()) >= enemy->get_position().y)) {
				if ((player->getPosition().x < enemy->get_position().x) and (player->getPosition().x + map->getTileSize()) >= enemy->get_position().x) {
					enemy->set_life(1.f);
				}
			}
		}
	}
	player->crear(button, x, y);
}

