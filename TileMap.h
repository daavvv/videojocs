#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "Sprite.h"
#include "ShaderProgram.h"
#include "json.hpp"
#include "AnimKeyframes.h"


#define SKY 94
#define LADDER 319
#define SUPPORT_TERRAIN 227
#define WATER 13
#define WATER_1 14
#define GRASS 237
#define GRASS_CAVED 134
#define DIRT 220
#define DIRT_CAVED 113
#define GOLD_COIN 144
#define STONE 88
#define STONE_CAVED 286

struct Tile {
	Tile():isSolid(false), ID(0), isDiggable(false), handbuilded(false) {}
	bool isSolid;
	bool isDiggable;
	bool handbuilded;
	int estat;// estat 0 = destruit; 1 = viu; 2 = destruint-se 
	int instant_estat;
	int timeAnimation;
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
	void update(int deltatime);
	void setCavar(bool cavar);

	
	int getTileSize() const { return tileSize; }
	glm::ivec2 getMapSize() const {
		return mapSize;
	}
	bool Exists_platform(const glm::ivec2 &pos, const glm::ivec2 &size);
	bool isOverGoldCoin(const glm::ivec2 &playerPos, const glm::ivec2 &size);

	glm::vec2 get_animation(int ID, int estat, int instant_estat);
	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;

	bool bottomTileIsDiggable(const glm::ivec2 &playerPos, const glm::ivec2 &size);
	bool topTileIsDiggable(const glm::ivec2 &playerPos, const glm::ivec2 &size);
	bool leftTileIsDiggable(const glm::ivec2 &playerPos, const glm::ivec2 &size);
	bool rightTileIsDiggable(const glm::ivec2 &playerPos, const glm::ivec2 &size);

	bool canJump(const glm::ivec2 &playerPos, const glm::ivec2 &size) const;

	bool bottomTileIsBuildable(const glm::ivec2 &playerPos, const glm::ivec2 &size, int *posY);
	bool leftTileIsBuildable(const glm::ivec2 &playerPos, const glm::ivec2 &size);
	bool rightTileIsBuildable(const glm::ivec2 &playerPos, const glm::ivec2 &size);

	bool buildTile(int ID);
	int digTile();


	
private:
	void create_animations(int ID);
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
	glm::ivec2 position, mapSize, tilesheetSize, tileToBeDigged, tileToBeBuilded;
	int tileSize, blockSize;
	Texture tilesheet, spritesheet;

	glm::vec2 tileTexSize, coordenadas;
	ShaderProgram programa;
	//int *map;
	Tile *structMap;
	bool cabar;
	Sprite *sprite;
	Tile *background;
	Tile *background_objects;
	Tile *foreground_objects;
	vector<AnimKeyframes> animations;
};


#endif // _TILE_MAP_INCLUDE


