#ifndef _UI_INCLUDE
#define _UI_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <iostream>
using namespace std;


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class UI
{

public:
	UI(){}

	void init();
	void update(int deltaTime);
	void render();
	void initShaders();

private:
	float currentTime;
	glm::mat4 projection;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	ShaderProgram UIProgram;


	/*
	GLuint vao_background,vao_terrain, vao_background_objects, vao_foreground_objects;
	GLuint vbo_background,vbo_terrain, vbo_background_objects, vbo_foreground_objects;
	GLint posLocation_background, texCoordLocation_background, posLocation_background_objects, texCoordLocation_background_objects;
	GLint posLocation_terrain, texCoordLocation_terrain, posLocation_foreground_objects, texCoordLocation_foreground_objects;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize, coordenadas;
	ShaderProgram programa;
	*/

};


#endif // _SCENE_INCLUDE

