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
	void updatePersonalItems(const vector<PersonalItem>& personalItems);
	void render(float playerlife,int goldCoins);
	void renderMainMenu(bool dead);
	void initShaders();
	void renderHearts(float life);
	void renderMaterialInventory();
	void renderWeaponsInventory();
	void renderObjectsInInventory();
	void renderCounters();
	void renderGoldCoins(int goldCoins);
	void renderWeaponPopup(string type);
	bool clickOnInventoryItem(int x, int y, int *tile);
	bool clickOnMenu(int x, int y, string *menu, bool dead);
	bool clickOnPopup(int x, int y, bool dead);
	bool clickOnWeaponsBar(int x, int y, string *type);
	void setupLeftMaterialBar(ShaderProgram &program);
	void addUIElement(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program, string path);
	void addInventoryItem(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program, string type, int amount);

private:
	bool swordPopupOpened;
	float currentTime;
	bool playButtonOver;
	glm::mat4 projection;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	ShaderProgram UIProgram;
	TexturedQuad* weaponsInventory;
	TexturedQuad* weaponPopup;
	TexturedQuad* goldCoins;
	TexturedQuad* goldCoinsCounter;
	TexturedQuad* highlight;
	TexturedQuad* menuBackground;
	TexturedQuad* playButton;
	TexturedQuad* exitButton;
	TexturedQuad* instructionsButton;
	Texture swordTex, axeTex;
	Texture onealt, twoalt, threealt, fouralt, fivealt, sixalt, sevenalt, eightalt, ninealt, tenalt, twentyalt, thirtyalt, fortyalt, fiftyalt, sixtyalt, seventyalt, eightyalt, ninetyalt, onehundredalt;
	Texture weaponsInventoryTex,swordPopupTex,axePopupTex,dirt, grass, stone, iron, zero, one, two, three, four, five, six, seven, eight, nine, ten, hightlight, menuBackgroundTex, playButtonTex, playAgainButtonTex, instructionsButtonTex, exitButtonTex, goldCoinsTex, goldCoinsCounterTex;
	vector<TexturedQuad*> UIElements, MaterialsLeftBar,CountersLeftBar;
	vector<TexturedQuad*> Inventory;
	vector<TexturedQuad*> CountersBox;
	vector<TexturedQuad*> personalItems;
	vector<int> ids;
	vector<string> weaponTypes;
	vector<Texture> textures, inventoryTextures, Counters,personalItemsTextures;
	int selectedItem,selectedItemID;
};


#endif // _SCENE_INCLUDE

