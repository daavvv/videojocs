#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Game.h"


void Game::init()
{
	MaterialsInventory = 4;
	bMaterialInventoryOpened = false;
	bPlay = true;
	glClearColor(0.87f, 0.98f, 1.0f, 1.0f);
	scene.init();
	ui.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	ui.update(deltaTime);
	return bPlay;
}



void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	/*
	cout << glutGet(GLUT_WINDOW_WIDTH) << ' ' << x << endl;
	cout << glutGet(GLUT_WINDOW_HEIGHT) << ' ' << y << endl;
	int centrex = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centrey = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	int puntx = x - centrex;
	int punty = y - centrey;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//store the x,y value where the click happened
		cout << "he clicat" << endl;
		if (abs(puntx) > abs(punty)) {
			if (puntx > 0) {
				cout << "dreta" << endl;
			}
			else {
				cout << "esquerra" << endl;
			}
		}
		else {
			if (punty < 0) {
				cout << "adalt" << endl;
			}
			else {
				cout << "abaix" << endl;
			}
		}
	}*/


	cout << "clicked on " << x << "," << y << endl;

	//Esto dejamelo así please
	if (bMaterialInventoryOpened) {
		ui.click(x, y);
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





