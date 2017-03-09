#pragma once

#include "Deps.h"

#include <vector>

class IOManager
{
public:
	static bool readFileToBuffer(string filePath, vector<unsigned char>& buffer);
};

