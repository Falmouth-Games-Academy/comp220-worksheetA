#pragma once
#include <set>
#include <iostream>
#include "Entity.h"
#include "ComponentManager.h"

class System
{
public:
	std::set<Entity> sy_Entities;
};