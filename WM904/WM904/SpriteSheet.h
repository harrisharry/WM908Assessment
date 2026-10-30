#pragma once
#include "src/GamesEngineeringBase.h"
class SpriteSheet {
private:
	GamesEngineeringBase::Image* _spriteSheetImage;
	unsigned int _spriteWidth = 0; //Records the offset for each sprite by its height and width.
	unsigned int _spriteHeight = 0;
public:

	SpriteSheet(std::string filePath,unsigned int spriteWidth = 32, unsigned int spriteHeight = 32) {
		_spriteWidth = spriteWidth;
		_spriteHeight = spriteHeight;
		_spriteSheetImage = new GamesEngineeringBase::Image;
		_spriteSheetImage->load(filePath);
	}
	GamesEngineeringBase::Image* SheetData();
	unsigned int GetHeight();
	unsigned int GetWidth();
	unsigned int SpriteWidth();
	unsigned int SpriteHeight();
};