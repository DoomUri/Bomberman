#pragma once
#ifndef _EXIT_INCLUDE
#define _EXIT_INCLUDE

#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


class Exit
{
public:
	~Exit();

	void init(ShaderProgram& program);
	void render();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	Texture renderImage;
};

#endif