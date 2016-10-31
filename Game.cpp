#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Game.h"


void Game::init()
{
	gameInitialized = true;
	MaterialsInventory = 4;
	bMaterialInventoryOpened = false;
	bPlay = true;
	glClearColor(0.87f, 0.98f, 1.0f, 1.0f);

	ui.init();
	if (gameInitialized) {
		scene.init();
	}
}

bool Game::update(int deltaTime)
{
	if (gameInitialized) {
		scene.update(deltaTime);
		return bPlay;
	}
	ui.update(deltaTime);
}



void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	



	if (gameInitialized) {
		float playerlife = scene.getPlayerLife();
		scene.render();
		ui.render(playerlife);

		if (getKey('i')) {
			if (MaterialsInventory == 4 && !bMaterialInventoryOpened) {
				MaterialsInventory--;
				return;
			}
			if (MaterialsInventory == 2 && bMaterialInventoryOpened) {
				MaterialsInventory--;
				return;
			}
		}
		else {
			if (MaterialsInventory == 3) {
				vector<Item> bag = scene.getPlayerBag();
				ui.updateBag(bag);
				ui.renderMaterialInventory();
				MaterialsInventory--;
				bMaterialInventoryOpened = true;
			}
			if (MaterialsInventory == 1) {
				MaterialsInventory = 4;
				bMaterialInventoryOpened = false;
			}

			if (bMaterialInventoryOpened) {
				ui.renderMaterialInventory();
			}
		}
	}
	else {
		ui.renderMainMenu();
	}
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button, int x, int y)
{


	cout << "clicked on " << x << "," << y << endl;

	//Esto dejamelo así please

	if (!gameInitialized) {
		string menu;
		ui.clickOnMenu(x, y, &menu);
	}

	if (gameInitialized) {
		if (bMaterialInventoryOpened) {
			int tile;
			if (ui.clickOnInventoryItem(x, y, &tile)) {
				cout << "Tile:" << tile << endl;
				scene.setBuildTile(tile);
			}
		}
		scene.mouse_clicked(button, x, y);
	}
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





