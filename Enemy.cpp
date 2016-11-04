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
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, ATTACK_LEFT, ATTACK_RIGHT
};


void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	Enemic_primera_mort = true;
	life = 3.f;
	//cout << "aqui entro" << endl;
	spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

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

	sprite->setAnimationSpeed(ATTACK_LEFT, 8);
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.f, 0.75f));
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.25f, 0.75f));
	sprite->addKeyframe(ATTACK_LEFT, glm::vec2(0.f, 0.75f));

	sprite->setAnimationSpeed(ATTACK_RIGHT, 8);
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(0.5, 0.75f));
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(0.75, 0.75f));
	sprite->addKeyframe(ATTACK_RIGHT, glm::vec2(0.5, 0.75f));

	/*spritesheet.loadFromFile("images/enemic.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.2), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 10);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.2f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.2f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.2f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, 0.2f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.4f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.4f));*/

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy::update(int deltaTime, int Posplayerx, int Posplayery)
{
	int diferenciax = abs(posEnemy.x - Posplayerx);
	int diferenciay = abs(posEnemy.y - Posplayery);
	

	sprite->update(deltaTime);
	if (Areax > diferenciax / map->getTileSize() && Areay > diferenciay / map->getTileSize()) {
		if (diferenciay < diferenciax && Posplayerx < posEnemy.x) {
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posEnemy.x -= 1;
			if (map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32)))
			{
				posEnemy.x += 1;
				sprite->changeAnimation(STAND_LEFT);
				if (!bJumping and map->can_jump_enemy(glm::ivec2(posEnemy.x - map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))) {
					bJumping = true;
					jumpAngle = 0;
					startY = posEnemy.y;
				}
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
				if (!bJumping and map->can_jump_enemy(glm::ivec2(posEnemy.x + map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))) {
					bJumping = true;
					jumpAngle = 0;
					startY = posEnemy.y;
				}
			}
		}
		else if (!(Posplayery < posEnemy.y && diferenciay > diferenciax && (map->Exists_platform(posEnemy, glm::ivec2(32, 32)) or (Posplayerx >= posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x + map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))) or (Posplayerx < posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x - map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))))) and (diferenciay >= diferenciax && Posplayerx < posEnemy.x)) {
			if (sprite->animation() != MOVE_LEFT) {
				sprite->changeAnimation(MOVE_LEFT);
			}
			posEnemy.x -= 1;
			if (map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32)))
			{
				posEnemy.x += 1;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		else if (!(Posplayery < posEnemy.y && diferenciay > diferenciax && (map->Exists_platform(posEnemy, glm::ivec2(32, 32)) or (Posplayerx >= posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x + map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))) or (Posplayerx < posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x - map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))))) and diferenciay >= diferenciax && Posplayerx > posEnemy.x) {
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
			if (sprite->animation() != ATTACK_LEFT or sprite->animation() != ATTACK_RIGHT) {
				if (sprite->animation() == MOVE_LEFT)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() == MOVE_RIGHT)
					sprite->changeAnimation(STAND_RIGHT);
			}
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
				if (Posplayery < posEnemy.y && diferenciay > diferenciax && (map->Exists_platform(posEnemy, glm::ivec2(32, 32)) or (Posplayerx >= posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x + map->getTileSize(), posEnemy.y), glm::ivec2(32, 32))) or (Posplayerx < posEnemy.x and map->Exists_platform(glm::ivec2(posEnemy.x - map->getTileSize(), posEnemy.y), glm::ivec2(32, 32)))))
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

void Enemy::set_contador_atac(int actualitzacio)
{
	contador_atac = actualitzacio;
}

int Enemy::get_contador_atac()
{
	return contador_atac;
}

void Enemy::update_attack_left(int deltaTime){
	sprite->update(deltaTime);
	if (sprite->animation() != ATTACK_LEFT)
		sprite->changeAnimation(ATTACK_LEFT);

}

void Enemy::update_attack_right(int deltaTime) {
	sprite->update(deltaTime);
	if (sprite->animation() != ATTACK_RIGHT)
		sprite->changeAnimation(ATTACK_RIGHT);
}


bool Enemy::get_collisionDown() {
	//cout << "abans d'entrar a la func" << endl;
	bool hola = map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y);
	//cout << "hola " << hola << endl;
	return hola;
}

void Enemy::set_primera_mort(bool bolea)
{
	Enemic_primera_mort = bolea;
}

bool Enemy::get_primera_mort()
{
	return Enemic_primera_mort;
}

void Enemy::set_Area(int x, int y)
{
	Areax = x;
	Areay = y;
}