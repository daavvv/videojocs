#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	
	void mouse_clicked(int button, int x, int y);
	void init();
	void update(int deltaTime);
	void render();
	void setBuildTile(int tileID);
	void addPersonalItemToPlayer(bool weapon, string type);
	float getPlayerLife();
	bool checkIfPlayerHasWeapon(string type);
	int getGoldCoins();
	void setPlayerWeapon(string type);
	void substractMaterialToPlayer(int ID, int amount);
	vector<Item> getPlayerBag();
	vector<PersonalItem> getPlayerPersonalItems();
	
	

private:
	bool ataca_enemic(int deltaTime, Enemy *enemic);
	bool ataca_boss(int deltaTime);
	void initShaders();

private:
	//bool enableEnemies;
	int ticks;
	int contador;
	bool isPlayerDead;
	Boss *boss;
	TileMap *map;
	Player *player;
	Enemy *enemics[8];
	Enemy *enemy;
	Texture  spritesheet2;
	Sprite *sprite2;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

