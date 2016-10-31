#pragma once

#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"

class Boss
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void setPosition(const glm::vec2 &pos);
	void setTileMap(TileMap *tileMap);
	void render();
	void update(int deltaTime, int Posplayerx, int Posplayery);
	glm::ivec2 get_position() {
		return posBoss;
	}
	void reducir_vida();

private:
	bool bJumping;
	int jumpAngle, startY;
	glm::ivec2 tileMapDispl, posBoss;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

