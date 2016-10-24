#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "json.hpp"

#define SKY 94
#define LADDER 319
#define SUPPORT_TERRAIN 227
#define WATER 13
#define WATER_1 14
#define GRASS 237

struct Tile {
	Tile():isSolid(false), ID(0), isDiggable(false) {}
	bool isSolid;
	bool isDiggable;
	int estat;// estat 0 = destruit; 1 = viu; 2 = destruint-se 
	int ID;
};

// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);
	~TileMap();

	void render();
	void free();
	
	int getTileSize() const { return tileSize; }
	glm::ivec2 getMapSize() const {
		return mapSize;
	}

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool bottomTileIsDiggable(const glm::ivec2 &playerPos, const glm::ivec2 &size) const;


	
private:
	void printPhysicalView();
	bool loadLevel(const string &levelFile);
	bool loadLevelTest(const string &levelFile);
	void prepareArrays();
	void prepareBackground(const glm::vec2 &minCoords, ShaderProgram &program);
	void prepareTerrain(const glm::vec2 &minCoords, ShaderProgram &program);
	void prepareBackgroundObjects(const glm::vec2 &minCoords, ShaderProgram &program);
	void prepareForegroundObjects(const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLuint vao_background,vao_terrain, vao_background_objects, vao_foreground_objects;
	GLuint vbo_background,vbo_terrain, vbo_background_objects, vbo_foreground_objects;
	GLint posLocation_background, texCoordLocation_background, posLocation_background_objects, texCoordLocation_background_objects;
	GLint posLocation_terrain, texCoordLocation_terrain, posLocation_foreground_objects, texCoordLocation_foreground_objects;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize, coordenadas;
	ShaderProgram programa;
	//int *map;
	Tile *structMap;
	Tile *background;
	Tile *background_objects;
	Tile *foreground_objects;

};


#endif // _TILE_MAP_INCLUDE


