#ifndef _UI_INCLUDE
#define _UI_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TexturedQuad.h"
#include "Texture.h"
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include "Player.h"


using namespace std;


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class UI
{

public:
	UI(){}

	void init();
	void update(int deltaTime);
	void updateBag(const vector<Item>& bag);
	void render(float playerlife,int goldCoins);
	void renderMainMenu(bool dead);
	void initShaders();
	void renderHearts(float life);
	void renderMaterialInventory();
	void renderObjectsInInventory();
	void renderCounters();
	void renderGoldCoins(int goldCoins);
	bool clickOnInventoryItem(int x, int y, int *tile);
	bool clickOnMenu(int x, int y, string *menu, bool dead);
	void setupLeftMaterialBar(ShaderProgram &program);
	void addUIElement(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program, string path);
	void addInventoryItem(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program, string type, int amount);

private:
	float currentTime;
	bool playButtonOver;
	glm::mat4 projection;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	ShaderProgram UIProgram;
	TexturedQuad* goldCoins;
	TexturedQuad* goldCoinsCounter;
	TexturedQuad* highlight;
	TexturedQuad* menuBackground;
	TexturedQuad* playButton;
	TexturedQuad* exitButton;
	TexturedQuad* instructionsButton;
	Texture onealt, twoalt, threealt, fouralt, fivealt, sixalt, sevenalt, eightalt, ninealt, tenalt, twentyalt, thirtyalt, fortyalt, fiftyalt, sixtyalt, seventyalt, eightyalt, ninetyalt, onehundredalt;
	Texture stone,grass,zero,one,two,three,four,five,six,seven,eight,nine,ten,hightlight,menuBackgroundTex,playButtonTex,playAgainButtonTex,instructionsButtonTex,exitButtonTex,goldCoinsTex,goldCoinsCounterTex;
	vector<TexturedQuad*> UIElements, MaterialsLeftBar,CountersLeftBar;
	vector<TexturedQuad*> Inventory;
	vector<TexturedQuad*> CountersBox;
	vector<int> ids;
	vector<Texture> textures, inventoryTextures, Counters;
	int selectedItem,selectedItemID;
};


#endif // _SCENE_INCLUDE

