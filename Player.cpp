#include <cmath>
#include <iostream>
#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define DIGCOOLDOWN 6250

#define SWORDONPLAYERIMGPATH "images/UI/swordOnPlayer.png"
#define AXEONPLAYERIMGPATH "images/ui/axeOnPlayer.png"

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

/*
void OnMouseClick(int button, int state, int x, int y)
{
	cout << glutGet(GLUT_WINDOW_WIDTH)  <<' ' << x << endl;
	cout << glutGet(GLUT_WINDOW_HEIGHT) << ' '<< y<< endl;
	int centrex = glutGet(GLUT_WINDOW_WIDTH)/2;
	int centrey= glutGet(GLUT_WINDOW_HEIGHT)/2;
	int puntx = x - centrex;
	int punty = y - centrey;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//store the x,y value where the click happened
		cout << "he clicat" << endl;
		if (abs(puntx) > abs(punty)) {
			if (puntx > 0) {
				cout << "dreta" << endl;
			}
			else {
				cout << "esquerra" << endl;
			}
		}
		else {
			if (punty < 0) {
				cout << "adalt" << endl;
			}
			else {
				cout << "abaix" << endl;
			}
		}
	}
}*/

glm::ivec2 Player::getPosition(){
	return posPlayer;
}


vector<Item> Player::getBag() {
	return this->bag;
}

vector<PersonalItem> Player::getPersonalItems()
{
	return personalItems;
}


void Player::loadSprite() {

}

int Player::get_attack_power()
{
	return this->attackpower;
}



void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	
	//glutMouseFunc(OnMouseClick);
	attackpower = 3;
	weapon = "none";
	goldcoins = 0;
	buildTile = 0;
	dig = 2;
	build = 2;
	life = 3.f;
	bJumping = false;
	bdownLadder = false;
	bdigging = false;
	bbuilding = false;
	digCounter = DIGCOOLDOWN;
	buildCounter = DIGCOOLDOWN;

	swordTex.loadFromFile(SWORDONPLAYERIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA);
	axeTex.loadFromFile(AXEONPLAYERIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA);
	sword = Sprite::createSprite(glm::ivec2(26, 26), glm::ivec2(1, 1), &swordTex, &shaderProgram);
	axe = Sprite::createSprite(glm::ivec2(26, 26), glm::ivec2(1, 1), &axeTex, &shaderProgram);

	sword->setNumberAnimations(1);
	axe->setNumberAnimations(1);

	sword->setAnimationSpeed(MOVE_RIGHT, 1);
	axe->setAnimationSpeed(MOVE_RIGHT, 1);



	spritesheet.loadFromFile("images/player1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(25, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.25f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.50f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		int frames = 4;
		for (int i = frames-1; i > 0; --i)
		{
			float division = float(1) / float(4);
			float coordx = i*division;

			sprite->addKeyframe(MOVE_LEFT, glm::vec2(coordx, 0.25f));
		}

		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		for (int i = 0; i < frames - 1; ++i)
		{
			float division = float(1) / float(4);
			float coordx = i*division;

			sprite->addKeyframe(MOVE_RIGHT, glm::vec2(coordx, 0.50f));
		}

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	
}


float Player::getLife() {
	return this->life;
}

int Player::getGoldCoins()
{
	return this->goldcoins;
}

void Player::setWeapon(string type)
{
	this->weapon = type;
}

void Player::setLife(float life) {
	this->life = life;
}


void Player::printPosition(){
	
	//cout << "Player position: " << this->getPosition().x << "," << this->getPosition().y << endl;
	//projection = projection*glm::ortho()

	//gluOrtho2D( Position.X - 600 / 2.0, Position.X + 600 / 2.0, Position.Y - 600 / 2.0, Position.Y + 600 / 2.0);

}

void Player::setBuildTile(int tileID)
{
	this->buildTile = tileID;
}


void Player::update(int deltaTime)
{
	int xpos, ypos;
	/*Game::instance().mouseMove() {

	}*/

	if (map->isOverGoldCoin(posPlayer, glm::ivec2(32, 32))) {
		if (goldcoins < 100) {
			goldcoins++;
		}

		if (goldcoins == 5) {
			if (life <= 2) {
				life++;
				goldcoins = goldcoins - 5;
			}
		}
	}


	cout << weapon << endl;

	sprite->update(deltaTime);

	if (weapon == "sword") {
		attackpower = 5;
		sword->update(deltaTime);
		int x = posPlayer.x+72;
		int y = posPlayer.y-95;

		glm::ivec2 p;
		p.x = x;
		p.y = y;

		sword->setPosition(p);
	}

	if (weapon == "axe") {
		attackpower = 10;
		axe->update(deltaTime);
		int x = posPlayer.x + 72;
		int y = posPlayer.y - 95;

		glm::ivec2 p;
		p.x = x;
		p.y = y;

		axe->setPosition(p);
	}


		
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		//printPosition();
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		//printPosition();
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	
	if (this->buildTile != 0 && isEnoughAmount(this->buildTile)) {
		if (Game::instance().getKey('2')) {
			if (map->bottomTileIsBuildable(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
				if (build == 2 && !bbuilding) {
					posPlayer.y = posPlayer.y - 60;
					build--;
					return;
				}
			}
		}
		if (Game::instance().getKey('3')) {
			if (map->rightTileIsBuildable(posPlayer, glm::ivec2(32, 32))) {
				if (build == 2 && !bbuilding) {
					build--;
					return;
				}
			}
		}
		if (Game::instance().getKey('1')) {
			if (map->leftTileIsBuildable(posPlayer, glm::ivec2(32, 32))) {
				if (build == 2 && !bbuilding) {
					build--;
					return;
				}
			}
		}
		else {
			if (build == 1 && !bbuilding) {
				map->buildTile(this->buildTile);
				substractOne(this->buildTile);
				build = 2;
			}
		}
	}
	
	if (Game::instance().getKey('s')) {
		if (map->bottomTileIsDiggable(posPlayer, glm::ivec2(32, 32))) {

			if (dig == 2 && !bdigging){

				map->setCavar(true);
				map->render();

				dig--;
				return;
			}
		}
	}
	else if (Game::instance().getKey('a')) {
		if (map->leftTileIsDiggable(posPlayer, glm::ivec2(32, 32))) {

			if (dig == 2 && !bdigging) {

				map->setCavar(true);
				map->render();

				dig--;
				return;
			}
		}
	}
	else if (Game::instance().getKey('d')) {
		if (map->rightTileIsDiggable(posPlayer, glm::ivec2(32, 32))) {

			if (dig == 2 && !bdigging) {

				map->setCavar(true);
				map->render();

				dig--;
				return;
			}
		}
	}
	else if (Game::instance().getKey('w')) {
		if (map->topTileIsDiggable(posPlayer, glm::ivec2(32, 32))) {

			if (dig == 2 && !bdigging) {

				map->setCavar(true);
				map->render();

				dig--;
				return;
			}
		}
	}
	else {
		if (dig == 1 && !bdigging) {
			int tile = map->digTile();
			addItemToBag(tile);
			dig = 2;
		}
	}
	
	if(bJumping)
	{
	
		jumpAngle += JUMP_ANGLE_STEP;

		if (jumpAngle == 180 || !map->canJump(posPlayer, glm::ivec2(32, 32)))
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}

		//printPosition();
	}
	else
	{
		
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP) && map->canJump(posPlayer,glm::ivec2(32,32)))
			{

				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

bool Player::isEnoughAmount(int tileID) {
	for (int i = 0; i < bag.size(); ++i) {
		if (tileID == bag[i].ID) {
			if (bag[i].amount > 0) {
				return true;
			}
		}
	}
	return false;
}



bool Player::isItemInBag(int tileID) {
	for (int i = 0; i < bag.size(); ++i) {
		if (tileID == bag[i].ID) {
			return true;
		}
	}
	return false;
}

void Player::substractOne(int tileID) {
	for (int i = 0; i < bag.size(); ++i) {
		if (tileID == bag[i].ID) {
			bag[i].amount = bag[i].amount - 1;
		}
	}
}

void Player::addPersonalItem(bool weapon, string type)
{

	bool existeix = false;
	for (int i = 0; i < personalItems.size(); ++i) {
		if (type == personalItems[i].type) {
			existeix = true;
		}
	}

	if (!existeix) {
		personalItems.push_back(PersonalItem());
		int size = personalItems.size();
		personalItems[size - 1].type = type;
		personalItems[size - 1].weapon = weapon;
	}
}

void Player::substractMaterialToPlayer(int ID, int amount)
{
	if (isItemInBag(ID) && isEnoughAmount(ID)) {
		for (int i = 0; i < bag.size(); ++i) {
			if (ID == bag[i].ID) {
				bag[i].amount = bag[i].amount - amount;
			}
		}
	}
}


void Player::addItemToBag(int tileID) {

	if (!isItemInBag(tileID)) {
		bag.push_back(Item());
		int size = bag.size();
		bag[size - 1].ID = tileID;
		bag[size - 1].amount = bag[size - 1].amount + 1;
	}
	else {
		for (int i = 0; i < bag.size(); ++i) {
			if (tileID == bag[i].ID) {
				if (bag[i].amount < 100) {
					bag[i].amount = bag[i].amount + 1;
				}
			}
		}
	}
}



void Player::render()
{
	sprite->render();
	if (weapon == "sword") {
		sword->render();
	}
	if (weapon == "axe") {
		axe->render();
	}
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}



void Player::crear(int button, int x, int y) {
	//cout << glutGet(GLUT_WINDOW_WIDTH) << ' ' << x << endl;
	//cout << glutGet(GLUT_WINDOW_HEIGHT) << ' ' << y << endl;
	int centrex = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centrey = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	int puntx = x - centrex;
	int punty = y - centrey;
	if (this->buildTile != 0 && isEnoughAmount(this->buildTile)) {
		if (button == GLUT_LEFT_BUTTON)
		{
			//store the x,y value where the click happened
			//cout << "he clicat" << endl;
			if (abs(puntx) > abs(punty) and puntx > 0) {
				if (map->rightTileIsBuildable(posPlayer, glm::ivec2(32, 32))) {
					if (build == 2 && !bbuilding) {
						build--;
						return;
					}
				}
			}
			else if (abs(puntx) > abs(punty) and puntx <= 0) {
				//cout << "esquerra" << endl;
				if (map->leftTileIsBuildable(posPlayer, glm::ivec2(32, 32))) {
					if (build == 2 && !bbuilding) {
						build--;
						return;
					}
				}
			}
			if (abs(puntx) <= abs(punty) and punty < 0) {
				//cout << "adalt" << endl;
			}
			else if (abs(puntx) <= abs(punty) and punty >= 0) {
				//cout << "abaix" << endl;
				if (map->bottomTileIsBuildable(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
					if (build == 2 && !bbuilding) {
						posPlayer.y = posPlayer.y - 60;
						build--;
						return;
					}
				}
			}
			else {
				if (build == 1 && !bbuilding) {
					map->buildTile(this->buildTile);
					substractOne(this->buildTile);
					build = 2;
				}
			}
		}
	}
}