#pragma once
#include "System.h"
#include "Coordinator.h"
#include "DebugComponent.h"

class DebugSystem : public System
{
public:
	void DebugIDs();
	void Update(Coordinator* coord);
};