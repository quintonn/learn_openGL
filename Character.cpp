#ifndef CHARACTER_H
#define CHARACTER_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

#endif // !CHARACTER_H