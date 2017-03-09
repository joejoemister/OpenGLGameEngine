#include "MainGame.h"
#include "Error.h"

MainGame::MainGame() : _window(nullptr), _width(1024), _height(720), _gameState(GameState::PLAY), 
time(0), _maxFPS(120.0f)
{
}

MainGame::~MainGame()
{
}

void MainGame::run() {
	initSystems();
	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyjump_pack/PNG/CharacterRight_Standing.png");
	
	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyjump_pack/PNG/CharacterRight_Standing.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f, 0.0f, 1.0f, 1.0f, "Textures/jimmyjump_pack/PNG/CharacterRight_Standing.png");

	//_playerTexture = ImageLoader::loadPNG("Textures/jimmyjump_pack/PNG/CharacterRight_Standing.png");

	gameLoop();
}

void MainGame::initSystems() {
	// Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	_window = SDL_CreateWindow("OpenGlGame", 100, 100, _width, _height, SDL_WINDOW_OPENGL);
	
	if (_window == nullptr) {
		Error::fatalError("SDL Window could not be created");
	}
	
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		Error::fatalError("SDL_GLContext could not be created");
	}

	glewExperimental = true;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Error::fatalError("Glew failed to initialize");
	}

	cout << "OpenGl Version: " << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	SDL_GL_SetSwapInterval(1);

	initShaders();
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("shaders/shader.vert", "shaders/shader.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		float startTicks = SDL_GetTicks();

		processInput();
		time += 0.09f;
		drawGame();
		calculateFPS();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			frameCounter = 0;
			cout << _fps << endl;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}

	}
}

void MainGame::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
				break;
		}
		switch (evnt.key.keysym.sym) {
			case SDLK_ESCAPE:
				SDL_Quit();
				exit(0);
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("playerSampler");
	glUniform1i(textureLocation, 0);

	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, time);

	for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);
}

void MainGame::calculateFPS() {
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	
	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
	
	prevTicks = currentTicks;

	int count;

	currentFrame++;

	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	} else {
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}

	frameTimeAverage /= count;
	
	if (frameTimeAverage > 0) {
		_fps = 1000.0f / frameTimeAverage;
	} else {
		_fps = 60;
	}

}