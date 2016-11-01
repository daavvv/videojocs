#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "UI.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	void setWinId(int id);
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mouseMotionMove(int x, int y);
	void mousePress(int button, int x, int y);
	void mouseRelease(int button);

	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	int winID;
	string popupType;
	bool gameInitialized;
	bool startover;
	bool instructionsWindowOpened;
	bool weaponPopUpOpened;
	bool bPlay, bMaterialInventoryOpened;
	int MaterialsInventory;                       // Continue to play game?
	Scene scene;
	UI ui;// Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time

};


#endif // _GAME_INCLUDE


