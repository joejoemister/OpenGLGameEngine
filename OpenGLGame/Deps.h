#pragma once


#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "Error.h"

using namespace std;

enum DEPS { DEPS_OK, DEPS_NOT_OK };

class Deps {

	Deps();
	~Deps();

public:
	void depsOk();
	
	DEPS deps;

};