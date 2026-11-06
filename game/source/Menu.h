#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"

// Classe Menu: s'encarrega de pintar els menus quan no estem jugant: Menu principal, presentacions de nivells,
// game over, time over, ... Es un quad texturat que es pinta amb matrius de transformació identitat.

class Menu 
{
public:
	~Menu();

	void init(ShaderProgram& program);
	void render();
	void setImage(int i);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	Texture renderImage;
	Texture mainMenu, instructionsMenu, creditsMenu, Lvl1, Lvl2, Lvl3, Lvl4, LvlBoss, gameOver, winMenu, timeOver;
};

#endif