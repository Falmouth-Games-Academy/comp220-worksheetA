#include "Texture.h"

GLuint loadTextureFromFile(const std::string& filename)
{
	// Load in a texture from file and copy it in an openGL texture
	GLuint textureID;

	GLenum	textureFormat = GL_RGB;
	GLenum	internalFormat = GL_RGB8;

	SDL_Surface * surface = IMG_Load(filename.c_str());	// Load in a surface
	if (surface == nullptr)
	{
		printf("Could not load file %s", IMG_GetError());
		return 0;
	}
	// More error checking is recommended

	GLint	nOfColors = surface->format->BytesPerPixel;
	if (nOfColors == 4)					//	contains	an	alpha	channel
	{
		// Checks to see where the RED pixel is, as software can export with different colour orders
		if (surface->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
		}
		else {
			textureFormat = GL_BGRA;
			internalFormat = GL_RGBA8;
		}
	}
	else if (nOfColors == 3)					//	no	alpha	channel
	{
		if (surface->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGB;
			internalFormat = GL_RGB8;
		}
		else {
			textureFormat = GL_BGR;
			internalFormat = GL_RGB8;
		}
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Nearest seems to be a point filter
	glTexImage2D(GL_TEXTURE_2D,	//	Texture type
		0,	// Level (Mip maps - 0 means texture is copied in mip map level 0)
		internalFormat,		// Texture format (RGBA8 | RGB)
		surface->w,	// Width of texture
		surface->h, //  Height of texture
		0,	// Border: if you copy less of texture we can specify the colour to replace with
		textureFormat,	// File texture format (RGB, RGBA, BGR, etc.)
		GL_UNSIGNED_BYTE,	// Pixel data type (usually 0 - 255)
		surface->pixels	// texture pixels themselves
	);

	// surface is no longer necessary
	SDL_FreeSurface(surface);

	return textureID;
}

GLuint CreateTexture(int width, int height)
{
	GLuint textureID = 0;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	return textureID;
}
