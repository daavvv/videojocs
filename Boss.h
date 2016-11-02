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
	float get_life();
	void set_life(float resta);
	void update(int deltaTime, int Posplayerx, int Posplayery);
	void update_attack(int deltaTime);
	glm::ivec2 get_position() {
		return posBoss;
	}

private:
	int contador_atac;
	float life;
	bool bJumping;
	int jumpAngle, startY;
	glm::ivec2 tileMapDispl, posBoss;
	Texture spritesheet, spritesheet2;
	Sprite *sprite, *sprite2;
	TileMap *map;
};

