#pragma once

#include <sstream>
#include <fstream>
#include <iostream>

#include <array>
#include <vector>
#include <map>

#include "GLUtils.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

enum class ComponentFlags
{
	NONE = 0,
	RENDERER = 1,	// Contains functionality for rendering GameObject
	MESH = 2,	// Contains functionality for storing and/or manipulating mesh
	TRANSLATION = 4		// Contains functionality for manipulating position, rotation, scale etc.
};

///<summary>
/// Interface for implementing the component-based system
///</summary>
class IComponent
{
public:
	IComponent() {};
	virtual ~IComponent() {};

	virtual bool hasFlags(ComponentFlags flags) 
	{
		return GLU::operator|(GLU::operator&(componentFlags, flags), flags) == ComponentFlags::NONE ? false : true;
	}

protected:
	ComponentFlags componentFlags;
private:
};