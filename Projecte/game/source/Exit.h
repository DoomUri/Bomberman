#pragma once
#ifndef _EXIT_INCLUDE
#define _EXIT_INCLUDE

#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


// Classe Exit: Serveix per fer apareixer les lletres EXIT pampallugants al matar tots els enemics d'un nivell. Es un quad texturat
// amb mètodes render() i init().

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