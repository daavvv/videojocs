#include "UI.h"
#include "Game.h"



#define LIFEUIOFFSETX -35
#define LIFEUIOFFSETY -35
#define LIFEUIOFFSETX_PADDING 35
#define LIFESCALEFACTOR  0.2

#define MATERIALSUIOFFSETX -35
#define MATERIALSUIOFFSETY 10

#define MATERIALSCALEFACTOR 0.35
#define NUMBERSSEPARATION 40


void UI::init(){
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(128.f, 128.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };


	initShaders();

	//LOAD HEARTS
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f,1.f); 
	addUIElement(geom, texCoords, UIProgram, "images/UI/UI_HEART_FULL.png");//0
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	addUIElement(geom, texCoords, UIProgram, "images/UI/UI_HEART_HALF.png");//1
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	addUIElement(geom, texCoords, UIProgram, "images/UI/UI_HEART_EMPTY.png");//2

	//LOAD MATERIALS

	//STONE
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	addUIElement(geom, texCoords, UIProgram, "images/UI/stone.png");//3
	//STONE COUNTER
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	addUIElement(geom, texCoords, UIProgram, "images/UI/numbers/hud_0.png");//4

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
		else if (life < 1.5f) {
			UIElements[2]->render(textures[2]);
		}
}

void UI::renderMaterials() {

	//STONES ICON
	glm::mat4 modelview;
	UIProgram.use();
	UIProgram.setUniformMatrix4f("projection", projection);
	UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(MATERIALSUIOFFSETX + 0.f, MATERIALSUIOFFSETY + 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::scale(modelview, glm::vec3(MATERIALSCALEFACTOR, MATERIALSCALEFACTOR, MATERIALSCALEFACTOR));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	UIProgram.setUniformMatrix4f("modelview", modelview);
	UIElements[3]->render(textures[3]);

	//STONES VALUE
	
	UIProgram.use();
	UIProgram.setUniformMatrix4f("projection", projection);
	UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(MATERIALSUIOFFSETX + NUMBERSSEPARATION, MATERIALSUIOFFSETY + 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::scale(modelview, glm::vec3(0.1f, 0.1f, 0.1f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	UIProgram.setUniformMatrix4f("modelview", modelview);
	UIElements[4]->render(textures[4]);
	


}

void UI::render(float playerlife){
	renderHearts(playerlife);
	renderMaterials();
}


