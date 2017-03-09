#pragma once

#include "Deps.h"
#include <string>

class Error
{
public:
	Error();
	~Error();

	static void fatalError(std::string errorString);

};

