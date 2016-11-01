#include "UI.h"
#include "Game.h"



#define LIFEUIOFFSETX -35
#define LIFEUIOFFSETY -35
#define LIFEUIOFFSETX_PADDING 35
#define LIFESCALEFACTOR  0.2
#define MATERIALSINVENTORYSCALE 4//(SCREEN_WIDTH/2)/165.f

#define PLAYBUTTONSCALEX 2.5f
#define PLAYBUTTONSCALEY 1
#define PLAYBUTTONRAWSCALE 64.f
#define PLAYBUTTONOFFSETY 40

#define EXITBUTTONSCALEX 2.5f
#define EXITBUTTONSCALEY 1
#define EXITBUTTONRAWSCALE 64.f
#define EXITBUTTONOFFSETY 115

#define INSTRUCTIONSBUTTONSCALEX 2.5f
#define INSTRUCTIONSBUTTONSCALEY 1
#define INSTRUCTIONSBUTTONRAWSCALE 64.f
#define INSTRUCTIONSBUTTONOFFSETY 190

#define GOLDCOINSRAWSCALEX 64.f
#define GOLDCOINSRAWSCALEY 64.f
#define GOLDCOINSSCALE 0.5f
#define GOLDCOINSOFFSETX 30
#define GOLDCOINSOFFSETY 75

#define GOLDCOINSCOUNTERRAWSCALEX 64.f
#define GOLDCOINSCOUNTERRAWSCALEY 64.f
#define GOLDCOINSCOUNTERSCALE 0.3f
#define GOLDCOINSCOUNTEROFFSETX GOLDCOINSOFFSETX + 35
#define GOLDCOINSCOUNTEROFFSETY GOLDCOINSOFFSETY



#define MATERIALSUIOFFSETX -35
#define MATERIALSUIOFFSETY 10

#define MATERIALSCALEFACTOR 0.35
#define NUMBERSSEPARATION 40

#define DIRTIMGPATH "images/UI/dirt.png"
#define GRASSIMGPATH "images/UI/grass.png"

#define ZEROIMGPATH "images/UI/numbers/hud_0.png"
#define ONEIMGPATH "images/UI/numbers/hud_1.png"
#define TWOIMGPATH "images/UI/numbers/hud_2.png"
#define THREEIMGPATH "images/UI/numbers/hud_3.png"
#define FOURIMGPATH "images/UI/numbers/hud_4.png"
#define FIVEIMGPATH "images/UI/numbers/hud_5.png"
#define SIXIMGPATH "images/UI/numbers/hud_6.png"
#define SEVENIMGPATH "images/UI/numbers/hud_7.png"
#define EIGHTIMGPATH "images/UI/numbers/hud_8.png"
#define NINEIMGPATH "images/UI/numbers/hud_9.png"
#define HIGHLIGHTIMGPATH "images/UI/highlight.png"
#define MENUBACKGROUNDIMGPATH "images/UI/menuBackground.png"
#define PLAYBUTTONIMGPATH "images/UI/playButton.png"
#define PLAYBUTTONIMGPRESSEDPATH "images/UI/playButtonPressed.png"
#define PLAYAGAINBUTTONIMGPATH "images/UI/playAgainButton.png"
#define PLAYAGAINBUTTONIMGPRESSEDPATH "images/UI/playAgainButtonPressed.png"
#define EXITBUTTONIMGPATH "images/UI/exitButton.png"
#define EXITBUTTONIMGPRESSEDPATH "images/UI/exitButtonPressed.png"
#define INSTRUCTIONSBUTTONIMGPATH "images/UI/instruccionsButton.png"
#define INSTRUCTIONSBUTTONIMGPRESSEDPATH "images/UI/instruccionsButtonPressed.png"
#define GOLDCOINSIMGPATH "images/UI/coins.png"




#define ONEALT "images/UI/numbers_alt/one.png"
#define TWOALT "images/UI/numbers_alt/two.png"
#define THREEALT "images/UI/numbers_alt/three.png"
#define FOURALT "images/UI/numbers_alt/four.png"
#define FIVEALT "images/UI/numbers_alt/five.png"
#define SIXALT "images/UI/numbers_alt/six.png"
#define SEVENALT "images/UI/numbers_alt/seven.png"
#define EIGHTALT "images/UI/numbers_alt/eight.png"
#define NINEALT "images/UI/numbers_alt/nine.png"
#define TENALT "images/UI/numbers_alt/ten.png"
#define TWENTYALT "images/UI/numbers_alt/twenty.png"
#define THIRTYALT "images/UI/numbers_alt/thirty.png"
#define FORTYALT "images/UI/numbers_alt/forty.png"
#define FIFTYALT "images/UI/numbers_alt/fifty.png"
#define SIXTYALT "images/UI/numbers_alt/sixty.png"
#define SEVENTYALT "images/UI/numbers_alt/seventy.png"
#define EIGHTYALT "images/UI/numbers_alt/eighty.png"
#define NINETYALT "images/UI/numbers_alt/ninety.png"
#define ONEHUNDREDALT "images/UI/numbers_alt/one-hundred.png"



#define INVENTORYITEMRAWSCALEX 64.f
#define INVENTORYITEMRAWSCALEY 64.f
#define INVENTORYITEMSCALE 0.5
#define INVENTORYITEMSOFFSETX float(232 * SCREEN_WIDTH / 640)
#define INVENTORYITEMSOFFSETY float(122*SCREEN_HEIGHT/480)
#define INVENTORYITEMPADDINGX float(INVENTORYITEMRAWSCALEX*INVENTORYITEMSCALE + float(3.5f*SCREEN_WIDTH/640))
#define INVENTORYITEMPADDINGY float(INVENTORYITEMRAWSCALEY*INVENTORYITEMSCALE + float(3.5f*SCREEN_HEIGHT/640))

#define INVENTORYCOUNTERSCALE 0.2

void UI::init(){
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(128.f, 128.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	selectedItem = -1;
	playButtonOver = false;

	initShaders();

	if (menuBackgroundTex.loadFromFile(MENUBACKGROUNDIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	
	if (playButtonTex.loadFromFile(PLAYBUTTONIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}

	if (playAgainButtonTex.loadFromFile(PLAYAGAINBUTTONIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}

	if (exitButtonTex.loadFromFile(EXITBUTTONIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}

	if (instructionsButtonTex.loadFromFile(INSTRUCTIONSBUTTONIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	if (goldCoinsTex.loadFromFile(GOLDCOINSIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}



	if (hightlight.loadFromFile(HIGHLIGHTIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	if (dirt.loadFromFile(DIRTIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}

	if (grass.loadFromFile(GRASSIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}

	if (zero.loadFromFile(ZEROIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (one.loadFromFile(ONEIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (two.loadFromFile(TWOIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (three.loadFromFile(THREEIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (four.loadFromFile(FOURIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (five.loadFromFile(FIVEIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (six.loadFromFile(SIXIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (seven.loadFromFile(SEVENIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (eight.loadFromFile(EIGHTIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (nine.loadFromFile(NINEIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}


	if (onealt.loadFromFile(ONEALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (twoalt.loadFromFile(TWOALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (threealt.loadFromFile(THREEALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (fouralt.loadFromFile(FOURALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (fivealt.loadFromFile(FIVEALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (sixalt.loadFromFile(SIXALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (sevenalt.loadFromFile(SEVENALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (eightalt.loadFromFile(EIGHTALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (ninealt.loadFromFile(NINEALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (tenalt.loadFromFile(TENALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (twentyalt.loadFromFile(TWENTYALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (thirtyalt.loadFromFile(THIRTYALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (fortyalt.loadFromFile(FORTYALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (fiftyalt.loadFromFile(FIFTYALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (sixtyalt.loadFromFile(SIXTYALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (seventyalt.loadFromFile(SEVENTYALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (eightyalt.loadFromFile(EIGHTYALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (ninetyalt.loadFromFile(NINETYALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	if (onehundredalt.loadFromFile(ONEHUNDREDALT, TEXTURE_PIXEL_FORMAT_RGBA)) {
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}

	//LOAD HEARTS
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f,1.f); 
	addUIElement(geom, texCoords, UIProgram, "images/UI/UI_HEART_FULL.png");//0
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	addUIElement(geom, texCoords, UIProgram, "images/UI/UI_HEART_HALF.png");//1
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	addUIElement(geom, texCoords, UIProgram, "images/UI/UI_HEART_EMPTY.png");//2

	//LOAD GOLD COINS
	geom[0] = glm::vec2(0.f, 0.f);
	geom[1] = glm::vec2(64.f, 64.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	goldCoins = TexturedQuad::createTexturedQuad(geom, texCoords, UIProgram);

	//LOAD GOLD COINS COUNTER
	geom[0] = glm::vec2(0.f, 0.f);
	geom[1] = glm::vec2(64.f, 64.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	goldCoinsCounter = TexturedQuad::createTexturedQuad(geom, texCoords, UIProgram);

	//LOAD MATERIAL INVENTORY HUD
	geom[0] = glm::vec2(0.f, 0.f);
	geom[1] = glm::vec2(64.f, 64.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	addUIElement(geom, texCoords, UIProgram, "images/UI/materials.png");//3

	
	//LOAD HIGHLIGHT
	geom[0] = glm::vec2(0.f, 0.f);
	geom[1] = glm::vec2(64.f, 64.f);
	highlight = TexturedQuad::createTexturedQuad(geom, texCoords, UIProgram);


	//LOAD MAIN MENU


	//LOAD BACKGROUND
	geom[0] = glm::vec2(0.f, 0.f);
	geom[1] = glm::vec2(64.f, 64.f);
	menuBackground = TexturedQuad::createTexturedQuad(geom, texCoords, UIProgram);


	//LOAD PLAY BUTTON
	geom[0] = glm::vec2(0.f, 0.f);
	geom[1] = glm::vec2(PLAYBUTTONRAWSCALE, PLAYBUTTONRAWSCALE);
	playButton = TexturedQuad::createTexturedQuad(geom, texCoords, UIProgram);
	
	//LOAD EXIT BUTTON
	geom[0] = glm::vec2(0.f, 0.f);
	geom[1] = glm::vec2(EXITBUTTONRAWSCALE, EXITBUTTONRAWSCALE);
	exitButton = TexturedQuad::createTexturedQuad(geom, texCoords, UIProgram);

	//LOAD INSTRUCTIONS BUTTON
	geom[0] = glm::vec2(0.f, 0.f);
	geom[1] = glm::vec2(INSTRUCTIONSBUTTONRAWSCALE, INSTRUCTIONSBUTTONRAWSCALE);
	instructionsButton = TexturedQuad::createTexturedQuad(geom, texCoords, UIProgram);




	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	

}

void UI::addUIElement(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program, string path){
	TexturedQuad *texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, program);
	UIElements.push_back(texQuad);
	Texture tex;
	if(tex.loadFromFile(path,TEXTURE_PIXEL_FORMAT_RGBA)){
		cout << "loaded" << endl;
	}
	else {
		cout << "not loaded" << endl;
	}
	textures.push_back(tex);
}

void UI::addInventoryItem(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program, string type,int amount) {
	TexturedQuad *texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, program);
	TexturedQuad *texQuadCount = TexturedQuad::createTexturedQuad(geom, texCoords, program);
	Inventory.push_back(texQuad);
	CountersBox.push_back(texQuadCount);
	
	if (amount == 1) {
		Counters.push_back(one);
	}
	if (amount == 2) {
		Counters.push_back(two);
	}
	if (amount == 3) {
		Counters.push_back(three);
	}
	if (amount == 4) {
		Counters.push_back(four);
	}
	if (amount == 5) {
		Counters.push_back(five);
	}
	if (amount == 6) {
		Counters.push_back(six);
	}
	if (amount == 7) {
		Counters.push_back(seven);
	}
	if (amount == 8) {
		Counters.push_back(eight);
	}
	if (amount == 9) {
		Counters.push_back(nine);
	}
	
	if (type == "dirt") {
		inventoryTextures.push_back(dirt);
	}
	if (type == "grass") {
		inventoryTextures.push_back(grass);
	}
}


void UI::initShaders(){
	
	Shader vShader, fShader;
	vShader.initFromFile(VERTEX_SHADER, "shaders/UI.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/UI.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	UIProgram.init();
	UIProgram.addShader(vShader);
	UIProgram.addShader(fShader);
	UIProgram.link();
	if(!UIProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << UIProgram.log() << endl << endl;
	}
	UIProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void UI::update(int deltaTime){
	currentTime += deltaTime;
}

void UI::updateBag(const vector<Item>& bag)
{

	for (int i = 0; i < Inventory.size(); ++i) {
		Inventory[i]->free();
		CountersBox[i]->free();
		delete Inventory[i];
		delete CountersBox[i];
	}
	ids.clear();
	CountersBox.clear();
	Inventory.clear();
	inventoryTextures.clear();
	Counters.clear();

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(INVENTORYITEMRAWSCALEX, INVENTORYITEMRAWSCALEY) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	int bagSize = bag.size();

	cout << "Print bag size:" << bagSize << endl;

	bool exists = false;

	for (int i = 0; i < bagSize; ++i) {


		if (selectedItemID == bag[i].ID && bag[i].amount > 0 && selectedItem != -1) {
			exists = true;
		}

		if (bag[i].ID == DIRT && bag[i].amount > 0) {
			addInventoryItem(geom, texCoords, UIProgram, "dirt",bag[i].amount);//0
			ids.push_back(bag[i].ID);
		}
		if (bag[i].ID == GRASS && bag[i].amount > 0) {
			addInventoryItem(geom, texCoords, UIProgram, "grass", bag[i].amount);//0
			ids.push_back(bag[i].ID);
		}
	}

	if (!exists) {
		selectedItem = -1;
	}
}





void UI::renderMaterialInventory() {

	glm::mat4 modelview;
	UIProgram.use();
	UIProgram.setUniformMatrix4f("projection", projection);
	UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(float(SCREEN_WIDTH/2),float(SCREEN_HEIGHT/2), 0.f));
	//modelview = glm::translate(modelview, glm::vec3(32.f, 32.f, 0.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::scale(modelview, glm::vec3(MATERIALSINVENTORYSCALE, MATERIALSINVENTORYSCALE*424/274, 0));
	modelview = glm::translate(modelview, glm::vec3(-32.f, -32.f, 0.f));
	UIProgram.setUniformMatrix4f("modelview", modelview);
	UIElements[3]->render(textures[3]);

	renderObjectsInInventory();
	renderCounters();
}


void UI::renderObjectsInInventory() {

	int index = 0;

	for (int i = 0; i < Inventory.size(); ++i) {
		glm::mat4 modelview;
		UIProgram.use();
		UIProgram.setUniformMatrix4f("projection", projection);
		UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(INVENTORYITEMSOFFSETX + (i%6)*INVENTORYITEMPADDINGX, INVENTORYITEMSOFFSETY + (i/6)*INVENTORYITEMPADDINGY, 0.f));
		//modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
		//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
		modelview = glm::scale(modelview, glm::vec3(INVENTORYITEMSCALE, INVENTORYITEMSCALE, 0.f));
		modelview = glm::translate(modelview, glm::vec3(-32.f, -32.f, 0.f));
		UIProgram.setUniformMatrix4f("modelview", modelview);
		Inventory[i]->render(inventoryTextures[i]);
	}


	if (selectedItem != -1) {
		glm::mat4 modelview;
		UIProgram.use();
		UIProgram.setUniformMatrix4f("projection", projection);
		UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(INVENTORYITEMSOFFSETX + (selectedItem % 6)*INVENTORYITEMPADDINGX, INVENTORYITEMSOFFSETY + (selectedItem / 6)*INVENTORYITEMPADDINGY, 0.f));
		//modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
		//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
		modelview = glm::scale(modelview, glm::vec3(INVENTORYITEMSCALE, INVENTORYITEMSCALE, 0.f));
		modelview = glm::translate(modelview, glm::vec3(-32.f, -32.f, 0.f));
		UIProgram.setUniformMatrix4f("modelview", modelview);
		highlight->render(hightlight);
	}
}

void UI::renderCounters() {
	for (int i = 0; i < CountersBox.size(); ++i) {
		glm::mat4 modelview;
		UIProgram.use();
		UIProgram.setUniformMatrix4f("projection", projection);
		UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(INVENTORYITEMSOFFSETX + float(i % 6)*INVENTORYITEMPADDINGX + float(INVENTORYITEMSCALE*INVENTORYITEMRAWSCALEX/2) - (INVENTORYITEMPADDINGX - INVENTORYITEMSCALE*INVENTORYITEMRAWSCALEX), INVENTORYITEMSOFFSETY + (i / 6)*INVENTORYITEMPADDINGY+ float(INVENTORYITEMSCALE*INVENTORYITEMRAWSCALEY/2) - (INVENTORYITEMPADDINGY - INVENTORYITEMSCALE*INVENTORYITEMRAWSCALEY), 0.f));
		//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
		modelview = glm::scale(modelview, glm::vec3(INVENTORYCOUNTERSCALE, INVENTORYCOUNTERSCALE, INVENTORYCOUNTERSCALE));
		modelview = glm::translate(modelview, glm::vec3(-32.f, -32.f, 0.f));
		UIProgram.setUniformMatrix4f("modelview", modelview);
		CountersBox[i]->render(Counters[i]);
	}
}

void UI::renderGoldCoins(int goldCoinsAmount)
{


	if (goldCoinsAmount > 0) {
		glm::mat4 modelview;
		UIProgram.use();
		UIProgram.setUniformMatrix4f("projection", projection);
		UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(GOLDCOINSOFFSETX, GOLDCOINSOFFSETY, 0));
		//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
		modelview = glm::scale(modelview, glm::vec3(GOLDCOINSSCALE, GOLDCOINSSCALE, GOLDCOINSSCALE));
		modelview = glm::translate(modelview, glm::vec3(-32.f, -32.f, 0.f));
		UIProgram.setUniformMatrix4f("modelview", modelview);
		goldCoins->render(goldCoinsTex);

		
		UIProgram.use();
		UIProgram.setUniformMatrix4f("projection", projection);
		UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(GOLDCOINSCOUNTEROFFSETX, GOLDCOINSCOUNTEROFFSETY, 0));
		//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
		modelview = glm::scale(modelview, glm::vec3(GOLDCOINSCOUNTERSCALE, GOLDCOINSCOUNTERSCALE, 0));
		modelview = glm::translate(modelview, glm::vec3(-32.f, -32.f, 0.f));
		UIProgram.setUniformMatrix4f("modelview", modelview);

		if (goldCoinsAmount == 1) {
			goldCoinsCounter->render(onealt); // TODO 
		}
		if (goldCoinsAmount == 2) {
			goldCoinsCounter->render(twoalt); // TODO 
		}
		if (goldCoinsAmount == 3) {
			goldCoinsCounter->render(threealt); // TODO 
		}
		if (goldCoinsAmount == 4) {
			goldCoinsCounter->render(fouralt); // TODO 
		}
		if (goldCoinsAmount == 5) {
			goldCoinsCounter->render(fivealt); // TODO 
		}
		if (goldCoinsAmount == 6) {
			goldCoinsCounter->render(sixalt); // TODO 
		}
		if (goldCoinsAmount == 7) {
			goldCoinsCounter->render(sevenalt); // TODO 
		}
		if (goldCoinsAmount == 8) {
			goldCoinsCounter->render(eightalt); // TODO 
		}
		if (goldCoinsAmount == 9) {
			goldCoinsCounter->render(ninealt); // TODO 
		}
		if (goldCoinsAmount >= 10 && goldCoinsAmount < 20) {
			goldCoinsCounter->render(tenalt); // TODO 
		}
		if (goldCoinsAmount >= 20 && goldCoinsAmount < 30) {
			goldCoinsCounter->render(twentyalt); // TODO 
		}
		if (goldCoinsAmount >= 30 && goldCoinsAmount < 40) {
			goldCoinsCounter->render(thirtyalt); // TODO 
		}
		if (goldCoinsAmount >= 40 && goldCoinsAmount < 50) {
			goldCoinsCounter->render(fortyalt); // TODO 
		}
		if (goldCoinsAmount >= 50 && goldCoinsAmount < 60) {
			goldCoinsCounter->render(fiftyalt); // TODO 
		}
		if (goldCoinsAmount >= 60 && goldCoinsAmount < 70) {
			goldCoinsCounter->render(sixtyalt); // TODO 
		}
		if (goldCoinsAmount >= 70 && goldCoinsAmount < 80) {
			goldCoinsCounter->render(seventyalt); // TODO 
		}
		if (goldCoinsAmount >= 80 && goldCoinsAmount < 90) {
			goldCoinsCounter->render(eightyalt); // TODO 
		}
		if (goldCoinsAmount >= 90 && goldCoinsAmount < 100) {
			goldCoinsCounter->render(ninetyalt); // TODO 
		}
		if (goldCoinsAmount == 100) {
			goldCoinsCounter->render(onehundredalt); // TODO 
		}
	}
}





bool UI::clickOnMenu(int x, int y, string* menu, bool dead) {

	
	double left, right, top, bottom;
	left = (SCREEN_WIDTH/2) - (PLAYBUTTONSCALEX*PLAYBUTTONRAWSCALE) / 2;
	right = left + (PLAYBUTTONSCALEX*PLAYBUTTONRAWSCALE);
	top = ((SCREEN_HEIGHT/2)+PLAYBUTTONOFFSETY) - ((PLAYBUTTONSCALEY*PLAYBUTTONRAWSCALE) / 2);
	bottom = top + (PLAYBUTTONSCALEY*PLAYBUTTONRAWSCALE);

	/*
	cout << "left: " << left << endl;
	cout << "right: " << right << endl;
	cout << "top: " << top << endl;
	cout << "bottom: " << bottom << endl;
	*/

	if (x >= left && x <= right && y >= top && y <= bottom) {
		cout << "inside play button" << endl;
		*menu = "play";

		/*
		if (!dead) {
			if (playButtonTex.loadFromFile(PLAYBUTTONIMGPRESSEDPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
				//renderMainMenu();
			}
		}
		else {
			if (playAgainButtonTex.loadFromFile(PLAYAGAINBUTTONIMGPRESSEDPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
				//renderMainMenu();
			}
		}
		*/
		return true;
	}

	left = (SCREEN_WIDTH / 2) - (EXITBUTTONSCALEX*EXITBUTTONRAWSCALE) / 2;
	right = left + (EXITBUTTONSCALEX*EXITBUTTONRAWSCALE);
	top = ((SCREEN_HEIGHT / 2) + EXITBUTTONOFFSETY) - ((EXITBUTTONSCALEY*EXITBUTTONRAWSCALE) / 2);
	bottom = top + (EXITBUTTONSCALEY*EXITBUTTONRAWSCALE);


	if (x >= left && x <= right && y >= top && y <= bottom) {
		cout << "inside exit button" << endl;
		*menu = "exit";

		/*
		if (exitButtonTex.loadFromFile(EXITBUTTONIMGPRESSEDPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
			//renderMainMenu();
		}
		*/
		return true;
	}


	left = (SCREEN_WIDTH / 2) - (INSTRUCTIONSBUTTONSCALEX*INSTRUCTIONSBUTTONRAWSCALE) / 2;
	right = left + (INSTRUCTIONSBUTTONSCALEX*INSTRUCTIONSBUTTONRAWSCALE);
	top = ((SCREEN_HEIGHT / 2) + INSTRUCTIONSBUTTONOFFSETY) - ((INSTRUCTIONSBUTTONSCALEY*INSTRUCTIONSBUTTONRAWSCALE) / 2);
	bottom = top + (INSTRUCTIONSBUTTONSCALEY*INSTRUCTIONSBUTTONRAWSCALE);


	if (x >= left && x <= right && y >= top && y <= bottom) {
		cout << "inside INSTRUCTIONS button" << endl;
		*menu = "instructions";

		/*
		if (instructionsButtonTex.loadFromFile(INSTRUCTIONSBUTTONIMGPRESSEDPATH, TEXTURE_PIXEL_FORMAT_RGBA)) {
			//renderMainMenu();
		}
		*/
		return true;
	}

	/*
	instructionsButtonTex.loadFromFile(INSTRUCTIONSBUTTONIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA);
	playButtonTex.loadFromFile(PLAYBUTTONIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA);
	playAgainButtonTex.loadFromFile(PLAYAGAINBUTTONIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA);
	exitButtonTex.loadFromFile(EXITBUTTONIMGPATH, TEXTURE_PIXEL_FORMAT_RGBA);
	*/
	return false;

	
}



bool UI::clickOnInventoryItem(int x, int y, int* tile)
{

	double left, right, top, bottom;
	
	double scalex = INVENTORYITEMRAWSCALEX*INVENTORYITEMSCALE;
	double scaley = INVENTORYITEMRAWSCALEY*INVENTORYITEMSCALE;
	double paddingx = INVENTORYITEMPADDINGX - scalex;
	double paddingy = INVENTORYITEMPADDINGY - scaley;
	double offsetx = INVENTORYITEMSOFFSETX;
	double offsety = INVENTORYITEMSOFFSETY;

	int size = Inventory.size();

	for (int i = 0; i < ids.size(); ++i) cout << ids[i] << ",";
	cout << endl;

	for (int i = 0; i < size; ++i) {
		left = (offsetx - (scalex/2)) + (scalex+paddingx)*(i%6);
		right = left + scalex;
		top = (offsety - (scaley/2)) + (scaley + paddingy)*(i/6);
		bottom = top + scaley;

		
		cout << "Left: " << left << endl;
		cout << "Right: " << right << endl;
		cout << "Bottom: " << bottom << endl;
		cout << "Top: " << top << endl;
		

		if (x >= left && x <= right && y >= top && y <= bottom) {
			cout << "Clicked on inventory: " << i << endl << endl;
			*tile = ids[i];
			selectedItem = i;
			selectedItemID = ids[i];
			return true;
		}
	}

	return false;
}


void UI::renderHearts(float life) {

		//RENDER FIRST HEART
		glm::mat4 modelview;
		UIProgram.use();
		UIProgram.setUniformMatrix4f("projection", projection);
		UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(LIFEUIOFFSETX + 0.f,LIFEUIOFFSETY + 0.f, 0.f));
		modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
		//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
		modelview = glm::scale(modelview, glm::vec3(LIFESCALEFACTOR, LIFESCALEFACTOR, LIFESCALEFACTOR));
		modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
		UIProgram.setUniformMatrix4f("modelview", modelview);

		if (life >= 1.0f) {
			UIElements[0]->render(textures[0]);
		}
		else if (life == 0.5f) {
			UIElements[1]->render(textures[1]);
		}
		else  {
			UIElements[2]->render(textures[2]);
		}


		//RENDER SECOND HEART
		UIProgram.use();
		UIProgram.setUniformMatrix4f("projection", projection);
		UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(LIFEUIOFFSETX + LIFEUIOFFSETX_PADDING,LIFEUIOFFSETY + 0.f, 0.f));
		modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
		//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
		modelview = glm::scale(modelview, glm::vec3(LIFESCALEFACTOR, LIFESCALEFACTOR, LIFESCALEFACTOR));
		modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
		UIProgram.setUniformMatrix4f("modelview", modelview);
		
		if (life >= 2.0f) {
			UIElements[0]->render(textures[0]);
		}
		else if (life == 1.5f) {
			UIElements[1]->render(textures[1]);
		}
		else if (life < 1.5f) {
			UIElements[2]->render(textures[2]);
		}


		//RENDER THIRD HEART
		UIProgram.use();
		UIProgram.setUniformMatrix4f("projection", projection);
		UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(LIFEUIOFFSETX + LIFEUIOFFSETX_PADDING*2,LIFEUIOFFSETY + 0.f, 0.f));
		modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
		//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
		modelview = glm::scale(modelview, glm::vec3(LIFESCALEFACTOR, LIFESCALEFACTOR, LIFESCALEFACTOR));
		modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
		UIProgram.setUniformMatrix4f("modelview", modelview);
	
		if (life == 3.0f) {
			UIElements[0]->render(textures[0]);
		}
		else if (life == 2.5f) {
			UIElements[1]->render(textures[1]);
		}
		else if (life == 2.0f) {
			UIElements[2]->render(textures[2]);
		}
		else if (life <= 1.5f) {
			UIElements[2]->render(textures[2]);
		}
}





void UI::render(float playerlife,int goldCoins){
	renderHearts(playerlife);
	renderGoldCoins(goldCoins);
	
	//renderMaterialInventory();
}

void UI::renderMainMenu(bool dead)
{

	//BACKGROUND

	glm::mat4 modelview;
	UIProgram.use();
	UIProgram.setUniformMatrix4f("projection", projection);
	UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(float(SCREEN_WIDTH / 2), float(SCREEN_HEIGHT / 2), 0.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::scale(modelview, glm::vec3(10, SCREEN_HEIGHT/54, 0));
	modelview = glm::translate(modelview, glm::vec3(-32.f, -32.f, 0.f));
	UIProgram.setUniformMatrix4f("modelview", modelview);
	menuBackground->render(menuBackgroundTex);




	//PLAY BUTTON
	UIProgram.use();
	UIProgram.setUniformMatrix4f("projection", projection);
	UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(float(SCREEN_WIDTH / 2), float(SCREEN_HEIGHT / 2)+PLAYBUTTONOFFSETY, 0.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::scale(modelview, glm::vec3(PLAYBUTTONSCALEX, PLAYBUTTONSCALEY, 0));
	modelview = glm::translate(modelview, glm::vec3(-(PLAYBUTTONRAWSCALE/2), -(PLAYBUTTONRAWSCALE/2), 0.f));
	UIProgram.setUniformMatrix4f("modelview", modelview);
	if (!dead) {
		playButton->render(playButtonTex);
	}
	else {
		playButton->render(playAgainButtonTex);
	}

	//EXIT BUTTON
	UIProgram.use();
	UIProgram.setUniformMatrix4f("projection", projection);
	UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(float(SCREEN_WIDTH / 2), float(SCREEN_HEIGHT / 2) + EXITBUTTONOFFSETY, 0.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::scale(modelview, glm::vec3(EXITBUTTONSCALEX, EXITBUTTONSCALEY, 0));
	modelview = glm::translate(modelview, glm::vec3(-(EXITBUTTONRAWSCALE / 2), -(EXITBUTTONRAWSCALE / 2), 0.f));
	UIProgram.setUniformMatrix4f("modelview", modelview);
	exitButton->render(exitButtonTex);
	
	//INSTRUCTIONS BUTTON
	UIProgram.use();
	UIProgram.setUniformMatrix4f("projection", projection);
	UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(float(SCREEN_WIDTH / 2), float(SCREEN_HEIGHT / 2) + INSTRUCTIONSBUTTONOFFSETY, 0.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::scale(modelview, glm::vec3(INSTRUCTIONSBUTTONSCALEX, INSTRUCTIONSBUTTONSCALEY, 0));
	modelview = glm::translate(modelview, glm::vec3(-(INSTRUCTIONSBUTTONRAWSCALE / 2), -(INSTRUCTIONSBUTTONRAWSCALE / 2), 0.f));
	UIProgram.setUniformMatrix4f("modelview", modelview);
	instructionsButton->render(instructionsButtonTex);



	if (dead) {
		cout << "dead" << endl;
	}


}


