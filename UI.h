#ifndef _UI_INCLUDE
#define _UI_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TexturedQuad.h"
#include "Texture.h"
#include <iostream>
#include <vector>

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
	void addUIElement(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program, string path);

private:
	float currentTime;
	glm::mat4 projection;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	ShaderProgram UIProgram;
	vector<TexturedQuad*> UIElements;
	vector<Texture> textures;
};


#endif // _SCENE_INCLUDE

