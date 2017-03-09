#include "Deps.h"

Deps::Deps() : deps(DEPS_NOT_OK) {} 

Deps::~Deps() {}

void Deps::depsOk() {
	if (!DEPS_OK) {
		if (GLEW_OK == 1 && !SDL_INIT_EVERYTHING == 1) {
			Error::fatalError("Something went wrong with SDL or GLEW are you sure the dll files are in the folder with OpenGLGame.exe?");
		}
	}
}