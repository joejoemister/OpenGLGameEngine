#pragma once

#include "Error.h"
#include "Deps.h"
#include "GLTexture.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, string texturePath);

	void draw();

private:
	int _x;
	int _y;
	int _width;
	int _height;
	GLuint _vboID;
	GLTexture _texture;

};

