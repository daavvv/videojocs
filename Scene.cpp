#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <GL/glut.h>



#define SCREEN_X 64
#define SCREEN_Y -96

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 32


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
	//enableEnemies = true;
	enable_sprite2 = false;
	ticks = 0;
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	
	/*enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2((INIT_PLAYER_X_TILES+4) * map->getTileSize(), INIT_PLAYER_X_TILES* map->getTileSize()));
	enemy->setTileMap(map);*/

	
	//if (enableEnemies) {
		enemics[0] = new Enemy();
		enemics[0]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemics[0]->setPosition(glm::vec2(14 * map->getTileSize(), 24* map->getTileSize()));
		enemics[0]->set_Area(3, 3);
		enemics[0]->setTileMap(map);
		enemics[0]->set_contador_atac(0);

		enemics[1] = new Enemy();
		enemics[1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemics[1]->setPosition(glm::vec2(37 * map->getTileSize(), 32* map->getTileSize()));
		enemics[1]->set_Area(5, 5);
		enemics[1]->setTileMap(map);
		enemics[1]->set_contador_atac(0);

		enemics[2] = new Enemy();
		enemics[2]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemics[2]->setPosition(glm::vec2(25 * map->getTileSize(), 33 * map->getTileSize()));
		enemics[2]->set_Area(10, 10);
		enemics[2]->setTileMap(map);
		enemics[2]->set_contador_atac(0);

		enemics[3] = new Enemy();
		enemics[3]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemics[3]->setPosition(glm::vec2(36 * map->getTileSize(), 56 * map->getTileSize()));
		enemics[3]->set_Area(7, 7);
		enemics[3]->setTileMap(map);
		enemics[3]->set_contador_atac(0);

		enemics[4] = new Enemy();
		enemics[4]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemics[4]->setPosition(glm::vec2(74 * map->getTileSize(), 51 * map->getTileSize()));
		enemics[4]->set_Area(5, 5);
		enemics[4]->setTileMap(map);
		enemics[4]->set_contador_atac(0);

		enemics[5] = new Enemy();
		enemics[5]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemics[5]->setPosition(glm::vec2(97 * map->getTileSize(), 54 * map->getTileSize()));
		enemics[5]->set_Area(8, 8);
		enemics[5]->setTileMap(map);
		enemics[5]->set_contador_atac(0);

		enemics[6] = new Enemy();
		enemics[6]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemics[6]->setPosition(glm::vec2(63 * map->getTileSize(), 9 * map->getTileSize()));
		enemics[6]->set_Area(10, 10);
		enemics[6]->setTileMap(map);
		enemics[6]->set_contador_atac(0);

		enemics[7] = new Enemy();
		enemics[7]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemics[7]->setPosition(glm::vec2(72 * map->getTileSize(), 37 * map->getTileSize()));
		enemics[7]->set_Area(10, 10);
		enemics[7]->setTileMap(map);
		enemics[7]->set_contador_atac(0);


		boss = new Boss();
		boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		boss->setPosition(glm::vec2(107 * map->getTileSize(), 24* map->getTileSize()));
		boss->set_Area(8, 8);
		boss->setTileMap(map);
	//}
	
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	spritesheet2.loadFromFile("images/dead.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite2 = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.2, 0.2), &spritesheet2, &texProgram);
	sprite2->setNumberAnimations(1);
	sprite2->setAnimationSpeed(0, 25);

	sprite2->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite2->addKeyframe(0, glm::vec2(0.f, 0.2f));
	sprite2->addKeyframe(0, glm::vec2(0.f, 0.4f));
	sprite2->addKeyframe(0, glm::vec2(0.f, 0.6f));
	sprite2->addKeyframe(0, glm::vec2(0.f, 0.8f));
	sprite2->addKeyframe(0, glm::vec2(0.2f, 0.f));
	sprite2->addKeyframe(0, glm::vec2(0.2f, 0.2f));
	sprite2->addKeyframe(0, glm::vec2(0.2f, 0.4f));
	sprite2->addKeyframe(0, glm::vec2(0.2f, 0.6f));
	sprite2->addKeyframe(0, glm::vec2(0.2f, 0.8f));
	sprite2->addKeyframe(0, glm::vec2(0.4f, 0.f));
	sprite2->addKeyframe(0, glm::vec2(0.4f, 0.2f));
	sprite2->addKeyframe(0, glm::vec2(0.4f, 0.4f));
	sprite2->addKeyframe(0, glm::vec2(0.4f, 0.6f));
	sprite2->addKeyframe(0, glm::vec2(0.4f, 0.8f));
	sprite2->addKeyframe(0, glm::vec2(0.6f, 0.f));
	sprite2->addKeyframe(0, glm::vec2(0.6f, 0.2f));
	sprite2->addKeyframe(0, glm::vec2(0.6f, 0.4f));
	sprite2->addKeyframe(0, glm::vec2(0.6f, 0.6f));
	sprite2->addKeyframe(0, glm::vec2(0.6f, 0.8f));
	sprite2->addKeyframe(0, glm::vec2(0.8f, 0.f));
	sprite2->addKeyframe(0, glm::vec2(0.8f, 0.2f));
	sprite2->addKeyframe(0, glm::vec2(0.8f, 0.4f));
	sprite2->addKeyframe(0, glm::vec2(0.8f, 0.6f));
	sprite2->addKeyframe(0, glm::vec2(0.8f, 0.8f));

	sprite2->changeAnimation(0);

	sprite2->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
}

void Scene::update(int deltaTime)
{
	++ticks;
	currentTime += deltaTime;
	player->update(deltaTime);
	glm::ivec2 posicio_player = player->getPosition();
	if (enable_sprite2)sprite2->update(deltaTime);
	map->update(deltaTime);

	//if (enableEnemies) {
		if (enemics[0]->get_life() > 0) {
			//cout << ataca_enemic(deltaTime, enemics[0]) << endl;
			if (!ataca_enemic(deltaTime, enemics[0]))	enemics[0]->update(deltaTime, posicio_player.x, posicio_player.y);
		}
		if (enemics[1]->get_life() > 0) {
			//cout << ataca_enemic(deltaTime, enemics[1]) << endl;
			if (!ataca_enemic(deltaTime, enemics[1]))	enemics[1]->update(deltaTime, posicio_player.x, posicio_player.y);
		}
		if (enemics[2]->get_life() > 0) {
			//cout << ataca_enemic(deltaTime, enemics[1]) << endl;
			if (!ataca_enemic(deltaTime, enemics[2]))	enemics[2]->update(deltaTime, posicio_player.x, posicio_player.y);
		}
		if (enemics[3]->get_life() > 0) {
			//cout << ataca_enemic(deltaTime, enemics[1]) << endl;
			if (!ataca_enemic(deltaTime, enemics[3]))	enemics[3]->update(deltaTime, posicio_player.x, posicio_player.y);
		}
		if (enemics[4]->get_life() > 0) {
			//cout << ataca_enemic(deltaTime, enemics[1]) << endl;
			if (!ataca_enemic(deltaTime, enemics[4]))	enemics[4]->update(deltaTime, posicio_player.x, posicio_player.y);
		}
		if (enemics[5]->get_life() > 0) {
			//cout << ataca_enemic(deltaTime, enemics[1]) << endl;
			if (!ataca_enemic(deltaTime, enemics[5]))	enemics[5]->update(deltaTime, posicio_player.x, posicio_player.y);
		}
		if (enemics[6]->get_life() > 0) {
			//cout << ataca_enemic(deltaTime, enemics[1]) << endl;
			if (!ataca_enemic(deltaTime, enemics[6]))	enemics[6]->update(deltaTime, posicio_player.x, posicio_player.y);
		}
		if (enemics[7]->get_life() > 0) {
			//cout << ataca_enemic(deltaTime, enemics[1]) << endl;
			if (!ataca_enemic(deltaTime, enemics[7]))	enemics[7]->update(deltaTime, posicio_player.x, posicio_player.y);
		}
		if (boss->get_life() > 0) {
			ataca_boss(deltaTime);
		}
	//}
	//boss->update(deltaTime, posicio_player.x, posicio_player.y);
}

bool Scene::ataca_enemic(int deltaTime, Enemy *enemic) {
	//si esta al costat que ataqui
	int posy = (enemic->get_position().y);
	//cout << (player->getPosition().x > enemy->get_position().x) << ' ' << ((player->getPosition().x - map->getTileSize()) <= enemy->get_position().x) << endl;
	if (((player->getPosition().y >= enemic->get_position().y) and (player->getPosition().y - map->getTileSize()) <= enemic->get_position().y) or ((player->getPosition().y <= enemic->get_position().y) and (player->getPosition().y + map->getTileSize()) >= enemic->get_position().y)) {

		if ((player->getPosition().x > enemic->get_position().x) and (player->getPosition().x - map->getTileSize()) <= enemic->get_position().x) {
			//cout << "et matari babyy" << endl;
			enemic->set_contador_atac(enemic->get_contador_atac()+1);//++contador
			if(enemic->get_contador_atac()%50 == 0){
				//canviar animacio a atacar
				enemic->update_attack_right(deltaTime);
				player->setLife(player->getLife() - 0.5f);
				}
			
			if (enemic->get_collisionDown()) {
				return true;
			}
		}
		else if ((player->getPosition().x <= enemic->get_position().x) and (player->getPosition().x + map->getTileSize()) >= enemic->get_position().x) {
			//cout << "et matari babyy" << endl;
			enemic->set_contador_atac(enemic->get_contador_atac() + 1);
			if (enemic->get_contador_atac() % 50 == 0) {
				//canviar animacio a atacar
				enemic->update_attack_left(deltaTime);
				player->setLife(player->getLife() - 0.5f);
			}
			if (enemic->get_collisionDown()) {

				return true;
			}
		}
		else {
			enemic->set_contador_atac(0);
		}
	}
	else {
		enemic->set_contador_atac(0);
	}
	return false;
}


float Scene::getPlayerLife() {
	return player->getLife();
}

bool Scene::checkIfPlayerHasWeapon(string type)
{
	return player->hasWeapon(type);
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
	if (enable_sprite2) {
		
		sprite2->render();
		if ((ticks - ticks_inicials) == 15) {
			enable_sprite2 = false;
		}
	}
	//if (enableEnemies) {

		if (enemics[0]->get_life() > 0) {
			enemics[0]->render();
		}
		else if (enemics[0]->get_primera_mort()) {
			enemics[0]->set_primera_mort(false);
			cout << "entro aqui" << endl;
			ticks_inicials = ticks;
			enable_sprite2 = true;
			sprite2->setPosition(glm::vec2(enemics[0]->get_position().x + 1 * map->getTileSize()+16, enemics[0]->get_position().y -3*map->getTileSize()-16));
		}
		if (enemics[1]->get_life() > 0) {
			enemics[1]->render();
		}
		else if (enemics[1]->get_primera_mort()) {
			enemics[1]->set_primera_mort(false);
			cout << "entro aqui" << endl;
			ticks_inicials = ticks;
			enable_sprite2 = true;
			sprite2->setPosition(glm::vec2(enemics[1]->get_position().x + 1 * map->getTileSize() + 16, enemics[1]->get_position().y - 3 * map->getTileSize() - 16));
		}
		if (enemics[2]->get_life() > 0) {
			enemics[2]->render();
		}
		else if (enemics[2]->get_primera_mort()) {
			enemics[2]->set_primera_mort(false);
			cout << "entro aqui" << endl;
			ticks_inicials = ticks;
			enable_sprite2 = true;
			sprite2->setPosition(glm::vec2(enemics[2]->get_position().x + 1 * map->getTileSize() + 16, enemics[2]->get_position().y - 3 * map->getTileSize() - 16));
		}
		if (enemics[3]->get_life() > 0) {
			enemics[3]->render();
		}
		else if (enemics[3]->get_primera_mort()) {
			enemics[3]->set_primera_mort(false);
			cout << "entro aqui" << endl;
			ticks_inicials = ticks;
			enable_sprite2 = true;
			sprite2->setPosition(glm::vec2(enemics[3]->get_position().x + 1 * map->getTileSize() + 16, enemics[3]->get_position().y - 3 * map->getTileSize() - 16));
		}
		if (enemics[4]->get_life() > 0) {
			enemics[4]->render();
		}
		else if (enemics[4]->get_primera_mort()) {
			enemics[4]->set_primera_mort(false);
			cout << "entro aqui" << endl;
			ticks_inicials = ticks;
			enable_sprite2 = true;
			sprite2->setPosition(glm::vec2(enemics[4]->get_position().x + 1 * map->getTileSize() + 16, enemics[4]->get_position().y - 3 * map->getTileSize() - 16));
		}
		if (enemics[5]->get_life() > 0) {
			enemics[5]->render();
		}
		else if (enemics[5]->get_primera_mort()) {
			enemics[5]->set_primera_mort(false);
			cout << "entro aqui" << endl;
			ticks_inicials = ticks;
			enable_sprite2 = true;
			sprite2->setPosition(glm::vec2(enemics[5]->get_position().x + 1 * map->getTileSize() + 16, enemics[5]->get_position().y - 3 * map->getTileSize() - 16));
		}
		if (enemics[6]->get_life() > 0) {
			enemics[6]->render();
		}
		else if (enemics[6]->get_primera_mort()) {
			enemics[6]->set_primera_mort(false);
			cout << "entro aqui" << endl;
			ticks_inicials = ticks;
			enable_sprite2 = true;
			sprite2->setPosition(glm::vec2(enemics[6]->get_position().x + 1 * map->getTileSize() + 16, enemics[6]->get_position().y - 3 * map->getTileSize() - 16));
		}
		if (enemics[7]->get_life() > 0) {
			enemics[7]->render();
		}
		else if (enemics[7]->get_primera_mort()) {
			enemics[7]->set_primera_mort(false);
			cout << "entro aqui" << endl;
			ticks_inicials = ticks;
			enable_sprite2 = true;
			sprite2->setPosition(glm::vec2(enemics[7]->get_position().x + 1 * map->getTileSize() + 16, enemics[7]->get_position().y - 3 * map->getTileSize() - 16));
		}
		if (boss->get_life() > 0) {
			boss->render();
		}
		else if (boss->get_primera_mort()) {
			boss->set_primera_mort(false);
			cout << "entro aqui" << endl;
			ticks_inicials = ticks;
			enable_sprite2 = true;
			sprite2->setPosition(glm::vec2(boss->get_position().x + 1 * map->getTileSize() + 16, enemics[7]->get_position().y - 3 * map->getTileSize() - 16));
		}
	//}
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
			for (int i = 0; i < 8; ++i) {
				//cout << "vidaa " << enemics[i]->get_life() << endl;
				if (((player->getPosition().y >= enemics[i]->get_position().y) and (player->getPosition().y - map->getTileSize()) <= enemics[i]->get_position().y) or ((player->getPosition().y <= enemics[i]->get_position().y) and (player->getPosition().y + map->getTileSize()) >= enemics[i]->get_position().y)) {
					if ((player->getPosition().x >= enemics[i]->get_position().x) and (player->getPosition().x - map->getTileSize()) <= enemics[i]->get_position().x) {
						enemics[i]->set_life(0.2f*player->get_attack_power());
						
					}
				}
			}
			if (((player->getPosition().y >= boss->get_position().y) and (player->getPosition().y - map->getTileSize()) <= boss->get_position().y) or ((player->getPosition().y <= boss->get_position().y) and (player->getPosition().y + map->getTileSize()) >= boss->get_position().y)) {
				if ((player->getPosition().x >= boss->get_position().x) and (player->getPosition().x - map->getTileSize()) <= boss->get_position().x) {
					//cout << "matooooooooooooooooooo2" << endl;
					boss->set_life(0.2f*player->get_attack_power());
					//cout << boss->get_life()<< endl; 
				}
			}
		}
		else if (abs(puntx) > abs(punty) and puntx > 0) {
			for (int i = 0; i < 8; ++i) {
				//cout << "vida" << enemics[i]->get_life() << endl;
				if (((player->getPosition().y >= enemics[i]->get_position().y) and (player->getPosition().y - map->getTileSize()) <= enemics[i]->get_position().y) or ((player->getPosition().y <= enemics[i]->get_position().y) and (player->getPosition().y + map->getTileSize()) >= enemics[i]->get_position().y)) {
					if ((player->getPosition().x <= enemics[i]->get_position().x) and (player->getPosition().x + map->getTileSize()) >= enemics[i]->get_position().x) {
						enemics[i]->set_life(0.2f*player->get_attack_power());
						//cout << "vida" <<  enemics[i]->get_life() << endl;
					}
				}
			}
			if (((player->getPosition().y >= boss->get_position().y) and (player->getPosition().y - map->getTileSize()) <= boss->get_position().y) or ((player->getPosition().y <= boss->get_position().y) and (player->getPosition().y + map->getTileSize()) >= boss->get_position().y)) {
				if ((player->getPosition().x <= boss->get_position().x) and (player->getPosition().x + map->getTileSize()) >= boss->get_position().x) {
					//cout << "matooooooooooooooooooo4" << endl;
					boss->set_life(0.2f*player->get_attack_power());
					//cout << boss->get_life() << endl;
				}
			}
		}
	}
	player->crear(button, x, y);
}




bool Scene::ataca_boss(int deltaTime) {
	//si esta al costat que ataqui
	int posy = (boss->get_position().y);
	if (ticks % 180 == 0) {
		//cout << "of course I enter" << endl;
		boss->update_attack(deltaTime);
		if (((player->getPosition().y >= boss->get_position().y) and (player->getPosition().y - map->getTileSize()) <= boss->get_position().y) or ((player->getPosition().y <= boss->get_position().y) and (player->getPosition().y + (map->getTileSize()) * 3) >= boss->get_position().y)) {// (map->getTileSize())*2 tamany del boss (doble que el enemic)
			if ((player->getPosition().x > boss->get_position().x) and (player->getPosition().x - (map->getTileSize())*3) <= boss->get_position().x) {
				player->setLife(player->getLife() - 1.f);
			}
			else if ((player->getPosition().x <= boss->get_position().x) and (player->getPosition().x + map->getTileSize()) >= boss->get_position().x) {
				player->setLife(player->getLife() - 1.f);
			}
		}

	}
	else if (ticks % 180 == 60) {//activar sprite de boomb
	}
	else {
		boss->update(deltaTime, player->getPosition().x, player->getPosition().y);
	}
	//cout << (player->getPosition().x > enemy->get_position().x) << ' ' << ((player->getPosition().x - map->getTileSize()) <= enemy->get_position().x) << endl;
	/*if (((player->getPosition().y >= boss->get_position().y) and (boss->getPosition().y - map->getTileSize()) <= boss->get_position().y) or ((player->getPosition().y <= boss->get_position().y) and (player->getPosition().y + map->getTileSize()) >= boss->get_position().y)) {

		if ((player->getPosition().x > boss->get_position().x) and (player->getPosition().x - map->getTileSize()) <= boss->get_position().x) {
			//cout << "et matari babyy" << endl;
			++contador;
			if (int(contador) % 50 == 0) {
				//canviar animacio a atacar
				player->setLife(player->getLife() - 0.5f);
			}
				return true;
		}
		else if ((player->getPosition().x <= boss->get_position().x) and (player->getPosition().x + map->getTileSize()) >= boss->get_position().x) {
			//cout << "et matari babyy" << endl;
			++contador;
			if (int(contador) % 50 == 0) {
				//canviar animacio a atacar
				boss->update_attack_left(deltaTime);
				player->setLife(player->getLife() - 0.5f);
			}
			if (boss->get_collisionDown()) {

				return true;
			}
		}
		else {
			contador = 0;
		}
	}
	else {
		contador = 0;
	}*/
	return false;
}