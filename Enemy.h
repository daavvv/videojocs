#pragma once

#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"


class Enemy
{
public:
	void update_attack_left(int deltaTime);
	void update_attack_right(int deltaTime);
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void setPosition(const glm::vec2 &pos);
	void setTileMap(TileMap *tileMap);
	void render();
	bool get_collisionDown();
	void set_Area(int x, int y);
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
	void set_contador_atac(int actualitzacio);
	int get_contador_atac();
private:
	int contador_atac;
	bool bJumping;
	int jumpAngle, startY;
	int Areax, Areay;
	glm::ivec2 tileMapDispl, posEnemy;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	float life;
};

