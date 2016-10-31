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
	void update(int deltaTime, int Posplayerx, int Posplayery);
	glm::ivec2 get_position() {
		return posEnemy;
	}
	void reducir_vida();

private:
	bool bJumping;
	int jumpAngle, startY;
	glm::ivec2 tileMapDispl, posEnemy;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

