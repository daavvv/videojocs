#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

enum EnemyAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	life = 3.f;
	//cout << "aqui entro" << endl;
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
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::update(int deltaTime, int Posplayerx, int Posplayery)
{
	int diferenciax = abs(posEnemy.x - Posplayerx);
	int diferenciay = abs(posEnemy.y - Posplayery);
	

	sprite->update(deltaTime);

	if (diferenciay < diferenciax && Posplayerx < posEnemy.x) {
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posEnemy.x -= 1;
		if (map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32)))
		{
			posEnemy.x += 1;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (diferenciay < diferenciax && Posplayerx > posEnemy.x) {
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posEnemy.x += 1;
		if (map->collisionMoveRight(posEnemy, glm::ivec2(32, 32)))
		{
			posEnemy.x -= 1;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (!(Posplayery < posEnemy.y && diferenciay > diferenciax && (map->Exists_platform(posEnemy, glm::ivec2(32, 32)) or (Posplayerx >= posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x + map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))) or (Posplayerx < posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x - map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))))) and (diferenciay >= diferenciax && Posplayerx < posEnemy.x)) {
		cout << "entro----------------------" << endl;
		if (sprite->animation() != MOVE_LEFT) {
			sprite->changeAnimation(MOVE_LEFT);
		}
		posEnemy.x -= 1;
		if (map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32)))
		{

			cout << "aqui no hauria d'entrar" << endl;
			posEnemy.x += 1;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (!(Posplayery < posEnemy.y && diferenciay > diferenciax && (map->Exists_platform(posEnemy, glm::ivec2(32, 32)) or (Posplayerx >= posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x + map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))) or (Posplayerx < posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x - map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))))) and diferenciay >= diferenciax && Posplayerx > posEnemy.x) {
		cout << "entro22222222222222222222222222222" << endl;
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posEnemy.x += 1;
		if (map->collisionMoveRight(posEnemy, glm::ivec2(32, 32)))
		{
			posEnemy.x -= 1;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else {//animacions
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posEnemy.y = startY;
		}
		else
		{
			posEnemy.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y);
		}
	}
	else
	{
		posEnemy.y += FALL_STEP;
		if (map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y))
		{
			if (Posplayery < posEnemy.y && diferenciay > diferenciax &&  (map->Exists_platform(posEnemy, glm::ivec2(32, 32)) or (Posplayerx >= posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x + map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))) or   (Posplayerx < posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x - map->getTileSize(), posEnemy.y), glm::ivec2(32, 32)))   ))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posEnemy.y;
			}
			/*else {
				if (diferenciay >= diferenciax && Posplayerx < posEnemy.x) {
					cout << "entro----------------------" << endl;
					if (sprite->animation() != MOVE_LEFT) {
						sprite->changeAnimation(MOVE_LEFT);
					}
					posEnemy.x -= 1;
					if (map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32)))
					{

						cout << "aqui no hauria d'entrar" << endl;
						posEnemy.x += 1;
						sprite->changeAnimation(STAND_LEFT);
					}
				}
				else if (diferenciay >= diferenciax && Posplayerx > posEnemy.x) {
					cout << "entro22222222222222222222222222222" << endl;
					if (sprite->animation() != MOVE_RIGHT)
						sprite->changeAnimation(MOVE_RIGHT);
					posEnemy.x += 1;
					if (map->collisionMoveRight(posEnemy, glm::ivec2(32, 32)))
					{
						posEnemy.x -= 1;
						sprite->changeAnimation(STAND_RIGHT);
					}
				}
				/*else {//animacions
					if (sprite->animation() == MOVE_LEFT)
						sprite->changeAnimation(STAND_LEFT);
					else if (sprite->animation() == MOVE_RIGHT)
						sprite->changeAnimation(STAND_RIGHT);
				}*/
			//}	
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}


void Enemy::render()
{
	sprite->render();
}

void Enemy::setPosition(const glm::vec2 &pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Enemy::set_life(float resta) {
	life = life - resta;
}