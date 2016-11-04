#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Boss.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define BOSSIMGPATH "images/boss.png"

enum BossAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, ATTACK
};


void Boss::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	//cout << "aqui entro" << endl;
	Boss_primera_mort = true;
	contador_atac = 0;
	Areax = 0;
	Areay = 0;
	life = 12.f;
	spritesheet.loadFromFile(BOSSIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);

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

	sprite->setAnimationSpeed(ATTACK, 8);
	sprite->addKeyframe(ATTACK, glm::vec2(0.75, 0.f));
	sprite->addKeyframe(ATTACK, glm::vec2(0.75, 0.25f));
	sprite->addKeyframe(ATTACK, glm::vec2(0.75, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBoss.x), float(tileMapDispl.y + posBoss.y)));


	//sprite2
	
}

void Boss::update(int deltaTime, int Posplayerx, int Posplayery)
{
	int diferenciax = abs(posBoss.x - Posplayerx);
	int diferenciay = abs(posBoss.y - Posplayery);
	//sprite2->update(deltaTime);
	sprite->update(deltaTime);
	if (Areax > diferenciax / map->getTileSize() && Areay > diferenciay / map->getTileSize()) {
		if (sprite->animation() != ATTACK) {
			contador_atac = 0;
			if (diferenciay < diferenciax && Posplayerx < posBoss.x) {
				if (sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
				posBoss.x -= 1;
				if (map->collisionMoveLeft(posBoss, glm::ivec2(64, 64)))
				{
					posBoss.x += 1;
					sprite->changeAnimation(STAND_LEFT);
				}
			}
			else if (diferenciay < diferenciax && Posplayerx > posBoss.x) {
				if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
				posBoss.x += 1;
				if (map->collisionMoveRight(posBoss, glm::ivec2(64, 64)))
				{
					posBoss.x -= 1;
					sprite->changeAnimation(STAND_RIGHT);
				}
			}
			else if (!(Posplayery < posBoss.y && diferenciay > diferenciax && (map->Exists_platform(posBoss, glm::ivec2(64, 64)) or (Posplayerx >= posBoss.x and map->Exists_platform(glm::ivec2(posBoss.x + map->getTileSize(), posBoss.y), glm::ivec2(64, 64))) or (Posplayerx < posBoss.x and map->Exists_platform(glm::ivec2(posBoss.x - map->getTileSize(), posBoss.y), glm::ivec2(64, 64))))) and (diferenciay >= diferenciax && Posplayerx < posBoss.x)) {
				if (sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
				posBoss.x -= 1;
				if (map->collisionMoveLeft(posBoss, glm::ivec2(64, 64)))
				{
					posBoss.x += 1;
					sprite->changeAnimation(STAND_LEFT);
				}
			}
			else if (!(Posplayery < posBoss.y && diferenciay > diferenciax && (map->Exists_platform(posBoss, glm::ivec2(64, 64)) or (Posplayerx >= posBoss.x and map->Exists_platform(glm::ivec2(posBoss.x + map->getTileSize(), posBoss.y), glm::ivec2(64, 64))) or (Posplayerx < posBoss.x and map->Exists_platform(glm::ivec2(posBoss.x - map->getTileSize(), posBoss.y), glm::ivec2(64, 64))))) and (diferenciay >= diferenciax && Posplayerx > posBoss.x)) {
				if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
				posBoss.x += 1;
				if (map->collisionMoveRight(posBoss, glm::ivec2(64, 64)))
				{
					posBoss.x -= 1;
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
					posBoss.y = startY;
				}
				else
				{
					posBoss.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
					if (jumpAngle > 90)
						bJumping = !map->collisionMoveDown(posBoss, glm::ivec2(64, 64), &posBoss.y);
				}
			}
			else
			{
				posBoss.y += FALL_STEP;
				if (map->collisionMoveDown(posBoss, glm::ivec2(64, 64), &posBoss.y))
				{
					if (Posplayery < posBoss.y && diferenciay > diferenciax && (map->Exists_platform(posBoss, glm::ivec2(64, 64)) or (Posplayerx >= posBoss.x and map->Exists_platform(glm::ivec2(posBoss.x + map->getTileSize(), posBoss.y), glm::ivec2(64, 64))) or (Posplayerx < posBoss.x and map->Exists_platform(glm::ivec2(posBoss.x - map->getTileSize(), posBoss.y), glm::ivec2(64, 64)))))
					{
						bJumping = true;
						jumpAngle = 0;
						startY = posBoss.y;
					}
					/*else {
						if (diferenciay >= diferenciax && Posplayerx < posBoss.x) {
							if (sprite->animation() != MOVE_LEFT)
								sprite->changeAnimation(MOVE_LEFT);
							posBoss.x -= 1;
							if (map->collisionMoveLeft(posBoss, glm::ivec2(64, 64)))
							{
								posBoss.x += 1;
								sprite->changeAnimation(STAND_LEFT);
							}
						}
						else if (diferenciay >= diferenciax && Posplayerx > posBoss.x) {
							if (sprite->animation() != MOVE_RIGHT)
								sprite->changeAnimation(MOVE_RIGHT);
							posBoss.x += 1;
							if (map->collisionMoveRight(posBoss, glm::ivec2(64, 64)))
							{
								posBoss.x -= 1;
								sprite->changeAnimation(STAND_RIGHT);
							}
						}
						else {//animacions
							if (sprite->animation() == MOVE_LEFT)
								sprite->changeAnimation(STAND_LEFT);
							else if (sprite->animation() == MOVE_RIGHT)
								sprite->changeAnimation(STAND_RIGHT);
						}
					}*/
				}
			}
		}
		else {
			contador_atac = contador_atac + deltaTime;
			if (contador_atac >= 1000) sprite->changeAnimation(STAND_RIGHT);
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBoss.x), float(tileMapDispl.y + posBoss.y)));
}


void Boss::render()
{
	sprite->render();
}

float Boss::get_life()
{
	return life;
}

void Boss::set_primera_mort(bool bolea)
{
	Boss_primera_mort = bolea;
}

bool Boss::get_primera_mort()
{
	return Boss_primera_mort;
}

void Boss::set_life(float resta)
{
	life = life - resta;
}

void Boss::set_Area(int x, int y)
{
	Areax = x;
	Areay = y;
}

void Boss::setPosition(const glm::vec2 &pos)
{
	posBoss = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBoss.x), float(tileMapDispl.y + posBoss.y)));
}

void Boss::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Boss::update_attack(int deltaTime) {
	//sprite2->update(deltaTime);
	if (sprite->animation() != ATTACK)
		sprite->changeAnimation(ATTACK);
	
	/*if (sprite2->animation() != 0) {
		sprite2->changeAnimation(0);
	}*/
}