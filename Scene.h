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
	float getPlayerLife();
	int getGoldCoins();
	vector<Item> getPlayerBag();
	
	

private:
	bool ataca_enemic();
	void initShaders();

private:
	int contador;
	bool isPlayerDead;
	Boss *boss;
	TileMap *map;
	Player *player;
	Enemy *enemy;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

