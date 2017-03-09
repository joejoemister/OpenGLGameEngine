#pragma once

#include "GLTexture.h"
#include "Deps.h"
#include "Sprite.h"
#include "GLSLProgram.h"

#include <windows.h>
#include <vector>

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

	int _width, _height;

private:
	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void initShaders();
	void calculateFPS();

	SDL_Window* _window;

	GameState _gameState;

	vector<Sprite*> _sprites;

	GLSLProgram _colorProgram;

	float _fps;
	float _frameTime;
	float _maxFPS;

	float time;
};

