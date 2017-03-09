#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(string texturePath) {
	return _textureCache.getTexture(texturePath);
}