#include "UI.h"
#include "Game.h"


void UI::init(){
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(128.f, 128.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };


	initShaders();


	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	addUIElement(geom,texCoords,UIProgram,"images/UI/hud_2.png");
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	/*texCoords[0] = glm::vec2(0.5f, 0.5f); texCoords[1] = glm::vec2(1.f, 1.f);
	addUIElement(geom,texCoords,UIProgram,"images/rocks.jpg");*/

	
	/*
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//GLfloat g_vertex_buffer_data[] = {-1.0f, -1.0f, 0.0f,1.0f, -1.0f, 0.0f,0.0f,  1.0f, 0.0f}
	GLfloat g_vertex_buffer_data[] = {-0.5f, -0.5f, 0.0f,0.5f, -0.5f, 0.0f,0.5f,  0.5f, 0.0f,-0.5f,  0.5f, 0.0f};

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	*/

}

void UI::addUIElement(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program, string path){
	TexturedQuad *texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, program);
	UIElements.push_back(texQuad);
	Texture tex;
	if(tex.loadFromFile(path,TEXTURE_PIXEL_FORMAT_RGB)){
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


void UI::render(){
	
	/*
	UIProgram.use();
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);*/



	/*
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(384.f, 48.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);*/


	glm::mat4 modelview;
	UIProgram.use();
	UIProgram.setUniformMatrix4f("projection", projection);
	UIProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(5.f, 5.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::scale(modelview,glm::vec3( 0.3f, 0.3f, 0.3f ));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	UIProgram.setUniformMatrix4f("modelview", modelview);
	
	for (int i = 0; i < UIElements.size(); ++i){
		UIElements[i]->render(textures[i]);

	}cout << endl;
	
}


