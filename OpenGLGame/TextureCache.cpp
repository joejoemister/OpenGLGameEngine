#include "TextureCache.h"

#include "ImageLoader.h"

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(string texturePath) {
	auto mit = _textureMap.find(texturePath);

	if (mit == _textureMap.end()) {
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);

		_textureMap.insert(make_pair(texturePath, newTexture));

		cout << "Loaded cache Texture\n";

		return newTexture;
	}

	cout << "Used cache Texture\n";

	return mit->second;

}
