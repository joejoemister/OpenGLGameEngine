#pragma once

#include "Deps.h"
#include "TextureCache.h"

class ResourceManager
{
public:
	static GLTexture getTexture(string texturePath);
private:
	static TextureCache _textureCache;
};

