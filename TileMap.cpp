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

	string path = "levels/test_level.json";
	loadLevelTest(path);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if(structMap != NULL)
		delete structMap;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
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

	//cout << j3 << endl;

	//cout << j3["tilesets"] << endl;
	//cout << j3["tilesets"]["image"] << endl;


	
	for (json::iterator it = j3["tilesets"].begin(); it != j3["tilesets"].end(); ++it) {
  		//cout << *it << '\n';
  		//cout << counter << endl;
  		//counter++;

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

	/*
	tilesheetSize.x = imageWidth/32;  //Numero de celdas en el tilesheet CAMBIAAARRR
	tilesheetSize.y = imageHeight/32;
	*/

	tilesheetSize.x = imageWidth/tilewidth;
	tilesheetSize.y = imageHeight/tilewidth;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	

	//map = new int[mapSize.x * mapSize.y];
	structMap = new Tile[mapSize.x*mapSize.y];
	background = new Tile[mapSize.x*mapSize.y];

	/*
	for (json::iterator it = j3["layers"].begin(); it != j3["layers"].end(); ++it){
		json::iterator array = it->begin();
  		for (array; array != it->end(); ++array){
  			if (array.key() == "data"){
				for (int i = 0; i < int(j3["height"])*int(j3["width"]); i++){	
						Tile tile;
						if (int(array.value()[i]) == CIELO){
							tile.isSolid = false;
						} else {
							tile.isSolid = true;	
						}
						//map[i] = int(array.value()[i]);
						tile.ID = int(array.value()[i]);
						structMap[i] = tile;		
				}

			};
  			cout << array.key() << ": " << array.value() << endl;
  		}
	}*/


	//Itera sobre las layers
	for (int i = 0; i < j3["layers"].size(); ++i){

			if (j3["layers"][i]["name"] == "Background"){
				
				for (int j = 0; j < j3["layers"][i]["data"].size(); j++){

					Tile tile;
					if (int(j3["layers"][i]["data"][j]) == CIELO){
							tile.isSolid = false;
					} else {
							tile.isSolid = true;	
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

					if (tile.ID == 0){
						tile.isSolid = false;
					}else {
						tile.isSolid = true;
					}
					structMap[j] = tile;		
				}
			}
	}

	//Background map
	for (int i = 0; i < mapSize.x * mapSize.y; ++i){
		cout << background[i].ID << ",";
		if ((i%mapSize.x) == (mapSize.x - 1)){
			cout << endl;
		}
	}
	cout << endl;

	//Terrain map
	for (int i = 0; i < mapSize.x * mapSize.y; ++i){
		cout << structMap[i].ID << ",";
		if ((i%mapSize.x) == (mapSize.x - 1)){
			cout << endl;
		}
	}
	cout << endl;

	//Terrain map physical view
	for (int i = 0; i < mapSize.x * mapSize.y; ++i){
		if (structMap[i].isSolid){
			cout << 1 << ",";
		} else {
			cout << 0 << ",";
		}	
		if ((i%mapSize.x) == (mapSize.x - 1)){
			cout << endl;
		}
	}
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

/*


bool TileMap::loadLevel(const string &levelFile)
{


	cout << "hola" << endl;

	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	
	map = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			fin.get(tile);
			if(tile == ' ')
				map[j*mapSize.x+i] = 0;
			else
				map[j*mapSize.x+i] = tile - int('0');
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();



	cout << "Position:" << position.x << "," << position.y << endl;
	cout << "Map size:" << mapSize.x << "," << mapSize.y << endl;
	cout << "Tilesheet size:" << tilesheetSize.x << "," << tilesheetSize.y << endl;
	cout << "TileTex size:" << tileTexSize.x << "," << tileTexSize.y << endl;
	//cout << "Image width:" << imageWidth << endl;
	//cout << "Image height:" << imageHeight << endl;

	cout << "Tile size:" << tileSize << endl;
	cout << "Block size:" << blockSize << endl;
	cout << "Tilesheet width:" << tilesheet.width() << endl;
	cout << "Tilesheet height:" << tilesheet.height() << endl;


	for (int i = 0; i < mapSize.x * mapSize.y; ++i){
		cout << map[i];
		if ((i%mapSize.x) == (mapSize.x - 1)){
			cout << endl;
		}
		else {
			cout << ",";
		}
	}
	cout << endl;

	
	return true;
}

*/

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	cout << "Min coords:" << minCoords.x << "," << minCoords.y << endl;

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = structMap[j * mapSize.x + i].ID;
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

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
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
	for(int y=y0; y<=y1; y++)
	{
		if(structMap[y*mapSize.x+x].ID != 0 && structMap[y*mapSize.x+x].isSolid)
			return true;
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
		if(structMap[y*mapSize.x+x].ID != 0 && structMap[y*mapSize.x+x].isSolid)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;
	
	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for(int x=x0; x<=x1; x++)
	{
		if(structMap[y*mapSize.x+x].ID != 0 && structMap[y*mapSize.x+x].isSolid)
		{
			if(*posY - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}
	return false;
}






























