#pragma once

#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"


class Enemy
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void setPosition(const glm::vec2 &pos);
	void setTileMap(TileMap *tileMap);
	void render();
	bool get_enemy_bjumping() {
		return bJumping;
	}
	void update(int deltaTime, int Posplayerx, int Posplayery);
	glm::ivec2 get_position() {
		return posEnemy;
	}
	void set_life(float resta);
	float get_life() {
		return life;
	}

private:
	bool bJumping;
	int jumpAngle, startY;
	glm::ivec2 tileMapDispl, posEnemy;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	float life;
};

