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
	void render(float playerlife);
	void renderMainMenu();
	void initShaders();
	void renderHearts(float life);
	void renderMaterialInventory();
	void renderObjectsInInventory();
	void renderCounters();
	bool clickOnInventoryItem(int x, int y, int *tile);
	bool clickOnMenu(int x, int y, string *menu);
	void setupLeftMaterialBar(ShaderProgram &program);
	void addUIElement(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program, string path);
	void addInventoryItem(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program, string type, int amount);

private:
	float currentTime;
	glm::mat4 projection;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	ShaderProgram UIProgram;
	TexturedQuad* highlight;
	TexturedQuad* menuBackground;
	TexturedQuad* playButton;
	TexturedQuad* instructionsButton;
	Texture stone,grass,zero,one,two,three,four,five,six,seven,eight,nine,ten,hightlight,menuBackgroundTex,playButtonTex,instructonsButtonTex;
	vector<TexturedQuad*> UIElements, MaterialsLeftBar,CountersLeftBar;
	vector<TexturedQuad*> Inventory;
	vector<TexturedQuad*> CountersBox;
	vector<int> ids;
	vector<Texture> textures, inventoryTextures, Counters;
	int selectedItem,selectedItemID;
};


#endif // _SCENE_INCLUDE

