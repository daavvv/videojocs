#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Game.h"


void Game::init()
{
	weaponPopUpOpened = false;
	gameInitialized = false;
	startover = false;
	MaterialsInventory = 4;
	bMaterialInventoryOpened = false;
	instructionsWindowOpened = false;
	bPlay = true;
	glClearColor(0.87f, 0.98f, 1.0f, 1.0f);
	scene.init();
	ui.init();
	
}

void Game::setWinId(int id)
{
	this->winID = id;
}

bool Game::update(int deltaTime)
{
	if (gameInitialized) {
		if (scene.getPlayerLife() > 0) {
			scene.update(deltaTime);
			return bPlay;
		}
		else {
			gameInitialized = false;
		}
	}
	ui.update(deltaTime);
}



void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameInitialized) {

		float playerlife = scene.getPlayerLife();
		int goldCoins = scene.getGoldCoins();
		if (playerlife > 0) {
			scene.render();
			ui.render(playerlife,goldCoins);


			vector<Item> bag = scene.getPlayerBag();

			bool canMakeSword = false;
			bool canMakeAxe = false;

			for (int i = 0; i < bag.size(); ++i) {
				if (bag[i].ID == STONE && !canMakeAxe) {
					if (bag[i].amount >= 10) {
						ui.renderWeaponPopup("sword");
						popupType = "sword";
						canMakeSword = true;
						weaponPopUpOpened = true;
					}
				}
				if (bag[i].ID == IRON) {
					if (bag[i].amount >= 20) {
						ui.renderWeaponPopup("axe");
						popupType = "axe";
						canMakeAxe = true;
						weaponPopUpOpened = true;
					}
				}
			}

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
			ui.renderMainMenu(false);
		}
	}
	else if (instructionsWindowOpened){
		//ui.renderMainMenu();
	}
	else if (scene.getPlayerLife() <= 0) {
		ui.renderMainMenu(true);
	}
	else {
		ui.renderMainMenu(false);
	}

}

void Game::keyPressed(int key)
{
	if (key == 27) { // Escape code
		if (gameInitialized) {
			gameInitialized = false;
			startover = true;
			init();
		}
	}
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

void Game::mouseMotionMove(int x, int y)
{

	if (!gameInitialized) {
		string menu;
		bool success = false;
		cout << x << "," << y << endl;

		bool dead = false;
		if (scene.getPlayerLife() > 0) {
			dead = false;
		}
		else {
			dead = true;
		}
		success = ui.clickOnMenu(x, y, &menu, dead);
	}
}

void Game::mousePress(int button, int x, int y)
{


	cout << "clicked on " << x << "," << y << endl;

	//Esto dejamelo así please

	if (!gameInitialized) {
		string menu;
		bool success = false;

		bool dead = false;
		if (scene.getPlayerLife() > 0) {
			dead = false;
		}
		else {
			dead = true;
		}
		success = ui.clickOnMenu(x, y, &menu, dead);

		if (success) {
			if (menu == "play") {
				gameInitialized = true;
				scene.init();
				return;
			}
			if (menu == "exit") {
				bPlay = false;
				glutDestroyWindow(winID);
				return;
			}
			if (menu == "instructions") {
				instructionsWindowOpened = true;
				return;
			}
		}
	}

	if (gameInitialized) {


		string type = "none";
		if (ui.clickOnWeaponsBar(x, y, &type)) {
			//do something
			cout << "click on weapons's bar: " << type << endl;
		}


		if (weaponPopUpOpened) {
			bool success = false;
			success = ui.clickOnPopup(x, y, false);
			if (success) {
				weaponPopUpOpened = false;
				if (popupType == "sword") {
					scene.substractMaterialToPlayer(STONE,10);
					scene.addPersonalItemToPlayer(true, "sword");
				}	
				if (popupType == "axe") {
					scene.addPersonalItemToPlayer(true, "axe");
					scene.substractMaterialToPlayer(IRON, 20);
				}
				vector<PersonalItem> p = scene.getPlayerPersonalItems();
				ui.updatePersonalItems(p);
			}
		}

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





