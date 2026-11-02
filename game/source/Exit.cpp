#include <vector>
#include "Exit.h"


Exit::~Exit() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Exit::init(ShaderProgram& program) {

	vector<float> vertices;

	renderImage.loadFromFile("images/exit.png", TEXTURE_PIXEL_FORMAT_RGBA);
	renderImage.setWrapS(GL_CLAMP_TO_EDGE);
	renderImage.setWrapT(GL_CLAMP_TO_EDGE);
	renderImage.setMinFilter(GL_NEAREST);
	renderImage.setMagFilter(GL_NEAREST);

	// First triangle
	vertices.push_back(-1.f); vertices.push_back(-1.f);
	vertices.push_back(0.f); vertices.push_back(1.f);
	vertices.push_back(1.f); vertices.push_back(-1.f);
	vertices.push_back(1.f); vertices.push_back(1.f);
	vertices.push_back(1.f); vertices.push_back(1.f);
	vertices.push_back(1.f); vertices.push_back(0.f);

	// Second triangle
	vertices.push_back(-1.f); vertices.push_back(-1.f);
	vertices.push_back(0.f); vertices.push_back(1.f);
	vertices.push_back(1); vertices.push_back(1);
	vertices.push_back(1.f); vertices.push_back(0.f);
	vertices.push_back(-1.f); vertices.push_back(1.f);
	vertices.push_back(0.f); vertices.push_back(0.f);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void Exit::render() {
	glEnable(GL_TEXTURE_2D);
	renderImage.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}