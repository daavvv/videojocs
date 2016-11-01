#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
#include <stdlib.h>
#include <stdio.h>

using json = nlohmann::json;



using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);

	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	//loadLevel(levelFile);
	cabar = false;
	coordenadas = minCoords;
	programa = program;

	string path = "levels/test_level.json";
	loadLevelTest(path);

	spritesheet.loadFromFile("images/blocks.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &program);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(0, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(0, glm::vec2(0.5f, 0.5f));
	sprite->changeAnimation(0);


	//creo animacions
	animations.clear();
	animations.resize(3500);

	create_animations(SKY);
	create_animations(LADDER);
	create_animations(SUPPORT_TERRAIN);
	create_animations(WATER);
	create_animations(WATER_1);
	create_animations(GRASS);
	create_animations(DIRT);
	prepareArrays();
}

TileMap::~TileMap()
{
	if(structMap != NULL)
		delete structMap;
}


void TileMap::update(int deltatime)
{
	sprite->update(deltatime);/*
	bool modificat = false;
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			if (structMap[j * mapSize.x + i].estat == 2) {
				structMap[j * mapSize.x + i].timeAnimation += deltatime;
				cout << " HE entrat!!!!" << endl;
				if (structMap[j * mapSize.x + i].timeAnimation > animations[structMap[j * mapSize.x + i].ID *10 + structMap[j * mapSize.x + i].estat].millisecsPerKeyframe)
				{
					cout << " aqui tambe entro obviament" << endl;
					structMap[j * mapSize.x + i].timeAnimation -= animations[structMap[j * mapSize.x + i].ID *10 + structMap[j * mapSize.x + i].estat].millisecsPerKeyframe;
					if (structMap[j * mapSize.x + i].instant_estat < 2) {
						structMap[j * mapSize.x + i].instant_estat = structMap[j * mapSize.x + i].instant_estat + 1;
					}
					else {
						structMap[j * mapSize.x + i].instant_estat = 0;
						structMap[j * mapSize.x + i].estat = 1;
						structMap[j * mapSize.x + i].ID = 0;
					}
					modificat = true;
				}

			}
		}
	}
	if (modificat) {
		prepareArrays();
	}*/
}

void TileMap::setCavar(bool cavar)
{
	this->cabar = cavar;
}


void TileMap::render()
{
	
	glEnable(GL_TEXTURE_2D);
	//use_tilesheet();
	tilesheet.use();
	glBindVertexArray(vao_background);
	glEnableVertexAttribArray(posLocation_background);
	glEnableVertexAttribArray(texCoordLocation_background);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);

	glBindVertexArray(vao_terrain);
	glEnableVertexAttribArray(posLocation_terrain);
	glEnableVertexAttribArray(texCoordLocation_terrain);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);

	
	glBindVertexArray(vao_background_objects);
	glEnableVertexAttribArray(posLocation_background_objects);
	glEnableVertexAttribArray(texCoordLocation_background_objects);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);

	
	glBindVertexArray(vao_foreground_objects);
	glEnableVertexAttribArray(posLocation_foreground_objects);
	glEnableVertexAttribArray(texCoordLocation_foreground_objects);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
	
	if (cabar) {
		sprite->setPosition(glm::vec2(float((tileToBeDigged.x + 2)*tileSize), float((tileToBeDigged.y - 3)*tileSize)));
		sprite->render();
	}
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo_background);
	glDeleteBuffers(1, &vbo_terrain);
	
	glDeleteBuffers(1, &vbo_background_objects);
	glDeleteBuffers(1, &vbo_foreground_objects);
	
}

void TileMap::create_animations(int ID) 
{
	//frames per segon
	//cout << ID << endl;

	animations[ID * 10 + 0].millisecsPerKeyframe = 125.f;
	animations[ID * 10 + 1].millisecsPerKeyframe = 125.f;
	animations[ID * 10 + 2].millisecsPerKeyframe = 125.f;
	
	int tile = ID;
	//cout << ID * 10 << endl;
	//afegir estats als blocs 0-> no existeix, 1-> existeix, 2 -> transicio  
	animations[ID * 10 + 1].keyframeDispl.push_back(glm::vec2(float((tile - 1) % tilesheetSize.x) / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y));

	animations[ID * 10 + 2].keyframeDispl.push_back(glm::vec2(float((tile - 1) % tilesheetSize.x)/ tilesheetSize.x + 0.2f, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y));
	animations[ID * 10 + 2].keyframeDispl.push_back(glm::vec2(float((tile - 1) % tilesheetSize.x)/ tilesheetSize.x + 0.4f, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y));
	animations[ID * 10 + 2].keyframeDispl.push_back(glm::vec2(float((tile - 1) % tilesheetSize.x)/ tilesheetSize.x + 0.6f, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y));

	animations[ID * 10 + 0].keyframeDispl.push_back(glm::vec2(float((tile - 1) % tilesheetSize.x) + 2.0f / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y));

}
bool TileMap::loadLevelTest(const string &levelFile)
{


	string path = "levels/test_level.json";
	
	ifstream file(path, std::ifstream::binary);
	ostringstream tmp;
	tmp << file.rdbuf();
	std::string jsonString = tmp.str();

	
	auto j3 = json::parse(jsonString);
	mapSize.y = int(j3["height"]);
	mapSize.x = int(j3["width"]);
	tileSize = blockSize = int(j3["tileheight"]);

	string tilesheet_path, data;
	int imageHeight, imageWidth, tilecount, tilewidth;

	
	for (json::iterator it = j3["tilesets"].begin(); it != j3["tilesets"].end(); ++it) { 	

  		json::iterator array = it->begin();

  		for (array; array != it->end(); ++array){


  			if (array.key() == "image"){
				tilesheet_path = array.value();
			}
			if (array.key() == "imageheight"){
				imageHeight = array.value();
			}
			if (array.key() == "imagewidth"){
				imageWidth = array.value();
			}
			if (array.key() == "tilecount"){
				tilecount = array.value();
			}
			if (array.key() == "tilewidth"){
				tilewidth = array.value();
			}



  			cout << array.key() << ": " << array.value() << endl;
  		}
	}


	tilesheet.loadFromFile(tilesheet_path, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);



	tilesheetSize.x = imageWidth/tilewidth;
	tilesheetSize.y = imageHeight/tilewidth;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	

	//map = new int[mapSize.x * mapSize.y];
	structMap = new Tile[mapSize.x*mapSize.y];
	background = new Tile[mapSize.x*mapSize.y];
	background_objects = new Tile[mapSize.x*mapSize.y];
	foreground_objects = new Tile[mapSize.x*mapSize.y];


	//Itera sobre las layers
	for (int i = 0; i < j3["layers"].size(); ++i){

			if (j3["layers"][i]["name"] == "Background"){
				
				for (int j = 0; j < j3["layers"][i]["data"].size(); j++){

					Tile tile;
					if (int(j3["layers"][i]["data"][j]) == SKY){
							tile.isSolid = false;
							tile.estat = 0;
							tile.instant_estat = 0;
							tile.timeAnimation = 0;
					} else {
							tile.isSolid = true;
							tile.estat = 1;
							tile.instant_estat = 0;
							tile.timeAnimation = 0;
					}
						//map[i] = int(array.value()[i]);
					tile.ID = int(j3["layers"][i]["data"][j]);
					background[j] = tile;		
				}
			}else if (j3["layers"][i]["name"] == "Terrain"){
				
				for (int j = 0; j < j3["layers"][i]["data"].size(); j++){

					Tile tile;
					//map[i] = int(array.value()[i]);
					tile.ID = int(j3["layers"][i]["data"][j]);
					//create_animations(tile.ID);

					if (tile.ID == GRASS){
						tile.isSolid = true;
						tile.isDiggable = true;
						tile.estat = 1;
						tile.instant_estat = 0;
						tile.timeAnimation= 0;
					}
					if (tile.ID == DIRT) {
						tile.isSolid = true;
						tile.isDiggable = true;
						tile.estat = 1;
						tile.instant_estat = 0;
						tile.timeAnimation = 0;
					}
					if (tile.ID == STONE) {
						tile.isSolid = true;
						tile.isDiggable = true;
						tile.estat = 1;
						tile.instant_estat = 0;
						tile.timeAnimation = 0;
					}
					if (tile.ID == IRON) {
						tile.isSolid = true;
						tile.isDiggable = true;
						tile.estat = 1;
						tile.instant_estat = 0;
						tile.timeAnimation = 0;
					}

					if (tile.ID == 0 || tile.ID == WATER || tile.ID == WATER_1){
						tile.isSolid = false;
						tile.estat = 0;
						tile.instant_estat = 0;
						tile.timeAnimation = 0;
					}else {
						tile.isSolid = true;
						tile.estat = 1;
						tile.instant_estat = 0;
						tile.timeAnimation = 0;
					}
					structMap[j] = tile;		
				}
			}else if (j3["layers"][i]["name"] == "BackgroundObjects"){
				
				for (int j = 0; j < j3["layers"][i]["data"].size(); j++){

					Tile tile;
					//map[i] = int(array.value()[i]);
					tile.ID = int(j3["layers"][i]["data"][j]);
					tile.isSolid = false;
					tile.estat = 0;
					tile.instant_estat = 0;
					tile.timeAnimation = 0;
					background_objects[j] = tile;		
				}
			}
			else if (j3["layers"][i]["name"] == "ForegroundObjects"){
				
				for (int j = 0; j < j3["layers"][i]["data"].size(); j++){

					Tile tile;
					//map[i] = int(array.value()[i]);
					tile.ID = int(j3["layers"][i]["data"][j]);
					tile.isSolid = false;
					tile.estat = 0;
					tile.instant_estat = 0;
					tile.timeAnimation = 0;
					foreground_objects[j] = tile;		
				}
			}
	}


	cout << "Background Map" << endl;
	
	//Background map
	for (int i = 0; i < mapSize.x * mapSize.y; ++i){
		cout << background[i].ID << ",";
		if ((i%mapSize.x) == (mapSize.x - 1)){
			cout << endl;
		}
	}
	cout << endl;

	cout << "Terrain Map" << endl;

	//Terrain map
	for (int i = 0; i < mapSize.x * mapSize.y; ++i){
		cout << structMap[i].ID << ",";
		if ((i%mapSize.x) == (mapSize.x - 1)){
			cout << endl;
		}
	}
	cout << endl;


	cout << "Physical view Map" << endl;

	//Terrain map physical view
	printPhysicalView();
	cout << endl;
	


	cout << "Position:" << position.x << "," << position.y << endl;
	cout << "Map size:" << mapSize.x << "," << mapSize.y << endl;
	cout << "Tilesheet size:" << tilesheetSize.x << "," << tilesheetSize.y << endl;
	cout << "TileTex size:" << tileTexSize.x << "," << tileTexSize.y << endl;
	cout << "Image width:" << imageWidth << endl;
	cout << "Image height:" << imageHeight << endl;
	cout << "Tilesheet width:" << tilesheet.width() << endl;
	cout << "Tilesheet height:" << tilesheet.height() << endl;
	cout << "Tile size:" << tileSize << endl;
	cout << "Block size:" << blockSize << endl;

	return true;

}


void TileMap::printPhysicalView() {
	for (int i = 0; i < mapSize.x * mapSize.y; ++i) {
		if (structMap[i].isSolid) {
			cout << 1 << ",";
		}
		else {
			cout << 0 << ",";
		}
		if ((i%mapSize.x) == (mapSize.x - 1)) {
			cout << endl;
		}
	}
}


void TileMap::prepareBackgroundObjects(const glm::vec2 &minCoords, ShaderProgram &program){

	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	//cout << "Min coords:" << minCoords.x << "," << minCoords.y << endl;

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = background_objects[j * mapSize.x + i].ID;
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				//texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x)/tilesheetSize.x, float((tile-1)/tilesheetSize.y) / tilesheetSize.y);
				texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x)/tilesheetSize.x, float((tile-1)/tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				texCoordTile[0] += halfTexel;
				//texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao_background_objects);
	glBindVertexArray(vao_background_objects);
	glGenBuffers(1, &vbo_background_objects);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_background_objects);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation_background_objects = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation_background_objects = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}



void TileMap::prepareForegroundObjects(const glm::vec2 &minCoords, ShaderProgram &program){

	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	//cout << "Min coords:" << minCoords.x << "," << minCoords.y << endl;

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = foreground_objects[j * mapSize.x + i].ID;
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				//texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x)/tilesheetSize.x, float((tile-1)/tilesheetSize.y) / tilesheetSize.y);
				texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x)/tilesheetSize.x, float((tile-1)/tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				texCoordTile[0] += halfTexel;
				//texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao_foreground_objects);
	glBindVertexArray(vao_foreground_objects);
	glGenBuffers(1, &vbo_foreground_objects);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_foreground_objects);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation_foreground_objects = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation_foreground_objects = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));



}




glm::vec2 TileMap::get_animation(int ID, int estat, int instant_estat) {
	//cout << animations[130 + estat].keyframeDispl[instant_estat].x << " " << animations[130 + estat].keyframeDispl[instant_estat].y << endl;
	return animations[DIRT*10 + estat].keyframeDispl[instant_estat];//return animations[ID + estat].keyframeDispl[instant_estat];
}





void TileMap::prepareTerrain(const glm::vec2 &minCoords, ShaderProgram &program){

	int nTiles = 0;
	Tile tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	//cout << "Min coords:" << minCoords.x << "," << minCoords.y << endl;

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = structMap[j * mapSize.x + i];
			if(tile.ID != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				//texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x)/tilesheetSize.x, float((tile-1)/tilesheetSize.y) / tilesheetSize.y);
				//texCoordTile[0] = get_animation(tile.ID, tile.estat, tile.instant_estat);
				texCoordTile[0] = glm::vec2(float((tile.ID-1)%tilesheetSize.x)/tilesheetSize.x, float((tile.ID-1)/tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				texCoordTile[0] += halfTexel;
				//texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao_terrain);
	glBindVertexArray(vao_terrain);
	glGenBuffers(1, &vbo_terrain);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_terrain);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation_terrain = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation_terrain = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));

}


void TileMap::prepareBackground(const glm::vec2 &minCoords, ShaderProgram &program){
	
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	//cout << "Min coords:" << minCoords.x << "," << minCoords.y << endl;

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = background[j * mapSize.x + i].ID;
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				//texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x)/tilesheetSize.x, float((tile-1)/tilesheetSize.y) / tilesheetSize.y);
				texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x)/tilesheetSize.x, float((tile-1)/tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				texCoordTile[0] += halfTexel;
				//texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao_background);
	glBindVertexArray(vao_background);
	glGenBuffers(1, &vbo_background);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_background);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation_background = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation_background = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));



}


void TileMap::prepareArrays()
{

	prepareBackground(coordenadas, programa);
	prepareTerrain(coordenadas, programa);
	prepareBackgroundObjects(coordenadas, programa);
	prepareForegroundObjects(coordenadas, programa);


	
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (structMap[y*mapSize.x + x].ID != 0 && structMap[y*mapSize.x + x].isSolid) {
			//structMap[y*mapSize.x + x].ID = 0;
			//structMap[y*mapSize.x + x].isSolid = false;
			return true;
		}
	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if (structMap[y*mapSize.x + x].ID != 0 && structMap[y*mapSize.x + x].isSolid) {
			//structMap[y*mapSize.x + x].ID = 0;
			//structMap[y*mapSize.x + x].isSolid = false;
			return true;
		}
	}
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;
	
	/*
	for (int i = 0; i < mapSize.x * mapSize.y; ++i) {
		cout << (structMap[i].isSolid && structMap[i].ID != 0) << ",";
		if ((i%mapSize.x) == (mapSize.x - 1)) {
			cout << endl;
		}
	}
	*/


	x0 = pos.x / tileSize; //32/32 = 1
	x1 = (pos.x + size.x - 1) / tileSize; //32+32-1 = 63/32 = 1
	y = (pos.y + size.y - 1) / tileSize; //352+32-1 / 32 = 11
	for(int x=x0; x<=x1; x++)
	{
		if(structMap[y*mapSize.x+x].ID != 0 && structMap[y*mapSize.x+x].isSolid)
		{
			//cout << structMap[y*mapSize.x + x].isSolid  << " " << structMap[y*mapSize.x + x].ID  << endl;
			
			if(*posY - tileSize * y + size.y <= 5)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
			
		}
	}
	return false;
}




bool TileMap::canJump(const glm::ivec2 &playerPos, const glm::ivec2 &size) const {

	int tilex, tiley;

	tilex = playerPos.x / tileSize;
	tiley = (playerPos.y + size.y - 1) / tileSize;

	tiley = tiley - 1;

	if (structMap[(tiley)*mapSize.x + tilex].ID == GRASS || structMap[(tiley)*mapSize.x + tilex].ID == DIRT 
		|| structMap[(tiley)*mapSize.x + tilex].ID == SUPPORT_TERRAIN || structMap[(tiley)*mapSize.x + tilex].ID == STONE
		|| structMap[(tiley)*mapSize.x + tilex].ID == IRON) {
		return false;
	}

	return true;
}





bool TileMap::bottomTileIsDiggable(const glm::ivec2 &playerPos, const glm::ivec2 &size) 
{

	int tilex, tiley;

	tilex = playerPos.x / tileSize;
	tiley = (playerPos.y + size.y - 1) / tileSize;


	if (structMap[(tiley+1)*mapSize.x+tilex].isDiggable && structMap[(tiley + 1)*mapSize.x + tilex].isSolid){
		//cout << "Is diggable" << endl;
		tileToBeDigged.x = tilex;
		tileToBeDigged.y = tiley+1;
		/*
		structMap[(tiley + 1)*mapSize.x + tilex].isDiggable = false;
		structMap[(tiley + 1)*mapSize.x + tilex].ID = 0;
		structMap[(tiley + 1)*mapSize.x + tilex].isSolid = false;
		*/
		return true;
	}
	else {
		//cout << "Is not diggable" << endl;
	}
	return false;
}


bool TileMap::bottomTileIsBuildable(const glm::ivec2 &playerPos, const glm::ivec2 &size, int *posY) 
{
	int tilex, tiley;
	tilex = playerPos.x / tileSize;
	tiley = (playerPos.y + size.y - 1) / tileSize;

	if (structMap[(tiley + 1)*mapSize.x + tilex].isSolid) {
		*posY = (tiley-1)*32;
		tileToBeBuilded.x = tilex;
		tileToBeBuilded.y = tiley;
		return true;
	}
	return false;
}


bool TileMap::leftTileIsBuildable(const glm::ivec2 &playerPos, const glm::ivec2 &size)
{
	int tilex, tiley;
	tilex = playerPos.x / tileSize;
	tiley = (playerPos.y + size.y - 1) / tileSize;

	if (!structMap[(tiley)*mapSize.x + tilex-1].isSolid) {
		tileToBeBuilded.x = tilex-1;
		tileToBeBuilded.y = tiley;
		return true;
	}
	return false;
}

bool TileMap::rightTileIsBuildable(const glm::ivec2 &playerPos, const glm::ivec2 &size)
{
	int tilex, tiley;
	tilex = playerPos.x / tileSize;
	tiley = (playerPos.y + size.y - 1) / tileSize;

	if (!structMap[(tiley)*mapSize.x + tilex + 1].isSolid) {
		tileToBeBuilded.x = tilex + 1;
		tileToBeBuilded.y = tiley;
		return true;
	}
	return false;
}





bool TileMap::buildTile(int ID) {

	structMap[tileToBeBuilded.y*mapSize.x + tileToBeBuilded.x].ID = ID;
	structMap[tileToBeBuilded.y*mapSize.x + tileToBeBuilded.x].isSolid = true;
	structMap[tileToBeBuilded.y*mapSize.x + tileToBeBuilded.x].isDiggable = true;
	structMap[tileToBeBuilded.y*mapSize.x + tileToBeBuilded.x].handbuilded = true;

	prepareArrays();

	return true;
}




bool TileMap::topTileIsDiggable(const glm::ivec2 &playerPos, const glm::ivec2 &size)
{

	int tilex, tiley;

	tilex = playerPos.x / tileSize;
	tiley = (playerPos.y + size.y - 1) / tileSize;


	if (structMap[(tiley - 1)*mapSize.x + tilex].isDiggable && structMap[(tiley - 1)*mapSize.x + tilex].isSolid) {
		//cout << "Is diggable" << endl;
		tileToBeDigged.x = tilex;
		tileToBeDigged.y = tiley - 1;
		/*
		structMap[(tiley + 1)*mapSize.x + tilex].isDiggable = false;
		structMap[(tiley + 1)*mapSize.x + tilex].ID = 0;
		structMap[(tiley + 1)*mapSize.x + tilex].isSolid = false;
		*/
		return true;
	}
	else {
		//cout << "Is not diggable" << endl;
	}
	return false;
}




bool TileMap::rightTileIsDiggable(const glm::ivec2 &playerPos, const glm::ivec2 &size)
{

	int tilex, tiley;

	tilex = playerPos.x / tileSize;
	tiley = (playerPos.y + size.y - 1) / tileSize;


	if (structMap[(tiley)*mapSize.x + tilex+1].isDiggable && structMap[(tiley)*mapSize.x + tilex+1].isSolid) {
		//cout << "Is diggable" << endl;
		tileToBeDigged.x = tilex+1;
		tileToBeDigged.y = tiley;
		/*
		structMap[(tiley + 1)*mapSize.x + tilex].isDiggable = false;
		structMap[(tiley + 1)*mapSize.x + tilex].ID = 0;
		structMap[(tiley + 1)*mapSize.x + tilex].isSolid = false;
		*/
		return true;
	}
	else {
		//cout << "Is not diggable" << endl;
	}
	return false;
}


bool TileMap::leftTileIsDiggable(const glm::ivec2 &playerPos, const glm::ivec2 &size)
{

	int tilex, tiley;

	tilex = playerPos.x / tileSize;
	tiley = (playerPos.y + size.y - 1) / tileSize;


	if (structMap[(tiley)*mapSize.x + tilex - 1].isDiggable && structMap[(tiley)*mapSize.x + tilex - 1].isSolid) {
		//cout << "Is diggable" << endl;
		tileToBeDigged.x = tilex - 1;
		tileToBeDigged.y = tiley;
		/*
		structMap[(tiley + 1)*mapSize.x + tilex].isDiggable = false;
		structMap[(tiley + 1)*mapSize.x + tilex].ID = 0;
		structMap[(tiley + 1)*mapSize.x + tilex].isSolid = false;
		*/
		return true;
	}
	else {
		//cout << "Is not diggable" << endl;
	}
	return false;
}










int TileMap::digTile() {

	int tile;
	tile = structMap[(tileToBeDigged.y)*mapSize.x + tileToBeDigged.x].ID;


	if (!structMap[(tileToBeDigged.y)*mapSize.x + tileToBeDigged.x].handbuilded) {

		if (tile == DIRT) {
			structMap[(tileToBeDigged.y)*mapSize.x + tileToBeDigged.x].ID = DIRT_CAVED;
		}
		if (tile == GRASS) {
			structMap[(tileToBeDigged.y)*mapSize.x + tileToBeDigged.x].ID = GRASS_CAVED;
		}
		if (tile == STONE) {
			structMap[(tileToBeDigged.y)*mapSize.x + tileToBeDigged.x].ID = DIRT_CAVED;
		}
		if (tile == IRON) {
			structMap[(tileToBeDigged.y)*mapSize.x + tileToBeDigged.x].ID = DIRT_CAVED;
		}
 	}
	else {
		structMap[(tileToBeDigged.y)*mapSize.x + tileToBeDigged.x].ID = 0;
	}


	structMap[(tileToBeDigged.y)*mapSize.x + tileToBeDigged.x].isDiggable = false;
	structMap[(tileToBeDigged.y)*mapSize.x + tileToBeDigged.x].isSolid = false;
	prepareArrays();
	cabar = false;


	for (int i = 0; i < mapSize.x * mapSize.y; ++i) {
		if (structMap[i].isSolid) {
			cout << 1 << ",";
		}
		else {
			cout << 0 << ",";
		}
		if ((i%mapSize.x) == (mapSize.x - 1)) {
			cout << endl;
		}
	}

	return tile;
}



bool TileMap::Exists_platform(const glm::ivec2 &pos, const glm::ivec2 &size)
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int y_max = y - 4; y > y_max; ++y_max) {
		for (int x = x0; x <= x1; x++)
		{
			if (structMap[y_max*mapSize.x + x].ID != 0)
			{
				return true;
			}

		}
	}

	return false;

}

bool TileMap::isOverGoldCoin(const glm::ivec2 & playerPos, const glm::ivec2 & size)
{

	int tilex, tiley;
	tilex = float(playerPos.x)/float(tileSize);
	tiley = float(playerPos.y + size.y - 1) / float(tileSize);

	if (background_objects[(tiley)*mapSize.x + tilex].ID == GOLD_COIN) {


		background_objects[(tiley)*mapSize.x + tilex].ID = 0;

		prepareBackgroundObjects(coordenadas, programa);

		return true;
	}
	return false;
}




/*
bool TileMap::bottomTileIsDiggable(const glm::ivec2 &playerPos, const glm::ivec2 &size)
{

int tilex, tiley;

tilex = playerPos.x / tileSize;
tiley = (playerPos.y + size.y - 1) / tileSize;


if (structMap[(tiley+1)*mapSize.x+tilex].isDiggable && structMap[(tiley + 1)*mapSize.x + tilex].isSolid){
//cout << "Is diggable" << endl;
tileToBeDigged.x = tilex;
tileToBeDigged.y = tiley+1;

structMap[(tiley + 1)*mapSize.x + tilex].isDiggable = false;
structMap[(tiley + 1)*mapSize.x + tilex].ID = 0;
structMap[(tiley + 1)*mapSize.x + tilex].isSolid = false;

return true;
	}
	else {
		//cout << "Is not diggable" << endl;
	}
	return false;
}
*/























