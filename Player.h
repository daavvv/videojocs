#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

void OnMouseClick(int button, int state, int x, int y);
struct Item {
	Item() :buildable(false), ID(0), type("none"), amount(0) {}
	bool buildable;
	string type;
	int ID;
	int amount;
};


class Player
{




public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void printPosition();
	void addItemToBag(int tileID);
	bool isItemInBag(int tileID);
	float getLife();
	vector<Item> getBag();
	void setLife(float life);
	glm::ivec2 getPosition();
	
private:
	bool bJumping,bdownLadder,bdigging, bbuilding;
	int dig, build;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	float life;
	int digCounter,buildCounter;
	vector<Item> bag;

};


#endif // _PLAYER_INCLUDE


