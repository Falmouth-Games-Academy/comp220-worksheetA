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

using namespace GLU;

enum class ComponentFlags
{
	NONE = 0x00,
	RENDERER = 0x01,	// Contains functionality for rendering GameObject
	MESH = 0x02,	// Contains functionality for storing and/or manipulating mesh
	TRANSLATION = 0x04		// Contains functionality for manipulating position, rotation, scale etc.
};

///<summary>
/// Interface for implementing the component-based system
///</summary>
class IComponent
{
public:
	IComponent() {};
	virtual ~IComponent() {};

	// Should all methods be here : render, translate etc. and have individual components deal with implementing/not implementing them?
	// Certainly a point worth discussing

	virtual bool hasFlags(ComponentFlags flags) 
	{
		return (componentFlags & flags) == flags;
	}

protected:
	ComponentFlags componentFlags;
private:
};