#include "SpriteSheet.h"


unsigned int SpriteSheet::GetHeight() {
	return _spriteSheetImage->height;
}
unsigned int SpriteSheet::GetWidth() {
	return _spriteSheetImage->width;
}
unsigned int SpriteSheet::SpriteHeight() {
	return _spriteHeight;
}
unsigned int SpriteSheet::SpriteWidth() {
	return _spriteWidth;
}

GamesEngineeringBase::Image* SpriteSheet::SheetData() {
	return _spriteSheetImage;
}