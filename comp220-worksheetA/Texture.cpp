#include "Texture.h"

GLuint loadTextureFromFile(const std::string& filename)
{
	GLuint textureID;

	// Img surface function returns a pointer (c_str, char array)
	SDL_Surface * surface = IMG_Load(filename.c_str());

	// Error checking
	if (surface == nullptr)
	{
		printf("Could not load file %s\n", IMG_GetError());
		return 0;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);


	// Takes pixel data from surface and copies into texture - GL_UNSIGNED_BYTE (0,255) - GL_RGBA8 8 bites per pixel
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

	// Cleanup memory
	SDL_FreeSurface(surface);

	return textureID;
}
