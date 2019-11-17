#include"map.h"


Map::Map(int heightMap, int widthMap) :
	heightMap_(heightMap), widthMap_(widthMap)
{
	bool isLoad = cross_.loadFromFile("resource/cross.png", IntRect(0, 0, 60, 60));
	if (isLoad == false) {
		throw std::runtime_error("Map::Map() Error loading pictures");
	}

	isLoad = earth_.loadFromFile("resource/earth_0.png", IntRect(0, 0, 60, 60));
	if (isLoad == false) {
		throw std::runtime_error("Map::Map() Error loading pictures");
	}

	isLoad = lava_.loadFromFile("resource/lava_1.png", IntRect(0, 0, 60, 60));
	if (isLoad == false) {
		throw std::runtime_error("Map::Map() Error loading pictures");
	}

	isLoad = road_.loadFromFile("resource/road.png", IntRect(0, 0, 60, 60));
	if (isLoad == false) {
		throw std::runtime_error("Map::Map() Error loading pictures");
	}

	TileMap_ = new string[heightMap_];
	for(int i =0; i < heightMap_; i++) {
			TileMap_[i] = new char[widthMap_];
		}

	createTemplateMap();
}


Map::~Map() 
{
	delete[] TileMap_;
}


void Map::createTemplateMap()
{ 
	TileMap_[0] =  "00000000000000000000000000000000000000000000000000000000000";
	TileMap_[1] =  "000    00rrrrrrrrr0      000000           000rrrrrrrrr00000";
	TileMap_[2] =  "00       rrrrrrrrr        0000             ccrrrrrrrrrcc 00";
	TileMap_[3] =  "0        rrrrrrrrr ccc           cc  cc    ccrrrrrrrrrcc 00";
	TileMap_[4] =  "0        rrrrrrrrr                 cccc    ccrrrrrrrrrcc 00";
	TileMap_[5] =  "0   cc ccrrrrrrrrr   ccc          cccc     ccrrrrrrrrrcc  0";
	TileMap_[6] =  "0   cccccrrrrrrrrr       cc        ccccc   ccrrrrrrrrrcc 00";
	TileMap_[7] =  "0    ccccrrrrrrrrr                    cc   ccrrrrrrrrrcc 00";
	TileMap_[8] =  "00     ccrrrrrrrrrr                        ccrrrrrrrrrcc 00";
	TileMap_[9] =  "00     ccrrrrrrrrrrrc                      ccrrrrrrrrcc   0";
	TileMap_[10] = "00     ccrrrrrrrrrrrrc   ccc               ccrrrrrrrrcc   0";
	TileMap_[11] = "00     ccrrrrrrrrrrrc ccc                 ccrrrrrrrrrcc   0";
	TileMap_[12] = "0      ccrrrrrrrrrrc                cc   ccrrrrrrrrrrcc   0";
	TileMap_[13] = "0    c ccrrrrrrrrrc              ccc     ccrrrrrrrrrrcc   0";
	TileMap_[14] = "0  ccc ccrrrrrrrrrc             cccc     ccrrrrrrrrrrcc   0";
	TileMap_[15] = "0      ccrrrrrrrrrcccccccccccccc  ccc   ccrrrrrrrrrrrcc   0";
	TileMap_[16] = "0      ccrrrrrrrrrrrrrrrrrrrrrrcccc     ccrrrrrrrrrrcc    0";
	TileMap_[17] = "0       ccrrrrrrrrrrrrrrrrrrrrrrrrrc    ccrrrrrrrrrrcc    0";
	TileMap_[18] = "0        ccrrrrrrrrrrrrrrrrrrrrrrrrrcccccrrrrrrrrrrcc    00";
	TileMap_[19] = "0        ccrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrccc      00";
	TileMap_[20] = "0        ccrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrcc        00";
	TileMap_[21] = "0     cccccrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrccc         00";
	TileMap_[22] = "00        ccrrrrrrrr000000000rrrrrrrrrrrrrrrrcc           0";
	TileMap_[23] = "00        ccrrrrrrrr000000000000rrrrrrrrrrrrrcc           0";
	TileMap_[24] = "00        ccrrrrrrrr00000000000000rrrrrrrrrrrcc          00";
	TileMap_[25] = "00       ccrrrrrrrrrr00000000000000rrrrrrrrrrcc          00";
	TileMap_[26] = "0        ccrrrrrrrrrrr0000000000000rrrrrrrrrrcc          00";
	TileMap_[27] = "0        ccrrrrrrrrrrrr00000000000rrrrrrrrrrrcc          00";
	TileMap_[28] = "0         ccrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrcc          00";
	TileMap_[29] = "0          ccrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrcc           0";
	TileMap_[30] = "0           ccrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrcc    cc      0";
	TileMap_[31] = "0    cc      ccrrrrrrrrrrrrrrrrrccccrrrrrrrrcc  cc        0";
	TileMap_[32] = "0    cccc      ccrrrrrrrrrrrrrrrccccrrrrrrrcc  ccc        0";
	TileMap_[33] = "00       cc      ccrrrrrrrrrrrrrrrrrrrrrrrrcc ccccc       0";
	TileMap_[34] = "00        cc      ccrrrrrrrrrrrrrrrrrrrrrrcc    cccc     00";
	TileMap_[35] = "00         cc       ccrrrrrrrrrrrrrrrrrrrcc ccc          00";
	TileMap_[36] = "0          cc        ccrrrrrrrrrrrrrrrrrrcc   ccc        00";
	TileMap_[37] = "0      ccc             ccrrrrrrrrrrrrrrrrcc              00";
	TileMap_[38] = "00                     ccccccccrrrrrrrrrrcc              00";
	TileMap_[39] = "000                          cc00rrrrrrr000             000";
	TileMap_[40] = "00000000000000000000000000000000000000000000000000000000000";
	TileMap_[41] = "000  00000000  000000    000  00      0000   000000  000000";
}


void Map::createMap(RenderWindow &window)
{
	for (int i = 0; i < heightMap_; i++) {
		for (int j = 0; j < widthMap_; j++) {
			if (TileMap_[i].c_str()[j] == 'c') {
				sprite_.setTexture(cross_);
			}

			if (TileMap_[i].c_str()[j] == ' ') {
				sprite_.setTexture(earth_);
			}

			if (TileMap_[i].c_str()[j] == '0') {
				sprite_.setTexture(lava_);
			}

			if (TileMap_[i].c_str()[j] == 'r') {
				sprite_.setTexture(road_);
			}

			sprite_.setPosition(j * 60.0f, i * 60.0f);
			window.draw(sprite_);
		}
	}
}


string* Map::getTileMap() const
{
	return TileMap_;
}
