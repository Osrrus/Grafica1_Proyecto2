#pragma once
#include "Model.h"
#include <iostream>
#include <fstream>
#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"

using std::fstream;

class Obj :public CModel
{
	public:
		Obj();
		~Obj();
		bool load(string path);
		void displayBE();
		void displayDL();
		void createDL();
};
