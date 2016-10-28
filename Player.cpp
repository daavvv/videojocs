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

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


glm::ivec2 Player::getPosition(){
	return posPlayer;
}


vector<Item> Player::getBag() {
	return this->bag;
}


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	life = 3.f;
	bJumping = false;
	bdownLadder = false;
	bdigging = false;
	bbuilding = false;
	digCounter = DIGCOOLDOWN;
	buildCounter = DIGCOOLDOWN;
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}


float Player::getLife() {
	return this->life;
}

void Player::setLife(float life) {
	this->life = life;
}


void Player::printPosition(){
	
	//cout << "Player position: " << this->getPosition().x << "," << this->getPosition().y << endl;
	//projection = projection*glm::ortho()

	//gluOrtho2D( Position.X - 600 / 2.0, Position.X + 600 / 2.0, Position.Y - 600 / 2.0, Position.Y + 600 / 2.0);

}


void Player::update(int deltaTime)
{
	int xpos, ypos;
	/*Game::instance().mouseMove() {

	}*/

	sprite->update(deltaTime);

	if ((digCounter - (deltaTime*40)) < 0) {
		digCounter = DIGCOOLDOWN;
	}
	else {
		digCounter -= deltaTime*40;
	}


	if ((buildCounter - (deltaTime * 40)) < 0) {
		buildCounter = DIGCOOLDOWN;
	}
	else {
		buildCounter -= deltaTime * 40;
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
	/*
	else if (Game::instance().getKey('c'))
	{
		if (map->bottomTileIsDiggable(posPlayer, glm::ivec2(32, 32)))
		{
			cout << "estic fent un forat" << endl;
		}
	}*/
	else
	{
		
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}


	if (bbuilding) {
		bbuilding = false;
		cout << "Building" << endl;
		map->buildTile(220);
	}
	else {
		if(Game::instance().getKey('2')) {
			if (map->bottomTileIsBuildable(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
				if (buildCounter == DIGCOOLDOWN) {
					posPlayer.y = posPlayer.y-10;
					bbuilding = true;
				}
			}
			else {
				buildCounter = DIGCOOLDOWN;
			}
		}
		if (Game::instance().getKey('3')) {
			if (map->rightTileIsBuildable(posPlayer, glm::ivec2(32, 32))) {				
					bbuilding = true;				
			}			
		}
		if (Game::instance().getKey('1')) {
			if (map->leftTileIsBuildable(posPlayer, glm::ivec2(32, 32))) {
					bbuilding = true;
				
			}
		}


		/*if (map->bottomTileIsDiggable(posPlayer, glm::ivec2(32, 32))) {
				if (digCounter == DIGCOOLDOWN) {
					bdigging = true;
				}
			}
			else {
				digCounter = DIGCOOLDOWN;
			}*/
	}



	if (bdigging)
	{
		
		bdigging = false;
		cout << "Digging" << endl;
		int tile = map->digTile();
		addItemToBag(tile);

	}
	else {
		if (Game::instance().getKey('s')) {

			if (map->bottomTileIsDiggable(posPlayer, glm::ivec2(32, 32))) {
				if (digCounter == DIGCOOLDOWN) {
					bdigging = true;
				}
			}
			else {
				digCounter = DIGCOOLDOWN;
			}
		}

		if (Game::instance().getKey('d')) {

			if (map->rightTileIsDiggable(posPlayer, glm::ivec2(32, 32))) {
				if (digCounter == DIGCOOLDOWN) {
					bdigging = true;
				}
			}
			else {
				digCounter = DIGCOOLDOWN;
			}
		}

		if (Game::instance().getKey('w')) {

			if (map->topTileIsDiggable(posPlayer, glm::ivec2(32, 32))) {
				if (digCounter == DIGCOOLDOWN) {
					bdigging = true;
				}
			}
			else {
				digCounter = DIGCOOLDOWN;
			}
		}

		if (Game::instance().getKey('a')) {

			if (map->leftTileIsDiggable(posPlayer, glm::ivec2(32, 32))) {
				if (digCounter == DIGCOOLDOWN) {
					bdigging = true;
				}
			}
			else {
				digCounter = DIGCOOLDOWN;
			}
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


bool Player::isItemInBag(int tileID) {
	for (int i = 0; i < bag.size(); ++i) {
		if (tileID == bag[i].ID) {
			return true;
		}
	}
	return false;
}


void Player::addItemToBag(int tileID) {

	if (!isItemInBag(tileID)) {
		bag.push_back(Item());
		int size = bag.size();
		bag[size - 1].ID = tileID;
		bag[size - 1].amount = bag[size - 1].amount + 1;
	}

}



void Player::render()
{
	sprite->render();
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




