#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

//void OnMouseClick(int button, int state, int x, int y);
struct Item {
	Item() :buildable(false), ID(0), type("none"), amount(0) {}
	bool buildable;
	string type;
	int ID;
	int amount;
};

struct PersonalItem {
	PersonalItem() :weapon(true){}
	bool weapon;
	string type;
};


class Player
{




public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	void loadSprite();
	int get_attack_power();

	void crear(int button, int x, int y);
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void printPosition();
	void setBuildTile(int tileID);
	void addItemToBag(int tileID);
	bool isItemInBag(int tileID);
	bool isEnoughAmount(int tileID);
	bool hasWeapon(string type);
	void substractOne(int tileID);
	void addPersonalItem(bool weapon, string type);
	void substractMaterialToPlayer(int ID, int amount);
	float getLife();
	int getGoldCoins();
	int getAmountOfMaterial(int ID);
	void setWeapon(string type);
	vector<Item> getBag();
	vector<PersonalItem> getPersonalItems();
	void setLife(float life);
	glm::ivec2 getPosition();
	
private:
	bool canjump;
	int attackpower;
	string weapon;
	bool bJumping,bdownLadder,bdigging, bbuilding;
	int dig, build, buildTile, goldcoins;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Texture swordTex;
	Texture axeTex;
	Sprite *sprite;
	Sprite *sword;
	Sprite *axe;
	TileMap *map;
	float life;
	int digCounter,buildCounter;
	vector<Item> bag;
	vector<PersonalItem> personalItems;

};


#endif // _PLAYER_INCLUDE


