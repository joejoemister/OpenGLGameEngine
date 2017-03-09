#pragma once

#include "Deps.h"
#include "GLTexture.h"

#include <map>

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLTexture getTexture(string texturePath);

private:
	map<string, GLTexture> _textureMap;
};

