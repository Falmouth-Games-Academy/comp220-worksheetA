#include "DebugSystem.h"

void DebugSystem::DebugIDs()
{
	
}
void DebugSystem::Update(Coordinator* coord)
{
	if (sy_Entities.size() > 0)
	{
		std::set<Entity>::iterator it = sy_Entities.begin();
		for (int i = 0; i < sy_Entities.size(); i++)
		{
			std::cout << coord->GetComponent<DebugComponent>(*it).name << " " << coord->GetComponent<DebugComponent>(*it).info << std::endl;
			std::advance(it, i);
		}
	}
	/*
	for (Entity entity : sy_Entities)
		std::cout << coord->GetComponent<DebugComponent>(entity).name << " " << coord->GetComponent<DebugComponent>(entity).info << " " << std::endl;
		*/
}